#pragma once

#include <core/mat.h>
#include <core/func.h>

namespace nonEuc
{
	class World
	{
	public:
		//���������ռ䣨��ά���Σ�������

		//��ά������������->��ά�ռ��ӳ��(��һ���õ�)
		Func3to4 coord;
		//�ȹ����
		Func3to33 metric;
		//Jacobi����
		Func3to43 jacobi;
		//������Christoffel�Ǻ�
		Func3to333 gamma;
	
		
	};
}