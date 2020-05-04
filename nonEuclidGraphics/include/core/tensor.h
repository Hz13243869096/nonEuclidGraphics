#pragma once

#include <initializer_list>
#include <assert.h>
#include <vector>
#include <core/mat.h>

namespace cgcore
{

    //����Ϊ���ձ��ԣ��������ʵ��һ������׵��������ͣ��Ͱ���˹̹��͡�
    //�����������������Ҫ�ķǳ����ޣ�ֻʵ��shape = (3,3,3) ������tensor�����ף���������Ҳ����
    /*template<typename T, int dims_>
    struct tensor
    {
        T* data;
        size_t* shape;
        size_t* step;
        
        tensor()
        {

        }

        T& operator()(const std::vector<size_t>& idx)
        {
            size_t i = 0;
            for (size_t d = 0; d < dims; d++)
                i += step[d] * idx[d];
            return data[i];
        }
        
        template<size_t dim1,>
        sum(const std::vector<tensor<T>>&)
            
    };*/

    struct tensorf333
    {
        float* const data = new float[27];
        const size_t size = 27;
        
        tensorf333() {}

        tensorf333(const tensorf333& t2)
        {
            for (float* p1 = data, *p2 = t2.data, *pe = data + size; p1 < pe; p1++, p2++)
                *p1 = *p2;
        }

        tensorf333(const std::initializer_list<float>& elem_list)
        {
            assert(elem_list.size() <= size);
            size_t i = 0;
            for (float it : elem_list)
                data[i++] = it;
        }

        ~tensorf333() { delete[] data; }

        float& operator()(size_t i, size_t j, size_t k)
        {
            return data[9*i + 3*j + k];
        }
    };
}