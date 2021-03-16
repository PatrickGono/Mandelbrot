#pragma once
#include <GL/glew.h>
#include <memory>
#include <vector>

#include "CommonValues.h"

class Texture
{
private:
	GLuint texture_ID;
	int width, height;
	std::vector<unsigned char> texture_data;

public:
	Texture();
	Texture(int width, int height);
	~Texture();

	bool initialize_texture();
	bool set_texture();
	void use_texture();
	void clear_texture();

	unsigned char& operator[](int index) { return texture_data[index]; }
};

