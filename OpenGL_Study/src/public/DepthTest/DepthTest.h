#pragma once
#include "../GeometryVertices.h"
#include "./../../public/Main.h"


// 使用索引定义多个面，可形成立体。
namespace DepthTestRendering
{
    static int DepthTestRenderingRun()
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
        
        glEnable(GL_DEPTH_TEST); // 开启"深度测试"，深度测试默认是禁用的，所以如果要启用深度测试的话，我们需要用GL_DEPTH_TEST选项来启用它
        // glDepthFunc(GL_ALWAYS); // 深度测试函数，永远通过深度测试
        glDepthFunc(GL_LESS); // 深度测试函数，在片段深度值小于缓冲的深度值时通过测试
        
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
        Shader DepthTestShader("src/Shaders/VertexShaders/DepthTest/DepthTest.vs", "src/Shaders/FragmentShaders/DepthTest/DepthTest.fs");
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
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // "深度测试"-在每个渲染迭代之前使用GL_DEPTH_BUFFER_BIT来清除深度缓冲，否则你会仍在使用上一次渲染迭代中的写入的深度值
            //glDepthMask(GL_FALSE); // 在某些情况下你会需要对所有片段都执行深度测试并丢弃相应的片段，但不希望更新深度缓冲。基本上来说，你在使用一个只读的(Read-only)深度缓冲。OpenGL允许我们禁用深度缓冲的写入，只需要设置它的深度掩码(Depth Mask)设置为GL_FALSE
            
            DepthTestShader.use();
            DepthTestShader.setInt("material.diffuse", 0); // 设置漫反射贴图
            DepthTestShader.setInt("material.specular", 1); // 设置高光反射贴图
            // bind textures on corresponding texture units
            // 使用glActiveTexture激活纹理单元，传入我们需要使用的纹理单元
            // 多纹理设置
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap); // 设置漫反射贴图索引为 0
            // bind specular map
            glActiveTexture(GL_TEXTURE1);// 设置高光反射贴图索引为 1
            glBindTexture(GL_TEXTURE_2D, specularMap);
            
            // view/projection transformations
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            glm::mat4 view = camera.GetViewMatrix();

            // be sure to activate shader when setting uniforms/drawing objects
            DepthTestShader.use();
            DepthTestShader.setMat4("projection", projection);
            DepthTestShader.setMat4("view", view);
            DepthTestShader.setVec3("viewPos", camera.Position);

            // 材质属性
            DepthTestShader.setFloat("material.shininess", 64.0f);
            
            
            // 材质属性
            
            // 光源属性
            DepthTestShader.setVec3("light.position", lightPos);
            DepthTestShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
            DepthTestShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
            DepthTestShader.setVec3("light.specular", 2.0f, 2.0f, 2.0f);

            DepthTestShader.setFloat("light.constant",  1.0f);
            DepthTestShader.setFloat("light.linear",    0.09f);
            DepthTestShader.setFloat("light.quadratic", 0.032f);
            
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
                DepthTestShader.setMat4("model", model);

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

