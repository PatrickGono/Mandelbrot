#include "FPS_Counter.h"

FPS_Counter::FPS_Counter() : time_interval(1.0f)
{
	last_time = (float)glfwGetTime();
}

FPS_Counter::FPS_Counter(float interval) : time_interval(interval)
{
	last_time = (float)glfwGetTime();
}

void FPS_Counter::count_fps()
{
	current_time = (float)glfwGetTime();
	n_frames++;

	if (current_time - last_time >= time_interval)
	{
		std::cout << time_interval * 1000.0f / n_frames << "ms / frame\n";
		n_frames = 0;
		last_time += time_interval;
	}
}
