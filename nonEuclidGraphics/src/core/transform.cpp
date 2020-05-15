#include <core/transform.h>


vecf3 cgcore::Translate(const tensorf333& gamma, vecf3 du, vecf3 v)
{
	vecf3 dv;
	for (size_t i = 0; i < 3; i++)
	{
		dv[i] = 0.f;
		for (size_t k = 0; k < 3; k++)
			for (size_t l = 0; l < 3; l++)
				dv[i] -= gamma(i, k, l) * du[k] * v[l];
	}
	return v + dv;
}

matf3 cgcore::Translate(const matf3& S_u1, const matf3& S_u2, const tensorf333& gamma, vecf3 du, const matf3& R)
{
	// I������������������������SRI = SR �õ������������������Ĳ���������ʽ
	matf3 SR_1 = matf3::dot(S_u1, R);
	matf3 dSR(0.f);

	//��SR��ÿ����������ƽ��
	for (size_t j = 0; j < 3; j++)	//��ÿ��������
	{
		for (size_t i = 0; i < 3; i++)	//��ÿһ�� i
		{
			for (size_t k = 0; k < 3; k++)
				for (size_t l = 0; l < 3; l++)
					dSR(i, j) -= gamma(i, k, l) * du[k] * SR_1(l, j);
		}
	}
	matf3 SR_2 = SR_1 + dSR;
	matf3 rstR = matf3::dot(S_u2.inverse(), SR_2);
	//����������Ҫ�ٱ�֤����
	vecf3 a[3];
	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++)
			a[i][j] = rstR(j, i);
	a[0] = a[0].normalize();
	a[1] = vecf3::cross(a[2], a[0]).normalize();
	a[2] = vecf3::cross(a[0], a[1]).normalize();
	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++)
			rstR(j, i) = a[i][j];
	return rstR;
}

