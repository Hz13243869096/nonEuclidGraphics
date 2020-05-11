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

public:
	Mesh();
	Mesh(std::string path);	// ��ʼ����ʱ�����Ĭ�ϲ�����������������ϵ�µ�ŷʽ����
	// ����obj�ͼ�������ͼƬ
	Mesh(std::string path, std::string texImagePath);	
	// ����obj����ʹ���ṩ������
	Mesh(std::string path, std::shared_ptr<Texture2D> pTex);	
	~Mesh();

	void LoadObj(std::string path);
	void Transform(vecf3 center, matf3 S, matf3 R);	//�任�������ParaCoord��

	void LoadMesh();				// ��OpenGL�м�����������
	void LoadTexture(std::string path, std::string type = "Albedo");
	//void ParaReset();
	void Draw(GLuint programID, const matf4& m2paraTransform);	// ����ɫ������

private:
	std::vector<std::string> SplitString(const std::string& s, const std::string& spliter);

public:
	/*  Mesh Data  */
	std::vector<Vertex> vertices;		//��
	std::vector<unsigned int> indices;	//��
	std::shared_ptr<Texture2D> AlbedoTexture;		//��ͼ

	/*  Render data  */
	unsigned int VAO = 0;
	unsigned int VBO = 0, EBO = 0;

private:
	std::vector<vecf3> positions;
	std::vector<vecf3> normals;
	std::vector<vecf2> texcoords;
};


inline Mesh::Mesh()
{
}

inline Mesh::Mesh(std::string path)
{
	LoadObj(path);
	LoadMesh();
}

inline Mesh::Mesh(std::string path, std::string texImagePath)
{
	LoadObj(path);
	LoadMesh();
	LoadTexture(texImagePath, "Albedo");
}

inline Mesh::Mesh(std::string path, std::shared_ptr<Texture2D> pTex)
{
	LoadObj(path);
	LoadMesh();
	AlbedoTexture = pTex;
}

inline Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}