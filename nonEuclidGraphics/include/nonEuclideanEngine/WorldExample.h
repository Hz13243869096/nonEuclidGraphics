#pragma once

/*
	�� WorldExpamle.h ���ṩ��һЩ������������������;
	ֱ��������� Example �᷽��ܶࡣ

	TODO
*/

#include <core/mat.h>
#include <core/func.h>
#include <core/geometry.h>

using namespace cgcore;

namespace nonEuc
{
	class WorldExample
	{
	public:
		virtual void regularize_ref(vecf3& v) = 0;
		virtual vecf3 regularize(const vecf3& v) = 0;

		virtual vecf4 coord(const vecf3& v) = 0;
		virtual matf43 jacobi(const vecf3& v) = 0;
		virtual	matf3 metric(const vecf3& v) = 0;
		virtual tensorf333 gamma(const vecf3& v) = 0;
	};


	/*
	3�γ�����ռ䣨���ڲ�����ʾ���⣺����������㣩
	*/
	class HyperSphere : WorldExample
	{
	public:
		void regularize_ref(vecf3& u);

		vecf3 regularize(const vecf3& u);

		vecf4 coord(const vecf3& u);

		matf43 jacobi(const vecf3& u);

		matf3 metric(const vecf3& u);

		tensorf333 gamma(const vecf3& u);
	};

}