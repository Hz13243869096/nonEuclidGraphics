#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <core/vec.h>
#include <core/mat.h>


#include <GL/gl3w.h>            // Initialize with gl3wInit()
#include <GLFW/glfw3.h>
#include <core/Texture2D.h>
#include <core/Material.h>

class Mesh
{
	struct Vertex {
		// position
		vecf3 Position;
		// Parameter coordinates
		vecf3 ParaCoord;
		// normal
		vecf3 Normal;
		// texCoord
		vecf2 TexCoord;
		// TBN
		matf3 TBN;
	};

	struct Face
	{
		//position index
		unsigned int v_idx[3];
		//texture index
		unsigned int vt_idx[3];
		//normal index
		unsigned int vn_idx[3];
	};

public:
	Mesh();
	//Mesh(std::string path, Material::MaterialType mtype = Material::MaterialType::DEFAULT);	// ��ʼ����ʱ�����Ĭ�ϲ�����������������ϵ�µ�ŷʽ����
	// ����obj�ͼ�������ͼƬ
	Mesh(std::string path, std::string texImagePath, Material::MaterialType mtype = Material::MaterialType::DEFAULT);
	// ����obj����ʹ���ṩ������
	Mesh(std::string path, std::shared_ptr<Texture2D> pTex, Material::MaterialType mtype = Material::MaterialType::DEFAULT);
	~Mesh();

	void LoadObj(std::string path);

	void LoadMesh();				// ��OpenGL�м�����������
	void LoadTexture(std::string path, std::string type = "Albedo");
	//void ParaReset();
	void Draw(GLuint programID, const matf4& m2paraTransform);	// ����ɫ������

private:
	std::vector<std::string> SplitString(const std::string& s, const std::string& spliter);

public:
	/*  Mesh Data  */

	std::vector<vecf3> positions;
	std::vector<vecf3> normals;
	std::vector<vecf2> texcoords;

	std::vector<unsigned int> indices;//������OpenGL

	//std::vector<Vertex> vertices;		//��
	std::vector<Face> faces;	//��
	std::shared_ptr<Texture2D> AlbedoTexture;		//��ͼ
	Material material;


	/*  Render data  */
	unsigned int VAO = 0;
	unsigned int VBO = 0, EBO = 0;

private:
	
};


inline Mesh::Mesh()
{
}

/*inline Mesh::Mesh(std::string path, Material::MaterialType mtype)
{
	LoadObj(path);
	LoadMesh();
	material = Material(mtype);
}*/

inline Mesh::Mesh(std::string path, std::string texImagePath, Material::MaterialType mtype)
{
	LoadObj(path);
	LoadMesh();
	LoadTexture(texImagePath, "Albedo");
	material = Material(mtype);
}

inline Mesh::Mesh(std::string path, std::shared_ptr<Texture2D> pTex, Material::MaterialType mtype)
{
	LoadObj(path);
	LoadMesh();
	AlbedoTexture = pTex;
	material = Material(mtype);
}

inline Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}