//#include <glad/glad.h>
//#include <glfw/glfw3.h>
//
//#define stb_image_implementation
//#include <stb_image.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <shader_s.h>
//
//#include <iostream>
//
//void framebuffer_size_callback(glfwwindow* window, int width, int height);
//void processinput(glfwwindow* window);
//
//// settings
//const unsigned int scr_width = 800;
//const unsigned int scr_height = 600;
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwinit();
//    glfwwindowhint(glfw_context_version_major, 3);
//    glfwwindowhint(glfw_context_version_minor, 3);
//    glfwwindowhint(glfw_opengl_profile, glfw_opengl_core_profile);
//
//#ifdef __apple__
//    glfwwindowhint(glfw_opengl_forward_compat, gl_true);
//#endif
//
//    // glfw window creation
//    // --------------------
//    glfwwindow* window = glfwcreatewindow(scr_width, scr_height, "learnopengl", null, null);
//    if (window == null)
//    {
//        std::cout << "failed to create glfw window" << std::endl;
//        glfwterminate();
//        return -1;
//    }
//    glfwmakecontextcurrent(window);
//    glfwsetframebuffersizecallback(window, framebuffer_size_callback);
//
//    // glad: load all opengl function pointers
//    // ---------------------------------------
//    if (!gladloadglloader((gladloadproc)glfwgetprocaddress))
//    {
//        std::cout << "failed to initialize glad" << std::endl;
//        return -1;
//    }
//
//    // build and compile our shader zprogram
//    // ------------------------------------
//    shader ourshader("d:\\opengl\\opengl_study\\src\\shaders\\vertexshaders\\transformations.vs", "d:\\opengl\\opengl_study\\src\\shaders\\fragmentshaders\\transformations.fs");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float vertices[] = {
//        // positions          // texture coords
//         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
//         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
//        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
//    };
//    unsigned int indices[] = {
//        0, 1, 3, // first triangle
//        1, 2, 3  // second triangle
//    };
//    unsigned int vbo, vao, ebo;
//    glgenvertexarrays(1, &vao);
//    glgenbuffers(1, &vbo);
//    glgenbuffers(1, &ebo);
//
//    glbindvertexarray(vao);
//
//    glbindbuffer(gl_array_buffer, vbo);
//    glbufferdata(gl_array_buffer, sizeof(vertices), vertices, gl_static_draw);
//
//    glbindbuffer(gl_element_array_buffer, ebo);
//    glbufferdata(gl_element_array_buffer, sizeof(indices), indices, gl_static_draw);
//
//    // position attribute
//    glvertexattribpointer(0, 3, gl_float, gl_false, 5 * sizeof(float), (void*)0);
//    glenablevertexattribarray(0);
//    // texture coord attribute
//    glvertexattribpointer(1, 2, gl_float, gl_false, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glenablevertexattribarray(1);
//
//
//    // load and create a texture 
//    // -------------------------
//    unsigned int texture1, texture2;
//    // texture 1
//    // ---------
//    glgentextures(1, &texture1);
//    glbindtexture(gl_texture_2d, texture1);
//    // set the texture wrapping parameters
//    gltexparameteri(gl_texture_2d, gl_texture_wrap_s, gl_repeat);
//    gltexparameteri(gl_texture_2d, gl_texture_wrap_t, gl_repeat);
//    // set texture filtering parameters
//    gltexparameteri(gl_texture_2d, gl_texture_min_filter, gl_linear);
//    gltexparameteri(gl_texture_2d, gl_texture_mag_filter, gl_linear);
//    // load image, create texture and generate mipmaps
//    int width, height, nrchannels;
//    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//    unsigned char* data = stbi_load("d:\\opengl\\opengl_study\\src\\image\\resources\\container.jpg", &width, &height, &nrchannels, 0);
//    if (data)
//    {
//        glteximage2d(gl_texture_2d, 0, gl_rgb, width, height, 0, gl_rgb, gl_unsigned_byte, data);
//        glgeneratemipmap(gl_texture_2d);
//    }
//    else
//    {
//        std::cout << "failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//    // texture 2
//    // ---------
//    glgentextures(1, &texture2);
//    glbindtexture(gl_texture_2d, texture2);
//    // set the texture wrapping parameters
//    gltexparameteri(gl_texture_2d, gl_texture_wrap_s, gl_repeat);
//    gltexparameteri(gl_texture_2d, gl_texture_wrap_t, gl_repeat);
//    // set texture filtering parameters
//    gltexparameteri(gl_texture_2d, gl_texture_min_filter, gl_linear);
//    gltexparameteri(gl_texture_2d, gl_texture_mag_filter, gl_linear);
//    // load image, create texture and generate mipmaps
//    data = stbi_load("d:\\opengl\\opengl_study\\src\\image\\resources\\awesomeface.png", &width, &height, &nrchannels, 0);
//    if (data)
//    {
//        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell opengl the data type is of gl_rgba
//        glteximage2d(gl_texture_2d, 0, gl_rgb, width, height, 0, gl_rgba, gl_unsigned_byte, data);
//        glgeneratemipmap(gl_texture_2d);
//    }
//    else
//    {
//        std::cout << "failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//
//    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//    // -------------------------------------------------------------------------------------------
//    ourshader.use();
//    ourshader.setint("texture1", 0);
//    ourshader.setint("texture2", 1);
//
//
//    // render loop
//    // -----------
//    while (!glfwwindowshouldclose(window))
//    {
//        // input
//        // -----
//        processinput(window);
//
//        // render
//        // ------
//        glclearcolor(0.2f, 0.3f, 0.3f, 1.0f);
//        glclear(gl_color_buffer_bit);
//
//        // bind textures on corresponding texture units
//        glactivetexture(gl_texture0);
//        glbindtexture(gl_texture_2d, texture1);
//        glactivetexture(gl_texture1);
//        glbindtexture(gl_texture_2d, texture2);
//
//        // create transformations
//        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//        transform = glm::rotate(transform, (float)glfwgettime(), glm::vec3(0.0f, 0.0f, 1.0f));
//
//        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
//
//        // get matrix's uniform location and set matrix
//        ourshader.use();
//        unsigned int transformloc = glgetuniformlocation(ourshader.id, "transform");
//        gluniformmatrix4fv(transformloc, 1, gl_false, glm::value_ptr(transform));
//
//        // render container
//        glbindvertexarray(vao);
//        gldrawelements(gl_triangles, 6, gl_unsigned_int, 0);
//
//        // glfw: swap buffers and poll io events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwswapbuffers(window);
//        glfwpollevents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    gldeletevertexarrays(1, &vao);
//    gldeletebuffers(1, &vbo);
//    gldeletebuffers(1, &ebo);
//
//    // glfw: terminate, clearing all previously allocated glfw resources.
//    // ------------------------------------------------------------------
//    glfwterminate();
//    return 0;
//}
//
//// process all input: query glfw whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processinput(glfwwindow* window)
//{
//    if (glfwgetkey(window, glfw_key_escape) == glfw_press)
//        glfwsetwindowshouldclose(window, true);
//}
//
//// glfw: whenever the window size changed (by os or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(glfwwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glviewport(0, 0, width, height);
//}