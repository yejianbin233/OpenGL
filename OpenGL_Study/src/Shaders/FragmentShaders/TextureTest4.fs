#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float mixValue;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2; 

void main()
{
	// linearly interpolate between both textures
	// 可通过 minValue 控制混合结果
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
}