#pragma once
#include <vector>
#include <iostream>
#include <omp.h>
#include <thread>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Texture.h"
#include "Shader.h"
#include "Canvas.h"

enum class Calculation_Type
{
	SIMPLE,
	OPEN_MP,
	THREAD,
	SHADER
};

class Mandelbrot
{
public:
	Mandelbrot(int width, int height);

	void process_keyboard(bool keys[]);
	void calculate_and_render();
	void render();

private:
	int width, height;
	float pos_x, pos_y, zoom;
	int max_iterations;
	Calculation_Type calculation_type{ Calculation_Type::SIMPLE };
	Texture texture;
	std::vector<float> data;
	std::vector<std::unique_ptr<Shader>> shaders;
	Canvas canvas;

	void print_startup();

	void calculate_simple();
	void calculate_open_mp();
	void calculate_thread();
	void calculate_shader();

	void main_loop(int begin, int end);

	void convert_to_rgb();

	std::vector<float> calculate_color_ranges();


};

