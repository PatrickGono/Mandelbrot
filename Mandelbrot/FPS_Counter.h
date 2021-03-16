#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class FPS_Counter
{
private:
	float current_time{ 0.0f };
	float last_time{ 0.0f };
	unsigned int n_frames{ 0 };
	float time_interval{ 1.0f };

public:
	FPS_Counter();
	FPS_Counter(float interval);

	void count_fps();
};

