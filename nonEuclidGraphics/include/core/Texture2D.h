#pragma once
/*
openCV: �޸Ĺ��̵İ���Ŀ¼����Ŀ¼������������
*/

#include <core/vec.h>
#include <core/mat.h>
#include <core/rgb.h>
#include <core/transform.h>

#include <GL/gl3w.h>            // Initialize with gl3wInit()
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>

namespace cgcore
{
	class Texture2D
	{
	public:
		Texture2D();
		Texture2D(const std::string& path);
		~Texture2D();

		void Load(const std::string& path);
		rgbf Sample(vecf2 uv);

	private:
		std::string image_path;

	public:
		enum class WrapMode { Clamp, Repeat, Mirror };
		enum class SampleMode { Nearest, Linear };

		cv::Mat img;
		GLuint id = 0;					//OpenGL�õ�id

		//����OpenGL������
		void SetTextureImage();

		void Bind();
		void BindReset();

		bool IsValid();

	private:

	};


}