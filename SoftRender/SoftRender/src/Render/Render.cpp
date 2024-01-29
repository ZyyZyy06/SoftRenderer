#include "../../include/Render.h"
#include "../../include/Buffer.h"


void Renderer::bresenham(VertToFrag& from, VertToFrag& to, FrameBuffer* targetFrameBuffer) {
	int dx = to.screen_pos.x - from.screen_pos.x;
	int dy = to.screen_pos.y - from.screen_pos.y;
	int stepX = 1;
	int stepY = 1;

	if (dx < 0) {
		stepX = -1;
		dx = -dx;
	}
	if (dy < 0) {
		stepY = -1;
		dy = -dy;
	}

	int dy2 = 2 * dy;
	int dx2 = 2 * dx;
	int dy2_minex_dx2 = dy2 - dx2;

	int nowx = from.screen_pos.x;
	int nowy = from.screen_pos.y;

	// dy <= dx,
	VertToFrag tempV2f;
	if (dy <= dx) {
		int p = dy2 - dx;
		for (int i = 0; i <= dx; i++) {

			tempV2f = from.lerp(to, static_cast<double>(i) / dx);
			if (static_cast<double>(tempV2f.projection_pos.z) < targetFrameBuffer->depthBuffer.getValue(nowx, nowy)) {
				// shading
				Vector4f color = shader->fragmentShader(tempV2f);
				targetFrameBuffer->rgbaBuffer.setValue(nowx, nowy, color);
				targetFrameBuffer->depthBuffer.setValue(nowx, nowy, tempV2f.projection_pos.z);
			}
			nowx += stepX;
			if (p <= 0)
				p += dy2;
			else {
				nowy += stepY;
				p += dy2_minex_dx2;
			}
		}
	}
	// dy > dx
	else {
		int p = dx2 - dy;
		for (int i = 0; i <= dy; i++) {

			tempV2f = from.lerp(to, static_cast<double>(i) / dx);
			if (static_cast<double>(tempV2f.projection_pos.z) < targetFrameBuffer->depthBuffer.getValue(nowx, nowy)) {
				// shading
				Vector4f color = shader->fragmentShader(tempV2f);
				if (nowy >= 1080)
					int c = 2;
				targetFrameBuffer->rgbaBuffer.setValue(nowx, nowy, color);
				targetFrameBuffer->depthBuffer.setValue(nowx, nowy, tempV2f.projection_pos.z);
			}
			nowy += stepY;

			if (p <= 0)
				p += dx2;
			else {
				nowx += stepX;
				p -= dy2_minex_dx2;
			}
		}
	}

}

void Renderer::shadingLine(VertToFrag& left, VertToFrag& right, FrameBuffer* targetFrameBuffer) {
	int length = right.screen_pos.x - left.screen_pos.x;
	int nowx = (int)left.screen_pos.x;
	int nowy = (int)left.screen_pos.y;

	for (int i = 0; i <= length; i++) {
		VertToFrag tempV2f = left.lerp(right, static_cast<double>(i) / (length + 0.00001));
		tempV2f.screen_pos = Vector2f(nowx, nowy);

		if (tempV2f.projection_pos.z >= 1.0f) {
			int b = 0;
		}
		// zTest
		if (static_cast<double>(tempV2f.projection_pos.z) < targetFrameBuffer->depthBuffer.getValue(nowx, nowy)) {
			Vector4f color = shader->fragmentShader(tempV2f);

			targetFrameBuffer->rgbaBuffer.setValue(nowx, nowy, color);
			targetFrameBuffer->depthBuffer.setValue(nowx, nowy, tempV2f.projection_pos.z);

		}
		nowx++;
		// zTest over
	}
}

void Renderer::fillTopTriangle(VertToFrag& v1, VertToFrag& v2, VertToFrag& v3, FrameBuffer* targetFrameBuffer)
{
	int nowy = (int)v2.screen_pos.y;
	int height = (int)(nowy - v1.screen_pos.y);

	VertToFrag top = v1;
	VertToFrag left;
	VertToFrag right;

	VertToFrag tmpLeft;
	VertToFrag tmpRight;

	if (v2.screen_pos.x < v3.screen_pos.x) {
		left = v2;
		right = v3;
	}
	else {
		left = v3;
		right = v2;
	}

	for (int i = 0; i <= height; i++) {
		double weight = static_cast<double>(i) / static_cast<double>(height);
		tmpLeft = left.lerp(top, weight);
		tmpRight = right.lerp(top, weight);
		tmpLeft.screen_pos.y = nowy;
		tmpRight.screen_pos.y = nowy;
		shadingLine(tmpLeft, tmpRight, targetFrameBuffer);
		nowy--;
	}
}

void Renderer::fillBottomTriangle(VertToFrag& v1, VertToFrag& v2, VertToFrag& v3, FrameBuffer* targetFrameBuffer)
{
	int nowy = v2.screen_pos.y;
	int height = v1.screen_pos.y - nowy;

	VertToFrag bottom = v1;
	VertToFrag left;
	VertToFrag right;

	VertToFrag tmpLeft;
	VertToFrag tmpRight;

	if (v2.screen_pos.x < v3.screen_pos.x) {
		left = v2;
		right = v3;
	}
	else {
		left = v3;
		right = v2;
	}

	for (int i = 0; i <= height; i++) {
		if (i == height) {
			int a = 1;
		}
		double weight = static_cast<double>(i) / static_cast<double>(height);
		tmpLeft = left.lerp(bottom, weight);
		tmpRight = right.lerp(bottom, weight);
		tmpLeft.screen_pos.y = nowy;
		tmpRight.screen_pos.y = nowy;
		shadingLine(tmpLeft, tmpRight, targetFrameBuffer);
		nowy++;
	}
}

void Renderer::fillTriangle(VertToFrag& v1, VertToFrag& v2, VertToFrag& v3, FrameBuffer* targetFrameBuffer) {

	VertToFrag triangle[3] = { v1, v2, v3 };
	VertToFrag tmpVert;

	if (triangle[0].screen_pos.y > triangle[1].screen_pos.y) {
		tmpVert = triangle[0];
		triangle[0] = triangle[1];
		triangle[1] = tmpVert;
	}
	if (triangle[1].screen_pos.y > triangle[2].screen_pos.y) {
		tmpVert = triangle[1];
		triangle[1] = triangle[2];
		triangle[2] = tmpVert;
	}
	if (triangle[0].screen_pos.y > triangle[1].screen_pos.y) {
		tmpVert = triangle[0];
		triangle[0] = triangle[1];
		triangle[1] = tmpVert;
	}


	if (static_cast<int>(triangle[1].screen_pos.y) == static_cast<int>(triangle[2].screen_pos.y)) {
		fillTopTriangle(triangle[0], triangle[1], triangle[2], targetFrameBuffer);
	}
	else if (static_cast<int>(triangle[0].screen_pos.y) == static_cast<int>(triangle[1].screen_pos.y)) {
		fillBottomTriangle(triangle[2], triangle[0], triangle[1], targetFrameBuffer);
	}
	else {
		double weight = static_cast<double>((triangle[1].screen_pos.y - triangle[0].screen_pos.y))
			/ static_cast<double>((triangle[2].screen_pos.y - triangle[0].screen_pos.y));
		VertToFrag newVert = triangle[0].lerp(triangle[2], weight);
		newVert.screen_pos.y = triangle[1].screen_pos.y;
		fillTopTriangle(triangle[0], triangle[1], newVert, targetFrameBuffer);
		fillBottomTriangle(triangle[2], triangle[1], newVert, targetFrameBuffer);
	}
}


std::vector<VertToFrag> Renderer::clip(VertToFrag& v1, VertToFrag& v2, VertToFrag& v3) {
	std::vector<VertToFrag> ret;
	ret.push_back(v1);
	ret.push_back(v2);
	ret.push_back(v3);
	return ret;
}


void Renderer::perspectiveDivision(VertToFrag& v2f) {
	float w = v2f.projection_pos.w;
	v2f.projection_pos.x = v2f.projection_pos.x / w;
	v2f.projection_pos.y = v2f.projection_pos.y / w;
	v2f.projection_pos.z = v2f.projection_pos.z / w;
	v2f.projection_pos.w = 1.0;

	v2f.projection_pos.z = (v2f.projection_pos.z + 1.0f) * 0.5f;
	v2f.oneDivZ = 1.0 / static_cast<double>(v2f.projection_pos.z);
}

void Renderer::render(RenderTarget* renderTarget, Scene& scene, Camera& camera) {
	if (renderTarget == NULL) {
		this->buffer = WindowBuffer::getInstance()->getDrawBuffer();
	}
	else {
		this->buffer = &renderTarget->buffer;
	}

	V = worldToView(camera.pos, camera.target, camera.up);
	P = viewToClip_projection(camera.fovY, camera.aspect, camera.nearDis, camera.farDis);


	for (Object* object : scene.objects) {
		renderObject(object);
	}
	WindowBuffer::getInstance()->SwapWindowBuffer();
	std::cout << "render over" << std::endl;
}

void Renderer::renderObject(Object* object) {
	this->vertices = object->mesh.vertices;
	this->indices = object->mesh.indices;

	mat = &object->material;
	shader = mat->shader;
	
	shader->uniforms->M = object->transform.getTransformerMat();
	shader->uniforms->V = V;
	shader->uniforms->P = P;

	int triangleCount = indices.size() / 3;
	for (int i = 0; i < triangleCount; i++) {
		Vertex v1 = vertices[indices[i * 3]];
		Vertex v2 = vertices[indices[i * 3 + 1]];
		Vertex v3 = vertices[indices[i * 3 + 2]];
		renderTriangle(v1, v2, v3);
	}
}


void Renderer::renderTriangle(Vertex & v1, Vertex & v2, Vertex & v3) {

	VertToFrag v2f1 = shader->vertexShader(v1);
	VertToFrag v2f2 = shader->vertexShader(v2);
	VertToFrag v2f3 = shader->vertexShader(v3);

	std::vector<VertToFrag> render_quene = this->clip(v2f1, v2f2, v2f3);

	assert(render_quene.size() % 3 == 0);

	for (int i = 0; i < render_quene.size() / 3; i++)
	{
		VertToFrag f1 = render_quene[i];
		VertToFrag f2 = render_quene[i + 1];
		VertToFrag f3 = render_quene[i + 2];

		perspectiveDivision(f1);
		perspectiveDivision(f2);
		perspectiveDivision(f3);

		Matrix4x4 viewPortMat = viewPort(buffer->rgbaBuffer.width, buffer->rgbaBuffer.height);
		Vector4f f1ScreenPos = viewPortMat * f1.projection_pos;
		f1.screen_pos = Vector2f(f1ScreenPos.x, f1ScreenPos.y);
		Vector4f f2ScreenPos = viewPortMat * f2.projection_pos;
		f2.screen_pos = Vector2f(f2ScreenPos.x, f2ScreenPos.y);
		Vector4f f3ScreenPos = viewPortMat * f3.projection_pos;
		f3.screen_pos = Vector2f(f3ScreenPos.x, f3ScreenPos.y);

		//4. rasterization
		if (mat->mode == Material::LINE) {
			bresenham(f1, f2, buffer);
			bresenham(f1, f3, buffer);
			bresenham(f2, f3, buffer);
		}
		else if (mat->mode == Material::TRIANGLE) {
			fillTriangle(f1, f2, f3, buffer);
		}
	}
}

void Renderer::clear() {
	this->buffer = NULL;
	this->mat = NULL;
	vertices.clear();
	indices.clear();
}