#pragma once
#include "./../../../public/Main.h"

namespace DepthTextureRendering
{
    static int DepthTextureRenderingRun()
    {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        // --------------------
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, GlobalFuns::framebuffer_size_callback);
        glfwSetCursorPosCallback(window, GlobalFuns::mouse_callback);
        glfwSetScrollCallback(window, GlobalFuns::scroll_callback);

        // tell GLFW to capture our mouse
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);

        // build and compile shaders
        // -------------------------
        Shader simpleDepthShader("src/Shaders/VertexShaders/Lighting/Shadow/ShadowMappingDepth.vs", "src/Shaders/FragmentShaders/Lighting/Shadow/ShadowMappingDepth.fs");
        Shader debugDepthQuad("src/Shaders/VertexShaders/Lighting/Shadow/DebugDepth.vs", "src/Shaders/FragmentShaders/Lighting/Shadow/DebugDepth.fs");

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float planeVertices[] = {
            // positions            // normals         // texcoords
            25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
            -25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f,

            25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
            -25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f,
            25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 25.0f
        };
        // plane VAO
        unsigned int planeVBO;
        glGenVertexArrays(1, &GlobalFuns::planeVAO);
        glGenBuffers(1, &planeVBO);
        glBindVertexArray(GlobalFuns::planeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindVertexArray(0);

        // load textures
        // -------------
        unsigned int woodTexture = GlobalFuns::loadTexture("src/Image/Resources/wood.png");

        // 渲染深度贴图    
        // configure depth map FBO
        // -----------------------
        const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024; // 深度贴图尺寸 1024x1024
        unsigned int depthMapFBO;
        glGenFramebuffers(1, &depthMapFBO); // 创建深度贴图 Buffer
        // create depth texture
        unsigned int depthMap;
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                     NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // attach depth texture as FBO's depth buffer
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0); // 将深度数据缓冲到深度贴图
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        // shader configuration
        // --------------------
        debugDepthQuad.use();
        debugDepthQuad.setInt("depthMap", 0);

        // lighting info
        // -------------
        glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);

        // render loop
        // -----------
        while (!glfwWindowShouldClose(window))
        {
            // per-frame time logic
            // --------------------
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // input
            // -----
            GlobalFuns::processInput(window);

            // render
            // ------
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // 1. render depth of scene to texture (from light's perspective)
            // --------------------------------------------------------------
            glm::mat4 lightProjection, lightView;
            glm::mat4 lightSpaceMatrix;
            float near_plane = 1.0f, far_plane = 7.5f;
            lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane); // 正交矩阵，使用的是一个所有光线都平行的定向光。出于这个原因，我们将为光源使用正交投影矩阵
            lightView = glm::lookAt(camera.Position, glm::vec3(0.0f), camera.WorldUp); // 光源的视图空间（使用摄像机位置作为光源位置）
            lightSpaceMatrix = lightProjection * lightView; // 将任何三维位置转变到光源的可见坐标空间。
            // render scene from light's point of view
            simpleDepthShader.use();
            simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

            glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
            glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
            glClear(GL_DEPTH_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, woodTexture);
            GlobalFuns::renderScene(simpleDepthShader); // 渲染场景
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // reset viewport - 清空视口
            glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // render Depth map to quad for visual debugging
            // ---------------------------------------------
            debugDepthQuad.use();
            debugDepthQuad.setFloat("near_plane", near_plane);
            debugDepthQuad.setFloat("far_plane", far_plane);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, depthMap); // 采样深度贴图
            GlobalFuns::renderQuad();

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &GlobalFuns::planeVAO);
        glDeleteBuffers(1, &planeVBO);

        glfwTerminate();
        return 0;
    }
}