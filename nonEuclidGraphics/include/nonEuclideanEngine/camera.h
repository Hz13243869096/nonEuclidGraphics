#pragma once

#include <GL/gl3w.h>            // Initialize with gl3wInit()
#include <GLFW/glfw3.h>

#include <core/mat.h>
#include <core/vec.h>
#include <core/transform.h>
#include <core/geometry.h>

using namespace cgcore;

class Camera {
public:
	Camera();
	Camera(vecf3 position, matf3 S);
	~Camera();

	void UpdateDirection(vecf3 position, matf3 S);
	void UpdatePosition(const tensorf333& gamma, vecf3 du, matf3 &G, matf3 &S1, matf3 &S2);
	matf4 GetView(matf3 G);

public:
	vecf3 paraPos;		// ���������µ�λ��
	//vecf3 Front;		// z������(��������)
	//vecf3 Up;			// y������
	//vecf3 Right;		// x������

	float yaw = -90.0f;	// ˮƽ��
	float pitch = 0.0f; // ������

	matf3 Rotation;		// ��ת����	
	matf3 Position;		// λ�þ���	(Right, Up, Front) = S * R

private:
	float toRad(float degree){ return degree / 180 * PI<float>; }	
};