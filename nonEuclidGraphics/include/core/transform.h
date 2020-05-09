#pragma once

#include <core/mat.h>
#include <core/tensor.h>

namespace cgcore
{
	/*
	�����ṩһЩ�任�ĺ���
	1. ʩ����������(ģ��)
	template<typename T, size_t NRow, size_t NRow> 
		mat<T, NRow, NRow> SchmidtOrthogonalize(const mat<T, NRow, NRow>& metric);

	2. ƽ������
		vecf3 Translate(const matf3& g, const tensorf333& gamma, vecf3 du, vecf3 v)

	3. ƽ�Ƶ���ת���� TODO
		void Translate(const matf3& g, const tensorf333& gamma, vecf3 du, matf3 R)

	*/



	//ʩ���������� (metric : ��������) // UNTESTED (���Ǹ�ģ�庯��)
	template<typename T, size_t NRow>
	mat<T, NRow, NRow> SchmidtOrthogonalize(const mat<T, NRow, NRow>& metric)
	{
		mat<T, NRow, NRow> S;
		S.fill(static_cast<T>(0));
		vec<T, NRow> beta(static_cast<T>(0));
		for (size_t i = 0; i < NRow; i++)
		{
			//���� beta_i = S(1, i)r_1 + ... + S(m, i)r_m
			beta[i] = static_cast<T>(1);
			for (size_t l = 0; l < NRow; l++)
				for (size_t j = 0; j < i; j++)
					for (size_t k = 0; k < NRow; k++)
						beta[l] += S(k, j) * metric(i, k) * S(l, j);
			T beta_norm = sqrt(metric.dot_s(beta, beta));
			for (size_t l = 0; l < NRow; l++)
				S(l, i) = beta[l] / beta_norm;
		}
		return S;
	}
	
	//����Perspective����
	template<typename T>
	mat<T, 4, 4> Perspective(T fovY, T aspect, T zNear, T zFar) {
		assert(fovY > 0 && aspect > 0 && zNear >= 0 && zFar > zNear);

		T tanHalfFovY = std::tan(fovY / static_cast<T>(2));
		float cotHalfFovY = 1 / tanHalfFovY;

		T m00 = cotHalfFovY / aspect;
		T m11 = cotHalfFovY;
		T m22 = (zFar + zNear) / (zNear - zFar);
		T m23 = (2 * zFar * zNear) / (zNear - zFar);

		return mat<T, 4, 4>{
				m00, 0, 0, 0,
				0, m11, 0, 0,
				0, 0, m22, m23,
				0, 0, -1, 0,
		};
	}

}