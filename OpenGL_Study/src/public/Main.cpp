#include "Main.h"

#include "AntiAliasing/AntiAliasing.h"
#include "Blending/Blending.h"
#include "Blending/BlendingTranslucent.h"
#include "Camera/Camera.h"
#include "CubeMap/Cubemap_Skybox_EnviromentMapping_Reflection.h"
#include "CubeMap/Cubemap_Skybox_EnviromentMapping_Reflection_Refract.h"
#include "CubeMap\Cubemap_Skybox.h"
#include "DepthTest/DepthTest.h"
#include "DepthTest/VisualDepthBuffer.h"
#include "FaceCulling/FaceCulling.h"
#include "Gamma/GammaCorrection.h"
#include "Gamma/GammaCorrectionFragmentShader.h"
#include "Geometry/Triangle.h"
#include "Geometry/Triangle3D.h"
#include "GeometryShader/GeometryShader.h"
#include "indice/Indice.h"
#include "Instancing/Instancing.h"
#include "Instancing/InstancingAsteroids.h"
#include "Interpolation/Interpolation.h"
#include "Lighting/PhongAndBlinnPhong.h"
#include "Lighting/StandardLighting.h"
#include "Lighting/StandardLighting_Dynamic.h"
#include "Lighting/StandardLighting_HalfLambert_BllinPhong.h"
#include "Lighting/StandardLighting_HalfLambert_BllinPhong_Dynamic.h"
#include "Lighting/StandardLighting_HalfLambert_BllinPhong_LightingMap.h"
#include "Lighting/LightingSource/StandardLighting_DirectionalLight.h"
#include "Lighting/LightingSource/StandardLighting_MultiLighting.h"
#include "Lighting/LightingSource/StandardLighting_PointLight.h"
#include "Lighting/LightingSource/StandardLighting_SpotLight.h"
#include "Lighting/LightingSource/StandardLighting_SpotLightSoftEdge.h"
#include "Lighting/Shadow/DepthTexture.h"
#include "Lighting/Shadow/PointLightingSourceShadowMapping.h"
#include "Lighting/Shadow/ShadowMapping.h"
#include "Lighting/Shadow/ShadowMapping_Bias.h"
#include "Model/Model.h"
#include "PostProcess/FrameBuffer.h"
#include "PostProcess/FrameBuffer_PostProcess_AntiphaseColor.h"
#include "PostProcess/FrameBuffer_PostProcess_Blur.h"
#include "PostProcess/FrameBuffer_PostProcess_EdgeDetect.h"
#include "PostProcess/FrameBuffer_PostProcess_Grayscale.h"
#include "PostProcess/FrameBuffer_PostProcess_Sharpen.h"
#include "StencilTest/StencilTest.h"
#include "Texture/MoreTexture.h"
#include "Texture/Texture.h"
#include "Texture/TextureBlendVertexColor.h"
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
    // return TriangleRendering::TriangleRenderingRun(); // 绘制三角形
    // return TranslateRendering::TranslateRenderingRun(); // 演示平移
    // return ScaleRendering::ScaleRenderingRun(); // 演示缩放
    // return RotateRendering::RotateRenderingRun(); // 演示旋转
    // return InterpolationRendering::InterpolationRenderingRun(); // 演示渲染流水线自动处理的插值
    // return IndiceRendering::IndiceRenderingRun(); // 演示顶点形状绘制索引
    // return Triangle3DRendering::Triangle3DRenderingRun(); // 演示 3D 三角形
    // return CameraRendering::CameraRenderingRun(); // 演示 摄像机操作
    // return TextureRendering::TextureRenderingRun(); // 演示 纹理采样
    // return TextureBlendVertexColorRendering::TextureBlendVertexColorRenderingRun(); // 演示 纹理采样 与顶点颜色混合
    // return MoreTextureRendering::MoreTextureRenderingRun(); // 演示 多个纹理采样混合
    // return StandardLightingRendering::StandardLightingRenderingRun(); // 演示 标准灯光模型（环境光 + 漫反射（兰伯特光照模型） + 高光反射（Phong 光照模型））
    // return StandardLightingDynamicRendering::StandardLightingDynamicRenderingRun(); // 光源位置动态改变，演示 标准灯光模型（环境光 + 漫反射（兰伯特光照模型） + 高光反射（Phong 光照模型））
    // return StandardLightingHalfLambertBllinPhongRendering::StandardLightingHalfLambertBllinPhongRenderingRun(); // 演示 标准灯光模型（环境光 + 漫反射（半兰伯特光照模型） + 高光反射（Blinn-Phong 光照模型））
    // return StandardLightingHalfLambertBllinPhongDynamicRendering::StandardLightingHalfLambertBllinPhongDynamicRenderingRun(); // 光源位置动态改变，演示 标准灯光模型（环境光 + 漫反射（半兰伯特光照模型） + 高光反射（Blinn-Phong 光照模型））
    // return StandardLightingHalfLambertBllinPhongLightingMapRendering::StandardLightingHalfLambertBllinPhongLightingMapRenderingRun(); // 演示 标准灯光模型（环境光 + 漫反射（半兰伯特光照模型） + 高光反射（Blinn-Phong 光照模型）） 再应用光照贴图（漫反射贴图 + 高光反射贴图）
    // return StandardLightingDirectionalLightRendering::StandardLightingDirectionalLightRenderingRun(); // 演示定向光源
    // return StandardLightingPointLightRendering::StandardLightingPointLightRenderingRun(); // 演示点光源
    // return StandardLightingSpotLightRendering::StandardLightingSpotLightRenderingRun(); // 演示聚光源
    // return StandardLightingSpotLightSoftEdgeRendering::StandardLightingSpotLightSoftEdgeRenderingRun(); // 演示聚光源并软化光源边缘
    // return StandardLightingMultiLightingRendering::StandardLightingMultiLightingRenderingRun(); // 多光源场景
    // return ModelRendering::ModelRenderingRun(); // 导入模型
    // return DepthTestRendering::DepthTestRenderingRun(); // 开启深度测试，深度测试相关设置
    // return VisualDepthBufferRendering::VisualDepthBufferRenderingRun(); // 深度测试可视化
    // return StencilTestRendering::StencilTestRenderingRun(); // 模板测试，绘制物体轮廓
    // return BlendingRendering::BlendingRenderingRun(); // 混合应用，丢弃贴图 Alpha 值小于特定值（<0.1）的片段
    // return BlendingTranslucentRendering::BlendingTranslucentRenderingRun(); // 混合应用，根据物体排序混合不透明物体
    // return FaceCullingRendering::FaceCullingRenderingRun(); // 面剔除
    // return FrameBufferRendering::FrameBufferRenderingRun(); // 帧缓冲，创建帧缓冲
    // return FrameBufferPostProcessAntiphaseColorRendering::FrameBufferPostProcessAntiphaseColorRenderingRun(); // 帧缓冲，后期处理，颜色反相
    // return FrameBufferPostProcessBlurRendering::FrameBufferPostProcessBlurRenderingRun(); // 帧缓冲，后期处理，模糊
    // return FrameBufferPostProcessEdgeDetectRendering::FrameBufferPostProcessEdgeDetectRenderingRun(); // 帧缓冲，后期处理，边缘检测
    // return FrameBufferPostProcessGrayscaleRendering::FrameBufferPostProcessGrayscaleRenderingRun(); // 帧缓冲，后期处理，灰度
    // return FrameBufferPostProcessSharpenRendering::FrameBufferPostProcessSharpenRenderingRun(); // 帧缓冲，后期处理，锐化
    // return CubeMapSkyboxRendering::CubeMapSkyboxRenderingRun(); // 使用立方体贴图（Cubemap），创建天空盒
    // return CubeMapSkyboxEnvironmentMappingRendering::CubeMapSkyboxEnvironmentMappingRenderingRun(); // 使用立方体贴图（Cubemap），环境映射 - 反射
    // return CubeMapSkyboxEnvironmentMappingRefractRendering::CubeMapSkyboxEnvironmentMappingRefractRenderingRun(); // 使用立方体贴图（Cubemap），环境映射 - 反射，折射
    // return GeometryShaderRendering::GeometryShaderRenderingRun(); // 几何着色器（Geometry Shader）
    // return InstancingRendering::InstancingRenderingRun(); // 实例化（Instancing）
    // return InstancingAsteroidsRendering::InstancingAsteroidsRenderingRun(); // 实例化（Instancing）小行星场景
    // return AntiAliasingRendering::AntiAliasingRenderingRun(); // 抗锯齿
    // return PhongAndBlinnPhongRendering::PhongAndBlinnPhongRenderingRun(); // 高级光照：Phong 和 Blinn-Phong 的对比
    // return GammaCorrectionRendering::GammaCorrectionRenderingRun(); // Gamma 矫正，使用 OpenGL 内置命令
    // return GammaCorrectionFragmentShaderRendering::GammaCorrectionFragmentShaderRenderingRun(); // Gamma 矫正，使用"FragmentShader（片元着色器）"

    // return DepthTextureRendering::DepthTextureRenderingRun(); // 阴影 - 深度贴图
    // return ShadowMappingRendering::ShadowMappingRenderingRun(); // 阴影 - 使用深度贴图渲染阴影
    // return ShadowMappingBiasRendering::ShadowMappingBiasRenderingRun(); // 阴影 - 使用深度贴图渲染阴影，改进阴影（使用"阴影偏移"解决阴影失真问题）

    return PointShadowMappingRendering::PointShadowMappingRenderingRun(); // 点光源阴影
}
