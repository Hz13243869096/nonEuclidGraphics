#pragma once

#include <core/vec.h>
#include <string.h>

namespace cgcore
{
	// С�ͳ��ܾ����ģ��
	template<typename T, size_t NRow, size_t NCol>
	struct mat
	{
		T* const data = new T[NRow*NCol];
		static const size_t size = NRow * NCol;

		mat(){}
		mat(const mat<T, NRow, NCol>& m)
		{
			memcpy(data, m.data, sizeof(T) * size);
		}
		mat(const T val)
		{
			fill(val);
		}
		
		mat(std::initializer_list<T> elem_list)
		{
			assert(elem_list.size() <= size && "Initializer list is too long");
			size_t i = 0;
			for (auto it : elem_list)
				data[i++] = it;
		}
		~mat() { delete[] data; }

		//ͨ���С��з���. (irow, joc) �൱�� [irow*Ncol+jcol]
		T& operator()(const size_t irow, const size_t jcol) const 
		{
			assert(irow < NRow && jcol < NCol && "mat:: Index out of range");
			return data[irow * NCol + jcol];
		}

		//ֱ��ͨ����������
		T& operator[](const size_t idx) const 
		{
			assert(idx < size && "mat:: Index out of range");
			return data[idx];
		}

		//��ֵ�����
		const mat<T, NRow, NCol>& operator =(const mat<T, NRow, NCol>& m)
		{
			for (size_t i = 0; i < size; i++)
				data[i] = m.data[i];
			return (*this);
		}

		void fill(T val);

		template<size_t L>
		static const mat<T, NRow, L> dot(const mat<T, NRow, NCol>& m1, const mat<T, NCol, L>& m2);

		const vec<T, NRow> dot(const vec<T, NCol>& v) const;

		const mat<T, NRow, NCol> operator*(const T t) const;

		const mat<T, NCol, NRow> transpose() const;
		
		//�������档�� ! ����3x3�������⣬���������Ƿ���ȷ��û����֤��
		mat<T, NCol, NRow> inverse() const;
		
		//������i, j
		void SR(size_t i, size_t j);
		//���� j �� val ���ӵ��� i ��
		void TR(size_t i, size_t j, T val);
		//���� i ���� val ��
		void DR(size_t i, T val);

		//������ˣ�v1^T.Self.v2
		const T dot_s(const vec<T, NRow>& v1, const vec<T, NCol>& v2) const;

		static mat<T, NRow, NCol> Identity();
		static mat<T, NRow, NRow> Diag(const vec<T, NRow> diag);
	};
	template<typename T, size_t NRow, size_t NCol>
	std::ostream& operator << (std::ostream& ostrm, const mat<T, NRow, NCol>& m);


	typedef mat<float, 3, 3> matf3;
	typedef mat<float, 4, 4> matf4;
	typedef mat<float, 4, 3> matf43;
}

#include <core/mat.inl>