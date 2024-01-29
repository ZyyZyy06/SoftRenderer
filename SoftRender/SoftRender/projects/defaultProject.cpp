#include "../include/Object.h"
#include "../include/Render.h"
#include "../include/Camera.h"

class DefaultShader : public Shader {
public:
	DefaultShader() : Shader() {
		uniforms = new Uniforms();
	}

	virtual ~DefaultShader() {
	}

	virtual  VertToFrag vertexShader(Vertex& vertex) {
		VertToFrag v2f = VertToFrag();

		v2f.world_pos = uniforms->M * vertex.pos;

		v2f.projection_pos = uniforms->P * uniforms->V * v2f.world_pos;


		v2f.color = vertex.color;
		v2f.normal = vertex.normal;

		v2f.texcoord = vertex.texcoord;

		return v2f;
	}

	virtual Vector4f fragmentShader(VertToFrag& v2f) {
		Vector4f fragColor = v2f.color;
		return fragColor;
	}
};

class Cube : public Object {
public:
	Cube() : Object("cube") {
		this->mesh = Mesh::cube();
	}
	virtual void update() {
		transform.rotation = transform.rotation + Vector3f(0.2, 0.2, 0.2);
		transform.rotation = transform.rotation + Vector3f(0.2, 0.2, 0.2);
	}
};


class DefaultProject : public Project {
public:
	Renderer renderer;
	Camera camera;
	Scene scene;

	DefaultProject() : Project() {}


	virtual void init() {
		//create objects
		Object* cube = new Cube();
		cube->transform.pos = Vector3f(0.0, 0.0, -2);
		cube->transform.scale = Vector3f(0.5, 0.5, 0.5);
		cube->transform.rotation = Vector3f(45, 45, 45);

		Object* cube2 = new Cube();
		cube2->transform.pos = Vector3f(0.6, 0.3, -4);
		cube2->transform.scale = Vector3f(0.5, 0.5, 0.5);
		cube2->transform.rotation = Vector3f(45, 45, 45);

		Material mat;
		//mat.mode = Material::LINE;
		Shader* shader = new DefaultShader();
		mat.shader = shader;
		cube->material = mat;
		cube2->material = mat;

		//create scene
		scene.objects.push_back(cube);
		scene.objects.push_back(cube2);
		scene.init();
	}

	virtual void update() {
		scene.update();
		renderer.clear();
		renderer.render(NULL, scene, camera);
	}
};