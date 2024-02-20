#pragma once
#include "../GeometryVertices.h"
#include "./../../public/Main.h"


// 使用索引定义多个面，可形成立体。
namespace StencilTestRendering
{
    static int StencilTestRenderingRun()
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
        glDepthFunc(GL_LESS); // 深度测试函数
        glEnable(GL_STENCIL_TEST); // 开启"模板测试"
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // 模板测试函数，描述了OpenGL应该对模板缓冲内容做什么
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // 应该如何更新缓冲。GL_KEEP	保持当前储存的模板值；GL_REPLACE	将模板值设置为glStencilFunc函数设置的ref值

        // build and compile shaders
        // -------------------------
        Shader shader("src/Shaders/VertexShaders/StencilTest/StencilTest.vs", "src/Shaders/FragmentShaders/StencilTest/StencilTest.fs");
        Shader shaderSingleColor("src/Shaders/VertexShaders/StencilTest/StencilTest.vs", "src/Shaders/FragmentShaders/StencilTest/StencilTestEdgeColor.fs");

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float cubeVertices[] = {
            // positions          // texture Coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
        };
        float planeVertices[] = {
            // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
            5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
            -5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

            5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
            5.0f, -0.5f, -5.0f, 2.0f, 2.0f
        };
        // cube VAO
        unsigned int cubeVAO, cubeVBO;
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        glBindVertexArray(cubeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glBindVertexArray(0);

        // plane VAO
        unsigned int planeVAO, planeVBO;
        glGenVertexArrays(1, &planeVAO);
        glGenBuffers(1, &planeVBO);
        glBindVertexArray(planeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glBindVertexArray(0);

        // load textures
        // -------------
        unsigned int cubeTexture = GlobalFuns::loadTexture("src/Image/Resources/marble.jpg");
        unsigned int floorTexture = GlobalFuns::loadTexture("src/Image/Resources/metal.png");

        // shader configuration
        // --------------------
        shader.use();
        shader.setInt("texture1", 0);

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
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            // don't forget to clear the stencil buffer!

            // set uniforms
            shaderSingleColor.use();
            auto model = glm::mat4(1.0f);
            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
                                                    0.1f, 100.0f);
            shaderSingleColor.setMat4("view", view);
            shaderSingleColor.setMat4("projection", projection);

            shader.use();
            shader.setMat4("view", view);
            shader.setMat4("projection", projection);

            // draw floor as normal, but don't write the floor to the stencil buffer, we only care about the containers. We set its mask to 0x00 to not write to the stencil buffer.
            // 像往常一样绘制地板，但不要将地板写入模具缓冲区，我们只关心容器。我们将其掩码设置为0x00以不写入模具缓冲区。
            glStencilMask(0x00);// 每一位在写入模板缓冲时都会变成0（禁用写入）
            // floor
            glBindVertexArray(planeVAO);
            glBindTexture(GL_TEXTURE_2D, floorTexture);
            shader.setMat4("model", glm::mat4(1.0f));
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);

            // 1st. render pass, draw objects as normal, writing to the stencil buffer
            // 1. 渲染过程，正常绘制对象，写入模具缓冲区
            // --------------------------------------------------------------------
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilMask(0xFF);// 每一位写入模板缓冲时都保持原样
            // cubes
            glBindVertexArray(cubeVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, cubeTexture);
            model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // 2nd. render pass: now draw slightly scaled versions of the objects, this time disabling stencil writing.
            // Because the stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are not drawn, thus only drawing 
            // the objects' size differences, making it look like borders.
            // 2. 渲染过程：现在绘制稍微缩放的对象版本，这一次禁用模具编写。
            //因为模具缓冲区现在已经充满了几个1。缓冲区中为1的部分未绘制，因此仅绘制
            //对象的大小差异，使其看起来像边框。
            // -----------------------------------------------------------------------------------------------------------------------------
            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            glStencilMask(0x00);
            glDisable(GL_DEPTH_TEST);
            shaderSingleColor.use();
            float scale = 1.1f;
            // cubes
            glBindVertexArray(cubeVAO);
            glBindTexture(GL_TEXTURE_2D, cubeTexture);
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
            model = glm::scale(model, glm::vec3(scale, scale, scale));
            shaderSingleColor.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(scale, scale, scale));
            shaderSingleColor.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            glEnable(GL_DEPTH_TEST);

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &cubeVAO);
        glDeleteVertexArrays(1, &planeVAO);
        glDeleteBuffers(1, &cubeVBO);
        glDeleteBuffers(1, &planeVBO);

        glfwTerminate();
        return 0;
    }
}
