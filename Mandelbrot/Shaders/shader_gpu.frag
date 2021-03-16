#version 330 core
in vec2 texture_coords;
in vec3 frag_pos;

out vec4 frag_color;

uniform vec3 position_and_zoom;
uniform sampler2D our_texture;

#define MAX_ITER 100

int compute_iterations()
{
	float pos_x = position_and_zoom.x;
	float pos_y = position_and_zoom.y;
	float zoom = position_and_zoom.z;

	float x_range = 4.0 / zoom;
	float y_range = 4.0 / zoom;

	float x = pos_x + 2.0 * (frag_pos.x - 0.5) * x_range;
	float y = pos_y + 2.0 * (frag_pos.y - 0.5) * y_range;

	float const_x = x;
	float const_y = y;

	float tmp_x = x;
	float distance = 0;
	int iteration = 0;

	while (iteration < MAX_ITER)
	{
		tmp_x = x;
		x = (x * x - y * y) + const_x;
		y = 2.0 * tmp_x * y + const_y;

		distance = x * x + y * y;

		if (distance > 4)
		{
			return iteration;
		}

		iteration++;
	}
	return 0;
}

vec4 calculate_color(int iterations)
{
	vec4 color = vec4(1.0, 1.0, 1.0, 1.0) * float(iterations) / float(MAX_ITER);
	return color;
}

void main()
{
	int iterations = compute_iterations();
	frag_color = calculate_color(iterations);
}