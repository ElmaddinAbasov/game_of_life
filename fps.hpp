#ifndef FPS_HPP
#define FPS_HPP
#include <SDL2/SDL.h>
#include "consts.hpp"
class fps
{
	Uint32 last_time; 	//how much time has passed
	double target_duration;
	double carry_delay;
	double max_delay;
	Uint32 fps_last_time;
	Uint32 fps_counter;
	bool fps_display;
	Uint32 fps_time_since(Uint32 last_time, Uint32* new_last_time);
	void fps_update_display();
public:
	fps();
	void fps_set_speed(int speed);
	void fps_displayy();
	void fps_update();
	void fps_increase_speed();
	void fps_descrease_speed();
	double get_target_duration()
	{
		return target_duration;
	}
	~fps();
};
#endif
