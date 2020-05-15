#pragma once


//FAST-BVH
#include <FastBVH.h>

#include <core/rgb.h>
#include <nonEuclideanEngine/world.h>

#include <core/primitive.h>
namespace nonEuc
{



	class RayTracer
	{
	public:
		RayTracer() {}

		RayTracer(World* _world);

		~RayTracer()
		{
			delete bvh;
		}

		World* world = nullptr;
		
		FastBVH::BVH<float, Triangle>* bvh = nullptr;

		std::vector<Triangle> triangles;		//���ǵ����� primitive ���� Triangle��world�е�����obj/area/light�������ζ�ͳһ�ŵ�triangles��

		rgbf background_color;

		float decay_distance;							//˥��ϵ��

		float distance_limit;

		void SetWorld(World* _world);
		void SetParameter(float _distance_limit, float _decay_distance, rgbf _background_color);
		// ����world�е����������Σ�����BVH
		void BuildBVH();
		
		// ��Ⱦ���ι�ϵ
		cv::Mat RenderTracing(float fov, float aspect, int width);

	private:
		




		//���һ�����ߵ���ɫ��
		//ray:���߼��䷽��, distance:�������߾��루���뷢��Ϊֹ��, times ���߷���Ĵ���
		rgbf shader(FastBVH::Ray<float> ray, float distance, int times);
		rgbf tracer(FastBVH::Ray<float> ray, FastBVH::Traverser<float, Triangle, Intersector>& traverser);
	};
}