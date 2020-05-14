#pragma once

#include <core/vec.h>

/*
	Ϊ�˷��㣬������ʱֻ��һ��Primitive�� Triangle���������ı���Sphere, Square...��
*/

namespace cgcore
{
	//������
	struct Triangle
	{
		// pos[0]��0�ŵ�Ĳ������꣬pos[1]��pos[2] ����Բ������� 
		vecf3 pos[3];
		// ����
		vecf3 normal;
		// ��������
		vecf2 uv[3];
		// ��world��������������
		size_t obj_id;
		// �ڶ�Ӧobj����id
		size_t face_id;
	};
}
