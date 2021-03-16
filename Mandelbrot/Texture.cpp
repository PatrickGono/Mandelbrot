#include "Texture.h"



Texture::Texture() : width(0), height(0), texture_ID(0), texture_data(0)
{
	initialize_texture();
}

Texture::Texture(int width, int height)
	: width(width), height(height), texture_ID(0), texture_data(0)
{
	initialize_texture();
	texture_data = std::vector<unsigned char>(width * height * 3, 0);
}


Texture::~Texture()
{
	clear_texture();
}

bool Texture::initialize_texture()
{
	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);

	// Set some parameters for wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	//glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	//glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

	// Once initialized, unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

bool Texture::set_texture()
{
	// Bind texture
	glBindTexture(GL_TEXTURE_2D, texture_ID);

	// Bind the data to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	// Once bound, unbind the texture and free the data
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

void Texture::use_texture()
{
	// Bind texture to texture unit (0 by default)
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
}

void Texture::clear_texture()
{
	glDeleteTextures(1, &texture_ID);
	texture_ID = 0;
	width = 0;
	height = 0;
}
