#pragma once

#include <type_traits>
#include <core/mat.h>
#include <core/func.h>
#include <core/Mesh.h>
namespace cgcore
{
	class Obj;
}

#include <core/Obj.h>

#include <nonEuclideanEngine/camera.h>
#include <nonEuclideanEngine/WorldExample.h>
#include <core/transform.h>

namespace nonEuc
{
	class Camera;

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
		Camera* camera = nullptr;

	public:

		World();

		//ʹ��һ��WorldExample����������
		template<typename TWorldExample>
		void SetWorldExample();

		~World();
		void AddObj(std::shared_ptr<Mesh> newMesh, vecf3 center, vecf3 scale, matf3 rotation);
	};

	template<typename TWorldExample>
	void World::SetWorldExample()
	{
		//��WorldExample��Ӧ������
		static_assert(std::is_base_of<WorldExample::WorldExampleBase, TWorldExample>::value);
		coord = TWorldExample::coord;
		jacobi = TWorldExample::jacobi;
		gamma = TWorldExample::gamma;
		regularize_ref = TWorldExample::regularize_ref;
		regularize = TWorldExample::regularize;
		metric = TWorldExample::metric;

		//��ʼ��Camera (��ʼ�����������޸�)
		delete camera;
		camera = new Camera({ 0.f, 0.f, 3.f }, *this);
	}

	inline World::~World()
	{
		delete camera;
	}
}

