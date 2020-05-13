#version 330 core


uniform sampler2D AlbedoTexture;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform mat3 G;

in vec2 TexCoord;
in vec3 SRnormal;
in vec3 WorldPos;
// Ouput data
out vec3 color;

vec3 G_normalize(vec3 v)
{
	return v / sqrt(dot(v, G * v));
}

void main()
{
	//�����ټӹ�Դ������
	// ������
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	// ������
	vec3 lightDir = G_normalize(lightPos - WorldPos);
	float diff = max(dot(SRnormal, G * lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// �߹�
	float shininess =100;
	float specularStrength = 0.8;
	vec3 viewDir = G_normalize(viewPos - WorldPos);
	//vec3 reflectDir = reflect(-lightDir, SRnormal);
	vec3 reflectDir = 2 * dot(lightDir, G * SRnormal) * G_normalize(SRnormal) - lightDir;
	float spec = pow(max(dot(viewDir, G * reflectDir), 0.0), shininess);
	vec3 specular = specularStrength * spec * lightColor;
	
	// Output color
	vec3 objColor = texture(AlbedoTexture, TexCoord).rgb;
	color = objColor * (ambient + diffuse + specular);
}
