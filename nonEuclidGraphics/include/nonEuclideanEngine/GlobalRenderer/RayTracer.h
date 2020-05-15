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
		//RayTracer();
		//~RayTracer() {}

		//void Init(std::shared_ptr<World> _world) { world = _world; BuildBVH(); }
		void Run(float fov, float aspect, int width);

	public:
		std::shared_ptr<World> world;
		
		FastBVH::BVH<float, Triangle> bvh;

		std::vector<Triangle> triangles;		//���ǵ����� primitive ���� Triangle��world�е�����obj/area/light�������ζ�ͳһ�ŵ�triangles��

		rgbf background_color;

		float decay_distance;							//˥��ϵ��

		float distance_limit;
	private:
		
		// ����world�е����������Σ�����BVH
		void BuildBVH();

		cv::Mat RenderTracing(float fov, float aspect, int width);

		//���һ�����ߵ���ɫ��
		//ray:���߼��䷽��, distance:�������߾��루���뷢��Ϊֹ��, times ���߷���Ĵ���
		rgbf shader(FastBVH::Ray<float> ray, float distance, int times);
		rgbf tracer(FastBVH::Ray<float> ray, FastBVH::Traverser<float, Triangle, Intersector>& traverser);
	};
}