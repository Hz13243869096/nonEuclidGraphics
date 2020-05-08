#pragma once

#include <GL/gl3w.h>            // Initialize with gl3wInit()
#include <GLFW/glfw3.h>

#include <core/mat.h>
#include <core/vec.h>

using namespace cgcore;

class Camera {
public:
	Camera();
	Camera(vecf3 position, matf3 S);
	~Camera();

	void UpdateDirection(vecf3 position, matf3 S);

public:
	vecf3 paraPos;		// ���������µ�λ��
	vecf3 Front;		// z������(��������)
	vecf3 Up;			// y������
	vecf3 Right;		// x������

	float yaw = -90.0f;	// ˮƽ��
	float pitch = 0.0f; // ������

private:
	float toRad(float degree){ return degree / 180 * 3.14159265f; }	
	//matf3 R;
};