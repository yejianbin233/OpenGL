#include "Main.h"

#include "Geometry/Triangle.h"
#include "Transform/Rotate.h"
#include "Transform/Scale.h"
#include "Transform/Translate.h"


// 创建窗口示例代码
int OpenGL_WindowTemplate()
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
    // -- 数据准备 --

    // -- 数据准备 --

    // -- 着色器（Shader） 设置 --


    // -- 着色器（Shader） 设置 --

    // render loop - 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        // input - 用户输入
        GlobalFuns::processInput(window);

        // render - --渲染指令--

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

int main()
{
    // return TriangleRendering::TriangleRenderingRun();
    // return TranslateRendering::TranslateRenderingRun();
    // return ScaleRendering::ScaleRenderingRun();
    return RotateRendering::RotateRenderingRun();
}