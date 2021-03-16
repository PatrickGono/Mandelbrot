#include "Canvas.h"

Canvas::Canvas()
{
	create_mesh();
}

void Canvas::create_mesh()
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	unsigned int n_vertices = 0;
	unsigned int n_indices = 0;


	// bottom left
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(-1.0f);
	// texture coordinates
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	n_vertices++;

	// bottom right
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);
	vertices.push_back(-1.0f);
	// texture coordinates
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);

	n_vertices++;

	// top left
	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
	vertices.push_back(-1.0f);
	// texture coordinates
	vertices.push_back(0.0f);
	vertices.push_back(1.0f);

	n_vertices++;

	// top right
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(-1.0f);
	// texture coordinates
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);

	n_vertices++;

	
	/* 
	   2..3
	   |\ :
	   | \:
	   0__1
	*/
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(1);
	n_indices = n_indices + 3;

	/*
	   2--3
	   :\ |
	   : \|
	   0..1
	*/
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	n_indices = n_indices + 3;


	mesh = std::make_unique<Mesh>();
	mesh->create_mesh(vertices.data(), indices.data(), n_vertices, n_indices);
}

void Canvas::render()
{
	if (!mesh)
	{
		return;
	}

	mesh->render_mesh();
}
