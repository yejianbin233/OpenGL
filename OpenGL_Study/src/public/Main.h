#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_s.h>

#include <iostream>

#include "Camera.h"

// settings
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

namespace GlobalFuns
{
    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    // inline void processInput(GLFWwindow* window)
    // {
    //     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //         glfwSetWindowShouldClose(window, true);
    // }
    //
    // // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // // ---------------------------------------------------------------------------------------------
    // inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    // {
    //     // make sure the viewport matches the new window dimensions; note that width and 
    //     // height will be significantly larger than specified on retina displays.
    //     glViewport(0, 0, width, height);
    // }

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    inline void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }


    // glfw: whenever the mouse moves, this callback is called
    // -------------------------------------------------------
    inline void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }   

    // glfw: whenever the mouse scroll wheel scrolls, this callback is called
    // ----------------------------------------------------------------------
    inline void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        camera.ProcessMouseScroll(static_cast<float>(yoffset));
    }
}



class Main
{
public:
};
