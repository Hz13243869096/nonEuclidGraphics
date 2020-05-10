#pragma once

#include <GL/gl3w.h>            // Initialize with gl3wInit()
#include <GLFW/glfw3.h>

#include <core/mat.h>
#include <core/vec.h>
#include <core/transform.h>
#include <core/geometry.h>

namespace nonEuc
{
	class World;
	class Camera;
}

#include <nonEuclideanEngine/world.h>

using namespace cgcore;

namespace nonEuc
{


	class Camera {
	public:
		Camera(vecf3 position, nonEuc::World& _world);
		~Camera();

		void ResetCamera(vecf3 position, float yaw, float pitch);
		void UpdateDirection(float dyaw, float dpitch);
		void UpdatePosition(vecf3 du);
		matf4 GetView();

	public:
		nonEuc::World& world;	//����������ã���camera�����Լ�ȥ����S��G��ʡ�����Ǵ��ݣ�

		vecf3 paraPos;		// ���������µ�λ��
		//vecf3 Front;		// z������(��������)
		//vecf3 Up;			// y������
		//vecf3 Right;		// x������

		matf3 Rotation;		// ��ת����	
		matf3 T;		// λ�þ���	T = (Right, Up, Front)^T = (S * R)^T

	private:
		float toRad(float degree) { return degree / 180 * PI<float>; }
	};
}
