#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>


#include <GL/gl3w.h>            // Initialize with gl3wInit()
#include <GLFW/glfw3.h>

#include<nonEuclideanEngine/world.h>
#include <core/Mesh.h>
#include <core/Obj.h>
#include <nonEuclideanEngine/shader.hpp>

namespace nonEuc
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		void SetWorld(std::shared_ptr<World> world){ current_world = world; }
		bool Init();	// ��ʼ��OpenGL��Imgui
		void Loop();	// ��Ҫ��ѭ��
		void Clear();	// �ڽ�����ʱ�����

		void UpdateCamera();

	private:
		// Ŀ�ľ��ǰ���������Ķ�����ʾ����
		// ����Ӧ�ð�����
		//	1.���е�Obj(Mesh)
		//	2.һ��Camera
		//	3.���ʵı任
		std::shared_ptr<World> current_world = nullptr;


		GLFWwindow* window = nullptr;		// ����
		GLuint programID = 0;				// ��ɫ��
		int scrwidth = 1280;
		int scrheight = 720;
		float far_plane = 100.f;
		float near_plane = 0.1f;

		bool show_demo_window = false;
		bool mouseIO = false;
		bool status_line = false;
		float mouse_speed = 0.05f;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	};
}


