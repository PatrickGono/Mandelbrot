// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "CommonValues.h"
#include "Window.h"
#include "FPS_Counter.h"
#include "Mandelbrot.h"


void handle_input(Mandelbrot& mandelbrot, Window& window)
{
	glfwPollEvents();
	mandelbrot.process_keyboard(window.get_keys());
	return;
}

void render_pass(Mandelbrot& mandelbrot, Window& window)
{
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mandelbrot.calculate_and_render();

	window.swap_buffers();
	return;
}

int main()
{
	const int screen_width{ 1080 };
	const int screen_height{ 1080 };

	Window window(screen_width, screen_height);
	window.initialize();

	Mandelbrot mandelbrot(screen_width, screen_height);

	FPS_Counter fps_counter;

	while (!window.get_should_close())
	{
		fps_counter.count_fps();

		handle_input(mandelbrot, window);

		render_pass(mandelbrot, window);
	}

	glfwTerminate();
	return 0;

}