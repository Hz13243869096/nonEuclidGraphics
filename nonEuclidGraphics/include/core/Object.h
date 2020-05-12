#pragma once

#include <core/vec.h>
#include <core/mat.h>
#include <core/Mesh.h>
#include <core/Obj.h>
#include <core/transform.h>



namespace cgcore
{
	class Object : public Obj
	{
	public:
		~Object();

		Object(nonEuc::World* _world, std::shared_ptr<Mesh> _mesh, vecf3 _center, vecf3 _scale, matf3 _rotation)
			: Obj(_world), mesh{ _mesh }, center{ _center }, R{ _rotation }
		{
			scale = matf3::Diag(_scale);
			obj_type = _Object;
		}

		void Transform(matf3 S);
		void Draw(GLuint programID);

	private:


	public:
		std::shared_ptr<Mesh> mesh;
		vecf3 center;
		matf3 R;
		matf3 scale;
		vecf3 color;	//��û����ͼʱʹ��

	private:


	};

	inline Object::~Object()
	{
		
	}
}
