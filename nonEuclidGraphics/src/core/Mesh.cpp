
#include<core/Mesh.h>


using namespace cgcore;


void Mesh::LoadObj(std::string path)
{
	std::ifstream objfile(path);
	if (!objfile) {
		std::cout << "ERROR::Mesh::LoadObj:" << std::endl
			<< "\t" << "open file (" << path << ") fail" << std::endl;
	}

	while (!objfile.eof())
	{
		std::string line;
		std::getline(objfile, line);
		if (line.empty() || line == "\n")
			continue;

		std::stringstream ss(line);
		std::string type;
		ss >> type;
		switch (type[0])
		{
		case 'v': {
			if (type.size() > 1)
			{
				switch (type[1])
				{
				case 'n': {
					vecf3 pos;
					ss >> pos[0];
					ss >> pos[1];
					ss >> pos[2];
					normals.push_back(pos);
				}
						break;
				case 't': {
					vecf2 pos;
					ss >> pos[0];
					ss >> pos[1];
					texcoords.push_back(pos);
				}
						break;
				default:
					break;
				}
			}
			else
			{
				vecf3 pos;
				ss >> pos[0];
				ss >> pos[1];
				ss >> pos[2];
				positions.push_back(pos);
			}
		}
				break;
		case 'f': {
			Face f;
			for (int i = 0; i < 3; i++)
			{
				std::string temp;
				ss >> temp;
				auto splitresult = SplitString(temp, "/");
				if (splitresult.size() >= 3)
				{
					// EBO�еĶ���������0��ʼ
					f.v_idx[i] = std::stoi(splitresult[0]) - 1;
					f.vt_idx[i] = std::stoi(splitresult[1]) - 1;
					f.vn_idx[i] = std::stoi(splitresult[2]) - 1;
				}
			}
			faces.push_back(f);
		}
				break;
		default:
			break;
		}
	}

	/*
	for (int i = 0; i < positions.size(); i++)
	{
		Vertex v;
		v.Position = positions[i];
		v.ParaCoord = positions[i];				// ������������ϵ��ŷ�������ʼ����������
		vertices.push_back(v);
	}
	if (normals.size() == vertices.size())
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			vertices[i].Normal = normals[i];
		}
	}
	//std::cout << vertices.size() << " " <<texcoords.size() << " " << std::endl;
	if (texcoords.size() >= vertices.size())
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			vertices[i].TexCoord = texcoords[i];
		}
	}
	*/
}

void Mesh::Transform(vecf3 center, matf3 S, matf3 R)
{
	for (int i = 0; i < positions.size(); i++)
	{
		positions[i] = matf3::dot(S, R).dot(positions[i]) + center;
	}
}

std::vector<std::string> Mesh::SplitString(const std::string& s, const std::string& spliter)
{
	std::string::size_type pos1, pos2;
	std::vector<std::string> v;
	pos2 = s.find(spliter);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + spliter.size();
		pos2 = s.find(spliter, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
	return v;
}

void Mesh::LoadMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	// vecf3��������������ƺ���һ��ָ�룬��̫����ֱ�ӽ�vertices���鴫��buffer����
	std::vector<float> vertice_data;
	for (size_t i = 0; i < faces.size(); i++)//����������
	{
		for (int j = 0; j < 3; j++)//�������������
		{
			// TODO:���Ҫ��������Ϣ����������ӣ�ע�⻹Ҫ�޸ĺ����glVertexAttribPointer

			for (int k = 0; k < 3; k++)//position
				vertice_data.push_back(positions[faces[i].v_idx[j]][k]);

			for (int k = 0; k < 2; k++)//texcoord
				vertice_data.push_back(texcoords[faces[i].v_idx[j]][k]);

			for (int k = 0; k < 3; k++)//normal
				vertice_data.push_back(normals[faces[i].v_idx[j]][k]);
		}
	}
	
	for (size_t i = 0; i < faces.size() * 3; i++)
	{
		indices.push_back(i);
	}

	GLsizei vdata_stride = 8 * sizeof(float);	//ÿ�������������ݵĴ�СΪ����

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertice_data.size() * sizeof(float), &vertice_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// ����Ҫ�����ݴ���OpenGL������׷�ӣ�

	glVertexAttribPointer(
		0,									// 0->paracoord,��������ɫ����������ȫ�ֲ�������
		3,									// 3��float�ĳ���
		GL_FLOAT,
		GL_FALSE,
		vdata_stride,						// ����
		(void*)0							// ��ʼλ��
	);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,									// 1->texcoord
		2,
		GL_FLOAT,
		GL_FALSE,
		vdata_stride,
		(void*)(3*sizeof(float))
	);
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(
		2,									// 2->normal
		3,
		GL_FLOAT,
		GL_FALSE,
		vdata_stride,
		(void*)(5 * sizeof(float))
	);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Mesh::LoadTexture(std::string path, std::string type)
{
	if (type == "Albedo")
	{
		AlbedoTexture = std::make_shared<Texture2D>();
		AlbedoTexture->Load(path);
		AlbedoTexture->SetTextureImage();
	}
	else
	{
		std::cout << "Mesh::LoadTexture : Inavailable texutre type" <<std::endl;
	}
}

void Mesh::Draw(GLuint programID, const matf4& m2paraTransform)
{
	// TODO:����������ͼ DOING
	// TODO:�����������


	// draw
	glUseProgram(programID);

	GLint Location = glGetUniformLocation(programID, "M");
	glUniformMatrix4fv(Location, 1, GL_TRUE, m2paraTransform.data);
	glActiveTexture(GL_TEXTURE0);
	AlbedoTexture->Bind();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	AlbedoTexture->BindReset();
}