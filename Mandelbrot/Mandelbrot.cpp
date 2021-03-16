#include "Mandelbrot.h"

Mandelbrot::Mandelbrot(int width, int height) : width(width), height(height), pos_x(0.0f), pos_y(0.0f), zoom(1.0f), max_iterations(MAX_ITERATIONS)
{
	data = std::vector<float>(width * height, 0.0f);
	texture = Texture(width, height);
	texture.initialize_texture();

	shaders.emplace_back(std::make_unique<Shader>("Shaders/shader.vert", "Shaders/shader.frag"));
	shaders.emplace_back(std::make_unique<Shader>("Shaders/shader.vert", "Shaders/shader_gpu.frag"));

	std::cout << "Simple:\n";
}

void Mandelbrot::process_keyboard(bool keys[])
{
	float velocity = 0.10f;

	if (keys[GLFW_KEY_W])
		pos_y += velocity / zoom;
	if (keys[GLFW_KEY_S])
		pos_y -= velocity / zoom;
	if (keys[GLFW_KEY_D])
		pos_x += velocity / zoom;
	if (keys[GLFW_KEY_A])
		pos_x -= velocity / zoom;
	if (keys[GLFW_KEY_E])
		zoom += 0.25 * zoom * velocity;
	if (keys[GLFW_KEY_Q])
		zoom -= 0.25 * zoom * velocity;

	if (keys[GLFW_KEY_1])
	{
		if (!(calculation_type == Calculation_Type::SIMPLE))
		{
			std::cout << "Simple:\n";
			calculation_type = Calculation_Type::SIMPLE;
		}
	}

	if (keys[GLFW_KEY_2])
	{
		if (!(calculation_type == Calculation_Type::OPEN_MP))
		{
			std::cout << "OpenMP:\n";
			calculation_type = Calculation_Type::OPEN_MP;
		}
	}

	if (keys[GLFW_KEY_3])
	{
		if (!(calculation_type == Calculation_Type::THREAD))
		{
			std::cout << "Threads:\n";
			calculation_type = Calculation_Type::THREAD;
		}
	}

	if (keys[GLFW_KEY_4])
	{
		if (!(calculation_type == Calculation_Type::SHADER))
		{
			std::cout << "Shader:\n";
			calculation_type = Calculation_Type::SHADER;
		}
	}
	return;
}

void Mandelbrot::calculate_and_render()
{
	switch(calculation_type)
	{
	case Calculation_Type::OPEN_MP:
		shaders[0]->use_shader();
		calculate_open_mp();
		convert_to_rgb();
		render();
		break;

	case Calculation_Type::THREAD:
		shaders[0]->use_shader();
		calculate_thread();
		convert_to_rgb();
		render();
		break;

	case Calculation_Type::SHADER:
		shaders[1]->use_shader();
		calculate_shader();
		render();
		break;

	default:
		shaders[0]->use_shader();
		calculate_simple();
		convert_to_rgb();
		render();
		break;
	}
}

void Mandelbrot::main_loop(const int begin, const int end)
{
	for (int i = begin; i < end; ++i)
	{
		float x{ 0.0f };
		float y{ 0.0f };
		float tmp_x{ 0.0f };
		float const_x{ 0.0f };
		float const_y{ 0.0f };
		float distance{ 0.0f };

		const float x_range = 4.0f / zoom;
		const float y_range = 4.0f / zoom;

		for (int j = 0; j < height; ++j)
		{
			x = pos_x + 2.0f * ((float)i - 0.5f * width) / width * x_range;
			y = pos_y + 2.0f * ((float)j - 0.5f * height) / height * y_range;

			const_x = x;
			const_y = y;

			int iteration = 0;

			data[j * width + i] = 0.0f;
			while (iteration < max_iterations)
			{
				tmp_x = x;
				x = (x * x - y * y) + const_x;
				y = (2.0f * tmp_x * y) + const_y;

				distance = x * x + y * y;

				if (distance > 4.0f)
				{
					data[j * width + i] = (float)iteration / (float)max_iterations;
					break;
				}

				++iteration;
			}
		}
	}
}

void Mandelbrot::calculate_simple()
{
	main_loop(0, width);
}


void Mandelbrot::calculate_open_mp()
{
	const float x_range = 4.0f / zoom;
	const float y_range = 4.0f / zoom;

	#pragma omp parallel for 
	for (int i = 0; i < width; ++i)
	{
		float x{ 0.0f };
		float y{ 0.0f };
		float tmp_x{ 0.0f };
		float const_x{ 0.0f };
		float const_y{ 0.0f };
		float distance{ 0.0f };

		for (int j = 0; j < height; ++j)
		{
			x = pos_x + 2.0f * ((float)i - 0.5f * width) / width * x_range;
			y = pos_y + 2.0f * ((float)j - 0.5f * height) / height * y_range;

			const_x = x;
			const_y = y;

			int iteration = 0;

			data[j * width + i] = 0.0f;
			while (iteration < max_iterations)
			{
				tmp_x = x;
				x = (x * x - y * y) + const_x;
				y = (2.0f * tmp_x * y) + const_y;

				distance = x * x + y * y;

				if (distance > 4.0f)
				{
					data[j * width + i] = (float)iteration / (float)max_iterations;
					break;
				}

				++iteration;
			}
		}
	}
}


void Mandelbrot::calculate_thread()
{
	const size_t n_threads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(n_threads);

	const float x_range = 4.0f / zoom;
	const float y_range = 4.0f / zoom;

	for (int thread_id = 0; thread_id < n_threads; thread_id++)
	{
		int section_width = width / n_threads;
		int start_index = thread_id * section_width;
		int end_index = (thread_id + 1) * section_width;

		threads[thread_id] = std::thread(&Mandelbrot::main_loop, this, start_index, end_index);
	}

	for (int thread = 0; thread < n_threads; thread++)
	{
		threads[thread].join();
	}
}

void Mandelbrot::calculate_shader()
{
	shaders[1]->set_vec3("position_and_zoom", pos_x, pos_y, zoom);
}


void Mandelbrot::convert_to_rgb()
{
	int i = 0;
	for (auto value : data)
	{
		texture[i + 0] = (unsigned char)(value * 255.0f);
		texture[i + 1] = (unsigned char)(value * 255.0f);
		texture[i + 2] = (unsigned char)(value * 255.0f);
		i += 3;
	}

	texture.set_texture();
}

void Mandelbrot::render()
{
	texture.use_texture();
	glm::mat4 ortho = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 10.0f);
	shaders[0]->set_mat4("projection", ortho);
	shaders[1]->set_mat4("projection", ortho);
	canvas.render();
}










//void Mandelbrot::print()
//{
//	for (int i = 0; i < width; ++i)
//	{
//		for (int j = 0; j < height; ++j)
//		{
//			std::cout << data[j * width + i] << " ";
//		}
//		std::cout << "\n";
//	}
//}
//
//void Mandelbrot::print_texture()
//{
//	for (int i = 0; i < width; ++i)
//	{
//		for (int j = 0; j < height; ++j)
//		{
//			std::cout << (unsigned int)texture[3 * j * width + 3 * i] << " "; // << texture[3 * i * height + 3 * j + 1] << " " << " " << texture[3 * i * height + 3 * j + 2] << " ";
//		}
//		std::cout << "\n";
//	}
//}
