#include "../../include/Object.h"

Mesh Mesh::triangle(Vector3f& p1, Vector3f& p2, Vector3f& p3)
{
	Mesh triangle;
	Vertex v1 = Vertex
	(Vector4f(1.0, 0.0, 0.0, 1.0),
		Vector4f(p1, 1.0),
		Vector3f(0, 0, 0),
		Vector2f(0, 0));
	Vertex v2
		= Vertex
		(Vector4f(0.0, 1.0, 0.0, 1.0),
			Vector4f(p2, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));
	Vertex v3
		= Vertex
		(Vector4f(0.0, 0.0, 1.0, 1.0),
			Vector4f(p3, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));

	triangle.vertices.clear();
	triangle.vertices.push_back(v1);
	triangle.vertices.push_back(v2);
	triangle.vertices.push_back(v3);

	triangle.indices.clear();
	triangle.indices.push_back(0);
	triangle.indices.push_back(1);
	triangle.indices.push_back(2);


	return triangle;
}

Mesh Mesh::plane()
{
	Mesh plane;

	Vertex v1
		= Vertex
		(Vector4f(1.0, 1.0, 1.0, 1.0),
			Vector4f(-0.5, -0.5, 0.0, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));
	Vertex v2
		= Vertex
		(Vector4f(1.0, 0.0, 0.0, 1.0),
			Vector4f(0.5, -0.5, 0.0, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));
	Vertex v3
		= Vertex
		(Vector4f(0.0, 1.0, 0.0, 1.0),
			Vector4f(0.5, 0.5, 0.0, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));
	Vertex v4
		= Vertex
		(Vector4f(0.0, 0.0, 1.0, 1.0),
			Vector4f(-0.5, 0.5, 0.0, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));

	plane.vertices.clear();
	plane.vertices.push_back(v1);
	plane.vertices.push_back(v2);
	plane.vertices.push_back(v3);
	plane.vertices.push_back(v4);

	plane.indices.clear();
	plane.indices.push_back(0);
	plane.indices.push_back(1);
	plane.indices.push_back(2);

	plane.indices.push_back(0);
	plane.indices.push_back(2);
	plane.indices.push_back(3);


	return plane;
}

Mesh Mesh::cube()
{
	Mesh cube;
	Vertex v1
		= Vertex
		(Vector4f(1.0, 1.0, 1.0, 1.0),
			Vector4f(0.5, 0.5, 0.5, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));
	Vertex v2
		= Vertex
		(Vector4f(1.0, 0.0, 0.0, 1.0),
			Vector4f(0.5, 0.5, -0.5, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));
	Vertex v3
		= Vertex
		(Vector4f(0.0, 1.0, 0.0, 1.0),
			Vector4f(-0.5, 0.5, -0.5, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));
	Vertex v4
		= Vertex
		(Vector4f(0.0, 0.0, 1.0, 1.0),
			Vector4f(-0.5, 0.5, 0.5, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));


	Vertex v5
		= Vertex
		(Vector4f(1.0, 1.0, 1.0, 1.0),
			Vector4f(0.5, -0.5, 0.5, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));
	Vertex v6
		= Vertex
		(Vector4f(1.0, 0.0, 0.0, 1.0),
			Vector4f(0.5, -0.5, -0.5, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));
	Vertex v7
		= Vertex
		(Vector4f(0.0, 1.0, 0.0, 1.0),
			Vector4f(-0.5, -0.5, -0.5, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));
	Vertex v8
		= Vertex
		(Vector4f(0.0, 0.0, 1.0, 1.0),
			Vector4f(-0.5, -0.5, 0.5, 1.0),
			Vector3f(0, 0, 0),
			Vector2f(0, 0));


	cube.vertices.clear();
	cube.vertices.push_back(v1);
	cube.vertices.push_back(v2);
	cube.vertices.push_back(v3);
	cube.vertices.push_back(v4);
	cube.vertices.push_back(v5);
	cube.vertices.push_back(v6);
	cube.vertices.push_back(v7);
	cube.vertices.push_back(v8);


	cube.indices.clear();

	cube.indices.push_back(0);
	cube.indices.push_back(4);
	cube.indices.push_back(7);

	cube.indices.push_back(0);
	cube.indices.push_back(3);
	cube.indices.push_back(7);


	cube.indices.push_back(0);
	cube.indices.push_back(3);
	cube.indices.push_back(2);

	cube.indices.push_back(0);
	cube.indices.push_back(1);
	cube.indices.push_back(2);

	cube.indices.push_back(1);
	cube.indices.push_back(2);
	cube.indices.push_back(6);


	cube.indices.push_back(1);
	cube.indices.push_back(5);
	cube.indices.push_back(6);



	cube.indices.push_back(0);
	cube.indices.push_back(1);
	cube.indices.push_back(5);

	cube.indices.push_back(0);
	cube.indices.push_back(4);
	cube.indices.push_back(5);


	cube.indices.push_back(3);
	cube.indices.push_back(7);
	cube.indices.push_back(6);


	cube.indices.push_back(3);
	cube.indices.push_back(2);
	cube.indices.push_back(6);

	cube.indices.push_back(4);
	cube.indices.push_back(5);
	cube.indices.push_back(6);


	cube.indices.push_back(4);
	cube.indices.push_back(7);
	cube.indices.push_back(6);


	return cube;
}