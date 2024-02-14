//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
//
//#include <shader_s.h>
//
//#include <iostream>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//float mixValue = 0.2f;
//
//int main()
//{
//    // glfw: initialize and configure - ��ʼ��������
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // OpenGL ���汾
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // OpenGL �ΰ汾
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ����ģʽ
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation - ���ڴ���
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    // ��������
//    glfwMakeContextCurrent(window);
//    // ���ڳߴ�����ص�������
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // glad: load all OpenGL function pointers - ʹ�� "Glad" ����� OpenGL ����
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // build and compile our shader zprogram
//    // ------------------------------------
//    Shader ourShader("D:\\OpenGL\\OpenGL_Study\\src\\Shaders\\VertexShaders\\TextureTest.vs", "D:\\OpenGL\\OpenGL_Study\\src\\Shaders\\FragmentShaders\\TextureTest4.fs");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    // ������������ - ��Ϊ��������
//    /*
//    OpenGL���Ǽ򵥵ذ����е�3D����任Ϊ��Ļ�ϵ�2D���أ�OpenGL����3D������3���ᣨx��y��z����-1.0��1.0�ķ�Χ��ʱ�Ŵ�������
//    �����������Χ�ڵ����������׼���豸����(Normalized Device Coordinates)���˷�Χ�ڵ�����������ʾ����Ļ�ϣ��������Χ����������򲻻���ʾ����
//    */
//    float vertices[] = {
//        // positions          // colors           // texture coords
//         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
//         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
//    };
//
//    // ����������
//    unsigned int indices[] = {
//        0, 1, 3, // first triangle
//        1, 2, 3  // second triangle
//    };
//
//    // OpenGL ����
//    /*
//    ����������� - VAO��Vertex Array Object�� - �����������(Vertex Array Object, VAO)�����񶥵㻺������������󶨣��κ����Ķ������Ե��ö��ᴢ�������VAO�С�
//
//
//    ���㻺����� - VBO��Vertex Buffer Object�� - ͨ�����㻺�����(Vertex Buffer Objects, VBO)���������ǵĶ������ݵ��ڴ棬������ GPU�ڴ棨ͨ������Ϊ�Դ棩�д���������㣨ʹ����Щ�������ĺô������ǿ���һ���Եķ���һ�������ݵ��Կ��ϣ�������ÿ�����㷢��һ�Ρ�����
//    ���㻺�����Ļ��������� GL_ARRAY_BUFFER��
//
//    Ԫ�ػ������ - EBO��Element Buffer Object ������������� Index Buffer Object��IBO��
//    */
//    unsigned int VBO, VAO, EBO;
//
//    // ���� OpenGL ����
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    // �� OpenGL ����
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//
//    // ���ö������� - �Ѷ������鸴�Ƶ������й� OpenGL ʹ��
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    // ���ö�������ָ��
//    // position attribute - ����λ������
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // color attribute - ������ɫ����
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    // texture coord attribute - ����������������
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//
//    // load and create a texture  - ����������������
//    // -------------------------
//    unsigned int texture1, texture2;
//    // texture 1
//    // ---------
//    glGenTextures(1, &texture1);
//    glBindTexture(GL_TEXTURE_2D, texture1);
//    // set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // load image, create texture and generate mipmaps
//    int width, height, nrChannels;
//
//    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis. - ��תͼ��� Y �ᣬʹ���� OpenGL ��ƥ��
//    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
//    unsigned char* data = stbi_load("D:\\OpenGL\\OpenGL_Study\\src\\Image\\Resources\\container.jpg", &width, &height, &nrChannels, 0);
//
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D); // ���� Minmap
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//
//    // texture 2
//    // ---------
//    glGenTextures(1, &texture2);
//    glBindTexture(GL_TEXTURE_2D, texture2);
//    // set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // load image, create texture and generate mipmaps
//    data = stbi_load("D:\\OpenGL\\OpenGL_Study\\src\\Image\\Resources\\awesomeface.png", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D); // ���� Minmap
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//
//    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//    // -------------------------------------------------------------------------------------------
//    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
//
//    // ���ֲ�ͬ�ķ�ʽ�������������
//    // either set it manually like so:
//    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
//    // or set it via the texture class
//    ourShader.setInt("texture2", 1);
//
//
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // bind textures on corresponding texture units - �����ĸ� uniform ��������Ӧ�ĸ�����Ԫ
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture1);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2);
//
//        // render container
//        ourShader.setFloat("mixValue", mixValue);
//        ourShader.use();
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    // �������룬ʹ�� ���¼�ͷ ����  mixValue ֵ
//    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
//    {
//        mixValue += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
//        if (mixValue >= 1.0f)
//            mixValue = 1.0f;
//    }
//    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
//    {
//        mixValue -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
//        if (mixValue <= 0.0f)
//            mixValue = 0.0f;
//    }
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}