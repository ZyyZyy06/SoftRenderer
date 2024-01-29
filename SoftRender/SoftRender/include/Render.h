#pragma once

#include "Buffer.h"

class RenderTarget {
public:
	FrameBuffer buffer;
	bool depthTest;

	RenderTarget();
};


class Renderer {
public:
	void render(RenderTarget* renderTarget, Scene& scene, Camera& camera);
	void clear();
	void renderObject(Object* object);
	void renderTriangle(Vertex& v1, Vertex& v2, Vertex& v3);

protected:
	Material* mat;
	FrameBuffer* buffer;
	Shader* shader;
	Matrix4x4 V;
	Matrix4x4 P;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	std::vector<VertToFrag> clip(VertToFrag& v1, VertToFrag& v2, VertToFrag& v3);
	void perspectiveDivision(VertToFrag& v2f);

	// rasterization
	void bresenham(VertToFrag& from, VertToFrag& to, FrameBuffer* targetFrameBuffer);
	void shadingLine(VertToFrag& left, VertToFrag& right, FrameBuffer* targetFrameBuffer);
	void fillTriangle(VertToFrag& v1, VertToFrag& v2, VertToFrag& v3, FrameBuffer* targetFrameBuffer);
	void fillTopTriangle(VertToFrag& v1, VertToFrag& v2, VertToFrag& v3, FrameBuffer* targetFrameBuffer);
	void fillBottomTriangle(VertToFrag& v1, VertToFrag& v2, VertToFrag& v3, FrameBuffer* targetFrameBuffer);
};