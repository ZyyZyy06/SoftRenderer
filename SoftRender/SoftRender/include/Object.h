#pragma once

#include <string>
#include "Math.h"
#include "Algorithm.h"
#include <vector>
#include "Light.h"
#include "Camera.h"

class Uniforms {
public:
	Matrix4x4 M;
	Matrix4x4 V;
	Matrix4x4 P;
};


class Vertex {
public:
	Vector4f color;
	Vector4f pos;
	Vector3f normal;
	Vector2f texcoord;

	Vertex() : color(), pos(), normal(), texcoord() {}
	Vertex(Vector4f color, Vector4f pos, Vector3f normal, Vector2f texcoord) : color(color), pos(pos), normal(normal), texcoord(texcoord) {}
	Vertex(const Vertex& vec) : color(vec.color), pos(vec.pos), normal(vec.normal), texcoord(vec.texcoord) {}
};

class Mesh {

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh() {}
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
		this->vertices = vertices;
		this->indices = indices;
	}

	static Mesh triangle(Vector3f& v1, Vector3f& v2, Vector3f& v3);
	static Mesh cube();
	static Mesh plane();
};

class VertToFrag {
public:

	Vector2f screen_pos;

	Vector4f world_pos;
	Vector4f projection_pos;
	Vector4f color;
	Vector2f texcoord;
	Vector3f normal;
	unsigned int texID;
	double oneDivZ;

	VertToFrag lerp(const VertToFrag& end, double weight) {
		VertToFrag out;
		if (weight < 0) {
			return *this;
		}
		else if (weight > 1.0) {
			return end;
		}
		else {
			out.color = this->color.lerp(end.color, weight);
			out.normal = this->normal.lerp(end.normal, weight);
			out.projection_pos = this->projection_pos.lerp(end.projection_pos, weight);
			out.world_pos = this->world_pos.lerp(end.world_pos, weight);
			out.screen_pos = this->screen_pos.lerp(end.screen_pos, weight);
			out.texcoord = this->texcoord.lerp(end.texcoord, weight);
			out.texID = this->texID;
			return out;
		}
	}
};

class Shader {
public:

	virtual VertToFrag vertexShader(Vertex& vertex) = 0;
	virtual Vector4f fragmentShader(VertToFrag& v2f) = 0;

	Uniforms* uniforms;

	Shader() {};
	virtual ~Shader() {
		if (uniforms != NULL) {
			delete uniforms;
		}
	};
};

class Material {
public:
	Material(){};
	Material(Shader* shader) { this->shader = shader; };
	~Material() {}
	enum RenderMode { LINE, TRIANGLE } mode = TRIANGLE;
	Shader* shader;
};

class Transformer {
public:
	Vector3f pos;
	Vector3f rotation;
	Vector3f scale;

	Transformer() {
		this->pos = Vector3f(0.0, 0.0, 0.0);
		this->rotation = Vector3f(0.0, 0.0, 0.0);
		this->scale = Vector3f(1.0, 1.0, 1.0);
	}

	Matrix4x4 getTransformerMat() {
		//move
		Matrix4x4 t_move = TranslationMat(pos);

		//rotation
		Matrix4x4 t_r_x = RotationMat(rotation.x, 'x');
		Matrix4x4 t_r_y = RotationMat(rotation.y, 'y');
		Matrix4x4 t_r_z = RotationMat(rotation.z, 'z');

		//scale
		Matrix4x4 t_scale = ScaleMat(scale);

		return t_move * t_r_z * t_r_y * t_r_x * t_scale;
	}
};


class Object {
private:
	static int ID_COUNT;
public:
	Mesh mesh;
	Material material;
	Transformer transform;
	std::string name;
	unsigned int id;
	virtual void init(){};
	virtual void update(){};

	Object() {
		transform.scale = Vector3f(1.0, 1.0, 1.0);
		id = ID_COUNT;
		ID_COUNT++;
		this->name = std::string("obj_temp");
	}

	Object(std::string name) {
		transform.scale = Vector3f(1.0, 1.0, 1.0);
		this->name = name;
		id = ID_COUNT;
		ID_COUNT++;
	}
	virtual ~Object() {

	}
};


class Scene {

public:
	std::vector<Object*> objects;
	std::vector<Light> Light;
	virtual void init() {
		for (Object* obj : this->objects) {
			obj->init();
		}
	}

	virtual void update() {
		for (Object* obj : this->objects) {
			obj->update();
		}
	}
	virtual ~Scene() {
		for (Object* obj : this->objects) {
			if (obj != NULL)
				delete obj;
		}
	};
};

class Project {
public:
	Project() {}

	virtual void init(){};
	virtual void update(){};

	virtual ~Project() {}
};




