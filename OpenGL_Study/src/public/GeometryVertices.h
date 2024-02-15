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
    }


    
}
