#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
	GLFWwindow* main_window;
	GLint buffer_width, buffer_height;
	GLint width, height;
	bool keys[1024];

	static void handle_keys(GLFWwindow* window, int key, int code, int action, int mode);
	void create_callbacks();

	GLfloat last_x;
	GLfloat last_y;
	GLfloat last_z;
	GLfloat x_change;
	GLfloat y_change;
	GLfloat z_change;
	bool mouse_first_moved;
	bool left_mouse_button_pressed;

	static void handle_mouse(GLFWwindow* window, double x_pos, double y_pos);

	static void handle_mouse_buttons(GLFWwindow* window, int button, int action, int mods);

	static void handle_mouse_scroll(GLFWwindow* window, double x_pos, double y_pos);


public:
	Window(GLint window_width, GLint window_height);
	~Window();

	int initialize();

	GLfloat get_buffer_width() { return buffer_width; }
	GLfloat get_buffer_height() { return buffer_height; }

	bool get_should_close() { return glfwWindowShouldClose(main_window); }

	void swap_buffers() { glfwSwapBuffers(main_window); }

	bool* get_keys() { return keys; }

	GLfloat get_x_change();
	GLfloat get_y_change();
	GLfloat get_z_change();
};

