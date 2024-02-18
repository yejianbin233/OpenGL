#pragma once
#include "../../GeometryVertices.h"
#include "./../../../public/Main.h"


// 使用索引定义多个面，可形成立体。
namespace StandardLightingSpotLightRendering
{
    static int StandardLightingSpotLightRenderingRun()
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
        
        // first, configure the cube's VAO (and VBO)
        unsigned int VBO, cubeVAO;
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(geometry_vertices_data::cube::verticesWithTexCoords), geometry_vertices_data::cube::verticesWithTexCoords, GL_STATIC_DRAW);

        glBindVertexArray(cubeVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // -- 纹理数据 --
        // load textures (we now use a utility function to keep the code more organized)
        // -----------------------------------------------------------------------------
        unsigned int diffuseMap = GlobalFuns::loadTexture("src/Image/Resources/container2.png");
        unsigned int specularMap = GlobalFuns::loadTexture("src/Image/Resources/container2_specular.png");
        // -- 纹理数据 --
        
        // -- 着色器（Shader） --
        Shader lightingShader("src/Shaders/VertexShaders/Lighting/LightingSource/StandardLighting_SpotLight.vs", "src/Shaders/FragmentShaders/Lighting/LightingSource/StandardLighting_SpotLight.fs");
        // -- 着色器（Shader）  --
        
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

            
            lightingShader.use();
            lightingShader.setInt("material.diffuse", 0); // 设置漫反射贴图
            lightingShader.setInt("material.specular", 1); // 设置高光反射贴图
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

            // be sure to activate shader when setting uniforms/drawing objects
            lightingShader.use();
            lightingShader.setMat4("projection", projection);
            lightingShader.setMat4("view", view);
            lightingShader.setVec3("viewPos", camera.Position);

            // 材质属性
            lightingShader.setFloat("material.shininess", 64.0f);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap); // 设置漫反射贴图索引为 0
            // bind specular map
            glActiveTexture(GL_TEXTURE1);// 设置高光反射贴图索引为 1
            glBindTexture(GL_TEXTURE_2D, specularMap);
            
            // 材质属性
            
            // 光源属性
            lightingShader.setVec3("light.position", camera.Position); // 摄像机位置作为聚光源位置
            lightingShader.setVec3("light.direction", camera.Front); // 摄像机向前方向作为聚光源照射方向
            lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
            
            lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
            lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
            lightingShader.setVec3("light.specular", 2.0f, 2.0f, 2.0f);

            lightingShader.setFloat("light.constant",  1.0f);
            lightingShader.setFloat("light.linear",    0.09f);
            lightingShader.setFloat("light.quadratic", 0.032f);
            
            // 光源属性
            
            // positions all containers - 场景物体数组
            glm::vec3 cubePositions[] = {
                glm::vec3( 0.0f,  0.0f,  0.0f),
                glm::vec3( 2.0f,  5.0f, -15.0f),
                glm::vec3(-1.5f, -2.2f, -2.5f),
                glm::vec3(-3.8f, -2.0f, -12.3f),
                glm::vec3( 2.4f, -0.4f, -3.5f),
                glm::vec3(-1.7f,  3.0f, -7.5f),
                glm::vec3( 1.3f, -2.0f, -2.5f),
                glm::vec3( 1.5f,  2.0f, -2.5f),
                glm::vec3( 1.5f,  0.2f, -1.5f),
                glm::vec3(-1.3f,  1.0f, -1.5f)
            };

            // render the cube - 绘制 i 个场景物体
            glBindVertexArray(cubeVAO);
            for (unsigned int i = 0; i < 10; i++)
            {
                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                lightingShader.setMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            
            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &cubeVAO);
        glDeleteTextures(1, &diffuseMap);
        glDeleteTextures(1, &specularMap);
        glDeleteBuffers(1, &VBO);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return 0;
    }
}

