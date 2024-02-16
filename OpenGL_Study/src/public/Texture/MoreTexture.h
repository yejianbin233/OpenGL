
#pragma once
#include "../GeometryVertices.h"
#include "./../../public/Main.h"

namespace MoreTextureRendering
{
    static int MoreTextureRenderingRun()
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
        glBufferData(GL_ARRAY_BUFFER, sizeof(geometry_vertices_data::square::simpleWithTexCoord), geometry_vertices_data::square::simpleWithTexCoord, GL_STATIC_DRAW); 

        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(geometry_vertices_data::square::indices), geometry_vertices_data::square::indices, GL_STATIC_DRAW);
        
        unsigned int VAO; // 声明 VAO
        glGenVertexArrays(1, &VAO); // 构建 VAO
        glBindVertexArray(VAO); // 绑定 VAO
        // 设置顶点属性指针 - 顶点数据索引 0，大小为 3，stride（步幅/偏移）为 3 个 float，与"顶点着色器"layout (location = 0) in vec3 aPos; 对应
        /* 如果有多个数据就需要进行多次设置，如
        *   layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aColor;
            layout (location = 2) in vec2 aTexCoord;
         */
        // 设置索引 0 为顶点位置数据
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // 设置索引 1 为纹理坐标数据
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // -- 纹理数据 --
        // 加载纹理数据 - 并且是 JPG 格式的纹理
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // OpenGL要求 y 轴 0.0 坐标是在图片的底部的，但是图片的 y 轴 0.0 坐标通常在顶部。可以使用该行命令来翻转 y 轴。
        unsigned char *data = stbi_load("src/Image/Resources/container.jpg", &width, &height, &nrChannels, 0);
        
        // 设置 OpenGL 纹理设置
        unsigned int texture1;
        glGenTextures(1, &texture1);
        // 使用glActiveTexture激活纹理单元，传入我们需要使用的纹理单元 或直接设置
        // glActiveTexture(GL_TEXTURE0); // 纹理索引 0
        // glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1); // 纹理索引 1
        glBindTexture(GL_TEXTURE_2D, texture1);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);// 可以使用前面载入的图片数据生成一个纹理
            glGenerateMipmap(GL_TEXTURE_2D); // 生成纹理的 MinMap
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        
        stbi_image_free(data); // 设置好 OpenGL 的纹理数据后，及时释放无用的图片数据。

        // texture 2
        // ---------
        unsigned int texture2;
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        data = stbi_load("src/Image/Resources/awesomeface.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            // 请注意，awesomeface.png 具有透明度，因此具有 alpha 通道，因此请确保告诉 OpenGL 数据类型为 GL_RGBA。
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        // -- 纹理数据 -- 

        // -- 数据准备 --

        // -- 着色器（Shader） --
        Shader ourShader("src/Shaders/VertexShaders/Texture.vs", "src/Shaders/FragmentShaders/MoreTexture.fs");
        ourShader.use();

        // 多纹理设置
        ourShader.setInt("texture1", 0);
        ourShader.setInt("texture2", 1);
        // -- 着色器（Shader）  --
        
        // render loop - 渲染循环
        while (!glfwWindowShouldClose(window))
        {
            // input - 用户输入
            GlobalFuns::processInput(window);

            // render - --渲染指令--

            // bind textures on corresponding texture units
            // 使用glActiveTexture激活纹理单元，传入我们需要使用的纹理单元
            glActiveTexture(GL_TEXTURE0); // 纹理索引 0
            glBindTexture(GL_TEXTURE_2D, texture1);
            glActiveTexture(GL_TEXTURE1); // 纹理索引 1
            glBindTexture(GL_TEXTURE_2D, texture2);
            
            ourShader.use(); // 使用着色器

            glBindVertexArray(VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            
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
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteTextures(1, &texture1);
        glDeleteTextures(1, &texture2);
        glDeleteBuffers(1, &EBO);
        // -- 清除缓冲数据 -- 


        // glfw: terminate, clearing all previously allocated GLFW resources.
        // 当渲染循环结束后我们需要正确释放/删除之前的分配的所有资源。
        glfwTerminate();
        return 0;
    }
}

