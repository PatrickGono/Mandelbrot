#include "Mesh.h"

Mesh::Mesh()
{
	VBO = 0;
	VAO = 0;
	IBO = 0;
	index_count = 0;
}

Mesh::~Mesh()
{
	clear_mesh();
}


void Mesh::create_mesh(GLfloat * vertices, unsigned int * indices, unsigned int n_vertices, unsigned int n_indices)
{
	index_count = n_indices;

	// we create one vertex array and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// we create one element buffer, bind it, and attach the data of the indices
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * n_indices, indices, GL_STATIC_DRAW);

	// we create one vertex buffer, bind it, and attach the data
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * n_vertices * 5, vertices, GL_STATIC_DRAW);

	// start with position (attribute 0), there are three coordinates, we need to read 
	// them with a stride of 5 as there are also the texture coords, and use 0 offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
	glEnableVertexAttribArray(0);

	// texture coordinates (attribute 1), there are two coordinates, stride 5, offset 3
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::render_mesh()
{
	//std::cout << "Rendering mesh in position: ";
	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//std::cout << "Mesh: mesh rendered\n";
}

void Mesh::clear_mesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
}
