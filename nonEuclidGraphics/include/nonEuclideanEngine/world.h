#pragma once

#include <type_traits>
#include <core/mat.h>
#include <core/func.h>
#include <core/Mesh.h>

#include <core/Obj.h>
#include <core/Object.h>

#include <core/AreaLight.h>

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
		//Func3i regularize_ref;
		//Func3ito3 regularize;
		Func3ijk regularize_ref;
		Func3ijkto3 regularize;
		
		//�ȹ����
		Func3to33 metric;
		//������Christoffel�Ǻ�
		Func3to333 gamma;
	
		std::vector<std::shared_ptr<Obj>> objectPtrs;
		Camera camera;


	public:

		World();

		// ʹ��һ��WorldExample����������
		template<typename TWorldExample>
		void SetWorldExample();

		~World();
		// ����������壬��ָ��center, scale, rotation
		void AddObj(std::shared_ptr<Mesh> newMesh, vecf3 center, vecf3 scale, vecf3 rotation);
		//
		void AddAreaLight(vecf3 position, vecf3 edge1, vecf3 edge2, float intensity, rgbf color);
		// ����OpenGL�Ĺ�Դ
		void SetUniformLight(GLuint programID);
		// ��ȡ����������������, ����Object��AreaLight
		std::vector<Triangle> GetTriangles();

	private:

		
	};

	template<typename TWorldExample>
	void World::SetWorldExample()
	{
		//��WorldExample��Ӧ������
		static_assert(std::is_base_of<WorldExample::WorldExampleBase, TWorldExample>::value);
		gamma = TWorldExample::gamma;
		regularize_ref = TWorldExample::regularize_ref;
		regularize = TWorldExample::regularize;
		metric = TWorldExample::metric;

		//��ʼ��Camera (��ʼ�����������޸�)
		camera = Camera({ 0.f , PI<float>/2.f, PI<float>/2.f}, this);

	}

	inline World::~World()
	{

	}
}

