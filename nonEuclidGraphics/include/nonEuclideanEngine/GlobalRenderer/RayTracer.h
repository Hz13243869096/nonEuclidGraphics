#pragma once


//FAST-BVH
#include <FastBVH/BVH.h>

#include <core/rgb.h>
#include <nonEuclideanEngine/world.h>

#include <core/primitive.h>
namespace nonEuc
{



	class RayTracer
	{
	public:
		World& world;
		
		FastBVH::BVH<float, Triangle> bvh;

		std::vector<Triangle> triangles;		//���ǵ����� primitive ���� Triangle��world�е�����obj/area/light�������ζ�ͳһ�ŵ�triangles��

		float decay;							//˥��ϵ��

	private:
		
		// ����world�е����������Σ�����BVH
		void BuildBVH();

		//���һ�����ߵ���ɫ��
		//ray:���߼��䷽��, distance:�������߾��루���뷢��Ϊֹ��, times ���߷���Ĵ���
		rgbf shader(FastBVH::Ray<float> ray, float distance, int times);
	};
}