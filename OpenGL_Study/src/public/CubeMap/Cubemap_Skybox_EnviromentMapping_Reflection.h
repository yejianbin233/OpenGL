#pragma once
#include "Model.h"
#include "../GeometryVertices.h"
#include "./../../public/Main.h"


// 光照贴图
namespace CubeMapSkyboxEnvironmentMappingRendering
{
    static int CubeMapSkyboxEnvironmentMappingRenderingRun()
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
        glEnable(GL_DEPTH_TEST); // 开启"深度测试"

        
        float skyboxVertices[] = {
            // positions          
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };

        // skybox VAO
        unsigned int skyboxVAO, skyboxVBO;
        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        
        Model ourModel("src/Model/nanosuit/nanosuit.obj");

        // -- 纹理数据 --
        // load textures (we now use a utility function to keep the code more organized)
        // -----------------------------------------------------------------------------
        unsigned int diffuseMap = GlobalFuns::loadTexture("src/Image/Resources/container2.png");
        unsigned int specularMap = GlobalFuns::loadTexture("src/Image/Resources/container2_specular.png");

        // 加载立方体纹理，需要注意加载的顺序（在数组中的索引位置）
        std::vector<std::string> faces
        {
            "src/Image/Resources/skybox/right.jpg",
            "src/Image/Resources/skybox/left.jpg",
            "src/Image/Resources/skybox/top.jpg",
            "src/Image/Resources/skybox/bottom.jpg",
            "src/Image/Resources/skybox/front.jpg",
            "src/Image/Resources/skybox/back.jpg"
        };
        unsigned int cubemapTexture = GlobalFuns::loadCubemap(faces);
        // -- 纹理数据 --
        
        // -- 着色器（Shader） --
        Shader skyboxShader("src/Shaders/VertexShaders/CubeMap/CubeMapSkybox.vs", "src/Shaders/FragmentShaders/CubeMap/CubeMapSkybox.fs");
        Shader sceneShader("src/Shaders/VertexShaders/CubeMap/Cubemap_Skybox_EnviromentMapping_Reflection.vs", "src/Shaders/FragmentShaders/CubeMap/Cubemap_Skybox_EnviromentMapping_Reflection.fs");
        // -- 着色器（Shader）  --
        
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f); // 光源位置
        
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
            
            sceneShader.use();
            sceneShader.setInt("material.diffuse", 0); // 设置漫反射贴图
            sceneShader.setInt("material.specular", 1); // 设置高光反射贴图
            // bind textures on corresponding texture units
            // 使用glActiveTexture激活纹理单元，传入我们需要使用的纹理单元
            // 多纹理设置
            glActiveTexture(GL_TEXTURE0); // 纹理索引 0
            glBindTexture(GL_TEXTURE_2D, diffuseMap);
            glActiveTexture(GL_TEXTURE1); // 纹理索引 1
            glBindTexture(GL_TEXTURE_2D, specularMap);
            
            // view/projection transformations
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 model = glm::mat4(1.0f);

            // 天空盒渲染
            glDepthMask(GL_FALSE);
            skyboxShader.use();
            // ... 设置观察和投影矩阵
            skyboxShader.setMat4("projection", projection);
            skyboxShader.setMat4("view", view);
            model = glm::scale(model, glm::vec3(20));
            skyboxShader.setMat4("model", model);
            glBindVertexArray(skyboxVAO);
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glDepthMask(GL_TRUE);
            
            // be sure to activate shader when setting uniforms/drawing objects
            sceneShader.use();
            sceneShader.setMat4("projection", projection);
            sceneShader.setMat4("view", view);
            // world transformation
            model = glm::mat4(1.0f);
            sceneShader.setMat4("model", model);
            
            ourModel.Draw(sceneShader);

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteTextures(1, &diffuseMap);
        glDeleteTextures(1, &specularMap);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return 0;
    }
}

