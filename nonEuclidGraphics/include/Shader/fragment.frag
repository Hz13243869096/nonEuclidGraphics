#version 330 core


uniform sampler2D AlbedoTexture;

in vec2 TexCoord;
// Ouput data
out vec3 color;

void main()
{
	//�����ټӹ�Դ������

	
	// Output color = red 
	color = texture(AlbedoTexture, TexCoord).rgb;
}
