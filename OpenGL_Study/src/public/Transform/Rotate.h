#pragma once
#include "../GeometryVertices.h"
#include "./../../public/Main.h"


namespace RotateRendering
{
    static int RotateRenderingRun()
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

        // -- Window Setting -- glfw window creation - 创建一个窗口对象，这个窗口对象存放了所有和窗口相关的数据，而且会被 GLFW 的其他函数频繁地用到。
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        
        glfwMakeContextCurrent(window);

        glfwSetFramebufferSizeCallback(window, GlobalFuns::framebuffer_size_callback); // 窗口尺寸变化回调函数
        // -- Window Setting --


        // -- Glad  --glad: load all OpenGL function pointers
        // GLAD 是用来管理 OpenGL 的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        // -- Glad  --
        // -- 数据准备 -- 数据初始化代码（只运行一次 (除非你的物体频繁改变)）
        unsigned int VBO; // 声明 VBO
        glGenBuffers(1, &VBO);// 构建缓冲
        glBindBuffer(GL_ARRAY_BUFFER, VBO); // 把新创建的缓冲绑定到 GL_ARRAY_BUFFER 目标上
        // 缓冲数据，把顶点数组复制到缓冲中供OpenGL使用
        glBufferData(GL_ARRAY_BUFFER, sizeof(geometry_vertices_data::triangles::small), geometry_vertices_data::triangles::small, GL_STATIC_DRAW); 

        unsigned int VAO; // 声明 VAO
        glGenVertexArrays(1, &VAO); // 构建 VAO
        glBindVertexArray(VAO); // 绑定 VAO
        // 设置顶点属性指针 - 顶点数据索引 0，大小为 3，stride（步幅/偏移）为 3 个 float，与"顶点着色器"layout (location = 0) in vec3 aPos; 对应
        /* 如果有多个数据就需要进行多次设置，如
        *   layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aColor;
            layout (location = 2) in vec2 aTexCoord;
         */
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // -- 数据准备 --

        // -- 着色器（Shader） --
        Shader ourShader("src/Shaders/VertexShaders/Translate.vs", "src/Shaders/FragmentShaders/Default.fs");
        ourShader.use();
        // -- 着色器（Shader）  --

        // render loop - 渲染循环
        while (!glfwWindowShouldClose(window))
        {
            // input - 用户输入
            GlobalFuns::processInput(window);

            // render - --渲染指令--
            // 清除上一帧渲染数据
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            // ourShader.use(); // 使用着色器
            glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

            ourShader.use();
            ourShader.setMat4("transform", transform);
            
            glDrawArrays(GL_TRIANGLES, 0, 3); // 绘制三角形
            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // 检查并调用事件，交换缓冲
            
            glfwSwapBuffers(window);
            glfwPollEvents();
            // -------------------------------------------------------------------------------
            // render - --渲染指令--
        }


        // optional: de-allocate all resources once they've outlived their purpose:
        // -- 清除缓冲数据 -- 
        // glDeleteVertexArrays(1, &VAO);
        // glDeleteBuffers(1, &VBO);
        // glDeleteBuffers(1, &EBO);
        // -- 清除缓冲数据 -- 


        // glfw: terminate, clearing all previously allocated GLFW resources.
        // 当渲染循环结束后我们需要正确释放/删除之前的分配的所有资源。
        glfwTerminate();
        return 0;
    }
}

