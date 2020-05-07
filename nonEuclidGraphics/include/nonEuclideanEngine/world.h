#pragma once

#include <core/mat.h>
#include <core/func.h>
#include <core/Mesh.h>

namespace nonEuc
{
	class World
	{
	public:
		//���������ռ䣨��ά���Σ�������

		//��ά������������->��ά�ռ��ӳ��(��һ���õ�)
		Func3to4 coord;
		//�ȹ����
		Func3to33 metric;
		//Jacobi����
		Func3to43 jacobi;
		//������Christoffel�Ǻ�
		Func3to333 gamma;
	
		std::vector<Mesh *> objectPtrs;

	public:
		World();
		~World();
		void AddMesh(Mesh * newMesh);
	};

	inline World::World()
	{

	}

	inline World::~World()
	{

	}

	inline void World::AddMesh(Mesh* newMesh)
	{
		// TODO:������Ҫ����newMesh�Ĳ�������
		objectPtrs.push_back(newMesh);
	}
}

