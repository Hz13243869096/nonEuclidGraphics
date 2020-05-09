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
	namespace WorldExample
	{
		class WorldExampleBase
		{
		public:
			/*
			virtual void regularize_ref(vecf3& v) = 0;
			virtual vecf3 regularize(const vecf3& v) = 0;

			virtual vecf4 coord(const vecf3& v) = 0;
			virtual matf43 jacobi(const vecf3& v) = 0;
			virtual	matf3 metric(const vecf3& v) = 0;
			virtual tensorf333 gamma(const vecf3& v) = 0;
			*/
		};

		
		class Gaussian : public WorldExampleBase
		{
		public:
			static void regularize_ref(vecf3& u);

			static vecf3 regularize(const vecf3& u);

			static vecf4 coord(const vecf3& u);

			static matf43 jacobi(const vecf3& u);

			static matf3 metric(const vecf3& u);

			static tensorf333 gamma(const vecf3& u);
		};

		/*
		3�γ�����ռ䣨���ڲ�����ʾ���⣺����������㣩
		*/
		class HyperSphere : public WorldExampleBase
		{
		public:
			static void regularize_ref(vecf3& u);

			static vecf3 regularize(const vecf3& u);

			static vecf4 coord(const vecf3& u);

			static matf43 jacobi(const vecf3& u);

			static matf3 metric(const vecf3& u);

			static tensorf333 gamma(const vecf3& u);
		};

		/*
		ŷʽ�ռ䣺������ڲ���
		*/
		class Euclidean : WorldExampleBase
		{
		public:
			static void regularize_ref(vecf3& u);

			static vecf3 regularize(const vecf3& u);

			static vecf4 coord(const vecf3& u);

			static matf43 jacobi(const vecf3& u);

			static matf3 metric(const vecf3& u);

			static tensorf333 gamma(const vecf3& u);
		};
	}
	
}