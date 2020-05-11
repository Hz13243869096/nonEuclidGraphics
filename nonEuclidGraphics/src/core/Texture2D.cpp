
#include <core/Texture2D.h>

using namespace cgcore;

Texture2D::Texture2D()
{
}

Texture2D::Texture2D(const std::string& path)
{
	Load(path);
	image_path = path;
}

Texture2D::~Texture2D()
{
}

void Texture2D::Load(const std::string& path)
{
	img = cv::imread(path, cv::IMREAD_COLOR);//3 channel BGR
	if (img.empty())
	{
		std::cout << "ERROR::Texture2D::Load:" << std::endl
			<< "\t" << "open file (" << path << ") fail" << std::endl;
	}
	image_path = path;
}

vecf3 Texture2D::Sample(vecf2 uv)
{
	if (img.empty())
	{
		std::cout << "ERROR::Texture2D::Sample:" << std::endl
			<< "\t" << "img is empty" << std::endl;
		return vecf3({ 0, 1, 0 });
	}
	//repeat mode
	uv[0] -= float(int(uv[0]));
	uv[1] -= float(int(uv[1]));

	int xidx = int(uv[0] * img.cols);
	int yidx = int(uv[1] * img.rows);
	float xlambda = uv[0] * img.cols - xidx;
	float ylambda = uv[1] * img.rows - yidx;
	//˫���Բ�ֵ
	cv::Vec3b result = (1 - ylambda) * ((1 - xlambda) * img.at<cv::Vec3b>(yidx, xidx) + xlambda * img.at<cv::Vec3b>(yidx, (xidx + 1) % img.cols))
		+ ylambda * ((1 - xlambda) * img.at<cv::Vec3b>((yidx + 1) % img.rows, xidx) + xlambda * img.at<cv::Vec3b>((yidx + 1) % img.rows, (xidx + 1) % img.cols));

	return vecf3({ (float)result[2], (float)result[1] , (float)result[0] });//ת��ΪRGB
}

void cgcore::Texture2D::SetTextureImage()
{
	if (img.empty())
	{
		std::cout << "Texture2D::SetTextureImage : No available texture image" << std::endl;
		return;
	}
	GLsizei width = img.cols, height = img.rows;
	//����id����
	glGenTextures(1, &id);					
	glBindTexture(GL_TEXTURE_2D, id);

	//�����������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//���������ݴ���OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data);	
	glGenerateMipmap(GL_TEXTURE_2D);

	BindReset();
}

void cgcore::Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void cgcore::Texture2D::BindReset()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool cgcore::Texture2D::IsValid()
{
	return id != 0;
}
