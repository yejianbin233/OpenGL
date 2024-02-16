#pragma once



namespace geometry_vertices_data {
    namespace triangles
    {
        // 模板
        // float simple[] = {
        //          // positions          // texture coords
        //          0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
        //          0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        //         -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        //         -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
        //     };

        float simple[] = {
            -1.0f, -1.0f, 0.0f, // 屏幕左下角
            1.0f, -1.0f, 0.0f, // 屏幕右下角
            0.0f, 1.0f, 0.0f,
       };

        float small[] = {
            -0.4f, -0.4f, 0.0f, // 屏幕左下角
            0.4f, -0.4f, 0.0f, // 屏幕右下角
            0.0f, 0.4f, 0.0f,
       };

        float simple_3d[] = {
            -1.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        };
        unsigned int indices_simple_3d[] = { 
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2 
        };
    }

    namespace square
    {
        float simpleWithVertexColor[] = {
            //     ---- 位置 ----       ---- 颜色 ----
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
           -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
           -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
       };

        float simpleWithTexCoord[] = {
            //     ---- 位置 ----       ---- 纹理坐标 ----
            0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left
       };

        float simpleWithVertexColorTexCoord[] = {
            // 位置          // 颜色           // 纹理坐标
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
           -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
           -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
       };

        unsigned int indices[] = {  
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
    }
    
}
