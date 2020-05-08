#pragma once


#include <core/mat.h>
#include <core/func.h>
#include <core/Mesh.h>
#include <core/Obj.h>
#include <nonEuclideanEngine/camera.h>

namespace nonEuc
{
	class World
	{
	public:
		//���������ռ䣨��ά���Σ�������

		//�淶�����꣨����ÿ�����������Ψһ��
		Func3 regularize_ref;
		Func3to3 regularize;
		
		//��ά������������->��ά�ռ��ӳ��(��һ���õ�)
		Func3to4 coord;
		//�ȹ����
		Func3to33 metric;
		//Jacobi����(��һ���õ�)
		Func3to43 jacobi;
		//������Christoffel�Ǻ�
		Func3to333 gamma;
	
		std::vector<std::shared_ptr<Obj>> objectPtrs;
		Camera camera;

	public:
		World();
		~World();
		void AddObj(std::shared_ptr<Mesh> newMesh, vecf3 center, matf3 rotation);
	};

	inline World::World()
	{
		camera = Camera(cgcore::vecf3{0.0f, 0.0f, -10.0f}, cgcore::matf3::Identity());
	}

	inline World::~World()
	{

	}
}

