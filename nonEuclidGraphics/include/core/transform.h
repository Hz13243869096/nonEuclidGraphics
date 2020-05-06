#pragma once

#include<core/mat.h>

namespace cgcore
{
	/*
	�����ṩһЩ�任�ĺ���
	1. ʩ����������
	template<typename T, size_t NRow, size_t NRow> mat<T, NRow, NRow>
		SchmidtOrthogonalize(const mat<T, NRow, NRow>& metric);

	2. ����ƽ��+��ת -> 4x4 Transform ����

	*/



	//ʩ���������� (metric : ��������) //TODO
	template<typename T, size_t NRow, size_t NRow>
		mat<T, NRow, NRow> SchmidtOrthogonalize(const mat<T, NRow, NRow>& metric)
	{
		mat<T, NRow, NRow> ret;
		ret.fill(static_cast<T>(0));
		//TODO
	}

	
}