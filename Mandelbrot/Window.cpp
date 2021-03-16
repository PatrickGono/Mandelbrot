#include "Window.h"

void Window::handle_keys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* the_window = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			the_window->keys[key] = true;
		}

		if (action == GLFW_RELEASE)
		{
			the_window->keys[key] = false;
		}
	}
}


void Window::handle_mouse(GLFWwindow* window, double x_pos, double y_pos)
{
	Window* the_window = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (!the_window->left_mouse_button_pressed)
		return;

	if (the_window->mouse_first_moved)
	{
		the_window->last_x = x_pos;
		the_window->last_y = y_pos;
		the_window->mouse_first_moved = false;
	}

	the_window->x_change = the_window->last_x - x_pos;
	the_window->y_change = the_window->last_y - y_pos;

	the_window->last_x = x_pos;
	the_window->last_y = y_pos;
}

void Window::handle_mouse_buttons(GLFWwindow* window, int button, int action, int mods)
{
	Window* the_window = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		the_window->left_mouse_button_pressed = true;
		the_window->mouse_first_moved = true;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		the_window->left_mouse_button_pressed = false;
	}
}

void Window::handle_mouse_scroll(GLFWwindow* window, double x_offset, double y_offset)
{
	Window* the_window = static_cast<Window*>(glfwGetWindowUserPointer(window));

	the_window->z_change = y_offset;
}


void Window::create_callbacks()
{
	glfwSetKeyCallback(main_window, handle_keys);
	glfwSetCursorPosCallback(main_window, handle_mouse);
	glfwSetMouseButtonCallback(main_window, handle_mouse_buttons);
	glfwSetScrollCallback(main_window, handle_mouse_scroll);
}

Window::Window(GLint window_width, GLint window_height) : width(window_width), height(window_height), main_window(nullptr), buffer_width(0), buffer_height(0), last_x(0), last_y(0), last_z(0), x_change(0), y_change(0), z_change(0)
{
	for (unsigned int i = 0; i < 1024; ++i)
	{
		keys[i] = false;
	}

	mouse_first_moved = true;
	left_mouse_button_pressed = false;
}

Window::~Window()
{
	glfwDestroyWindow(main_window);
	glfwTerminate();
}

int Window::initialize()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "GLFW initialization failed!\n";
		glfwTerminate();
		return 1;
	}

	// Set OpenGL version to 3.3, with forward but no backward compatibility 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create a window
	main_window = glfwCreateWindow(width, height, "atoms", nullptr, nullptr);
	if (!main_window)
	{
		std::cout << "GLFW window creation failed!\n";
		glfwTerminate();
		return 1;
	}

	// Get buffer size information
	glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height);

	// Set context for GLEW to use
	glfwMakeContextCurrent(main_window);

	// Handle keys + mouse input
	create_callbacks();
	glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialization failed!\n";
		glfwDestroyWindow(main_window);
		glfwTerminate();
		return 1;
	}

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);


	// Set up Viewport size
	glViewport(0, 0, buffer_width, buffer_height);

	glfwSetWindowUserPointer(main_window, this);

	return 0;
}

GLfloat Window::get_x_change()
{
	GLfloat change = x_change;
	x_change = 0.0f;
	return change;
}

GLfloat Window::get_y_change()
{
	GLfloat change = y_change;
	y_change = 0.0f;
	return change;
}

GLfloat Window::get_z_change()
{
	GLfloat change = z_change;
	z_change = 0.0f;
	return change;
}

