#pragma once
#include <iostream>

#include <GL/glew.h>

class Mesh
{
private:
	GLuint VAO, VBO, IBO;
	GLsizei index_count;

public:
	Mesh();
	~Mesh();

	void create_mesh(GLfloat* vertices, unsigned int* indices, unsigned int n_vertices, unsigned int n_indices);
	void render_mesh();
	void clear_mesh();
};

