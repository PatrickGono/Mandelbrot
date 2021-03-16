#version 330 core
in vec2 texture_coords;
in vec3 frag_pos;

out vec4 frag_color;

uniform sampler2D our_texture;


void main()
{
	frag_color = texture(our_texture, texture_coords);
}