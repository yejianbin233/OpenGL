#pragma once
#include "./../../public/Main.h"
// #include "GLEW/glew.h"

namespace AntiAliasingRendering
{

    static int AntiAliasingRenderingRun()
    {
        // Init GLFW
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_SAMPLES, 4); // 希望使用一个包含 N 个样本的多重采样缓冲。

        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr); // Windowed
        glfwMakeContextCurrent(window);

        // Set the required callback functions
        glfwSetKeyCallback(window, GlobalFuns::key_callback);
        glfwSetCursorPosCallback(window, GlobalFuns::mouse_callback);
        glfwSetScrollCallback(window, GlobalFuns::scroll_callback);

        // Options
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	

        // Initialize GLEW to setup the OpenGL Function pointers
        // glewExperimental = GL_TRUE;
        // glewInit();
        
        // Define the viewport dimensions
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

        // Setup OpenGL options
        glEnable(GL_MULTISAMPLE); // 抗锯齿- 启动"多重采样"Enabled by default on some drivers, but not all so always enable to make sure
        glEnable(GL_DEPTH_TEST);

        // Setup and compile our shaders
        Shader shader("shaders/advanced.vs", "shaders/advanced.frag");

        #pragma region "object_initialization"
        // Set the object data (buffers, vertex attributes)
        GLfloat cubeVertices[] = {
            // Positions       
            -0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f, 
             0.5f,  0.5f, -0.5f, 
             0.5f,  0.5f, -0.5f,  
            -0.5f,  0.5f, -0.5f,  
            -0.5f, -0.5f, -0.5f, 

            -0.5f, -0.5f,  0.5f, 
             0.5f, -0.5f,  0.5f, 
             0.5f,  0.5f,  0.5f, 
             0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f,  0.5f, 
            -0.5f, -0.5f,  0.5f, 

            -0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f, -0.5f,  
            -0.5f, -0.5f, -0.5f,  
            -0.5f, -0.5f, -0.5f, 
            -0.5f, -0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f, 

             0.5f,  0.5f,  0.5f,  
             0.5f,  0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f,  0.5f,  
             0.5f,  0.5f,  0.5f,  

            -0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f,  
             0.5f, -0.5f,  0.5f, 
             0.5f, -0.5f,  0.5f, 
            -0.5f, -0.5f,  0.5f,  
            -0.5f, -0.5f, -0.5f,  

            -0.5f,  0.5f, -0.5f,  
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,  
             0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f, -0.5f
        };
        // Setup cube VAO
        GLuint cubeVAO, cubeVBO;
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        glBindVertexArray(cubeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glBindVertexArray(0);
        #pragma endregion

        // Game loop
        while(!glfwWindowShouldClose(window))
        {
            // Set frame time
            GLfloat currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // Check and call events
            glfwPollEvents();
            
            // Clear buffers
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Set transformation matrices
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f,1000.0f);
            glm::mat4 view = camera.GetViewMatrix();
            shader.use();
            shader.setMat4("projection", projection);
            shader.setMat4("view", view);
            shader.setMat4("model", glm::mat4());
            
            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);

            // Swap the buffers
            glfwSwapBuffers(window);
        }


        glfwTerminate();
        return 0;
    }
}
