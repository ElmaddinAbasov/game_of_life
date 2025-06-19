#include "fps.hpp"

fps::fps()
{
//	target_duration = TARGET_DURATION;
	max_delay = 50;
	last_time = SDL_GetTicks();
	fps_last_time = last_time;
	carry_delay = 0;
	fps_counter = 0;
	fps_display = false;
}

void fps::fps_set_speed(int speed)
{
	target_duration = speed;
}

void fps::fps_displayy()
{
	if (fps_display)
	{
		fps_display = false;
		return;
	}
	else
	{
		fps_display = true;
		fps_counter = 0;
		fps_last_time = SDL_GetTicks();
	}
}

Uint32 fps::fps_time_since(Uint32 last_time, Uint32* new_last_time)
{
	Uint32 current_time = SDL_GetTicks();
	Uint32 elapsed_time = 0;
	if (current_time < last_time)
	{
		elapsed_time = (Uint32)-1 - last_time + current_time;
	}
	else
	{
		elapsed_time = current_time - last_time;
	}
	if (new_last_time)
		*new_last_time = current_time;
	return elapsed_time;
}

void fps::fps_update_display()
{
	if (fps_display)
	{
		if (fps_time_since(last_time, NULL) >= 1000)
		{	
			printf("%d\n", fps_counter);
			fps_counter = 0;
			fps_last_time += 1000;
		}
		fps_counter++;
	}
}

void fps::fps_update()
{
	Uint32 delay;
	Uint32 elapsed_time = fps_time_since(last_time, NULL);
	double duration = target_duration + carry_delay;
	if (duration > elapsed_time)
	{
		delay = (Uint32)duration - elapsed_time;
		SDL_Delay(delay);
	}
	elapsed_time = fps_time_since(last_time, &last_time);
	carry_delay = duration - elapsed_time;
	if (carry_delay > max_delay)
	{
		carry_delay = max_delay;
	}
	else if (carry_delay < -max_delay)
	{
		carry_delay = -max_delay;
	}
	fps_update_display();
}

void fps::fps_increase_speed()
{
	if (target_duration > 8)
		target_duration /= 2;
}

void fps::fps_descrease_speed()
{
	if (target_duration < 1024)
		target_duration *= 2;
}

fps::~fps()
{
}
