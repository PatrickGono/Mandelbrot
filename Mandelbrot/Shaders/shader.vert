#version 330 core
layout (location = 0) in vec3 array_pos;
layout (location = 1) in vec2 array_texture_coords;

out vec2 texture_coords;
out vec3 frag_pos;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(array_pos.xyz, 1.0);
	frag_pos = vec3(array_pos);
	texture_coords = array_texture_coords;
}