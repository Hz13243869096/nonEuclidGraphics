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
		//���������λ�ã�paraCoord��
		vecf3 pos[3];
		//��world��������������
		size_t obj_id;
		//��������Ķ����ţ�����ǹ�Դ�Ļ���0, 1, 2 ���ɣ�
		size_t idx[3];
	};
}
