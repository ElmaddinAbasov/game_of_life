#include "game.hpp"

void game::init_sdl()
{
	int res;
	res = SDL_Init(sdl_init_flags);
	if (res == -1)
	{
		fprintf(stderr, "ERROR: void game::init_sdl() -> %s\n", SDL_GetError());
		exit(1);
	}
}

void game::create_window()
{
	w = SDL_CreateWindow(game_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_width, g_height, 0);
	if (!w)
	{
		fprintf(stderr, "ERROR: void game::create_window() -> %s\n", SDL_GetError());
		exit(2);
	}
}

void game::create_render()
{
	r = SDL_CreateRenderer(w, -1, sdl_render_flags);
	if (!r)
	{
                fprintf(stderr, "ERROR: void game::create_render() -> %s\n", SDL_GetError());
                exit(3);		
	}
}

void game::ttf_init()
{
	int res;
	res = TTF_Init();
	if (res == -1)
	{
		fprintf(stderr, "ERROR: void game::ttf_init() -> %s\n", TTF_GetError());
		exit(4);
	}
}

void game::quit_sdl()
{
	SDL_Quit();
}

void game::game_events()
{
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT :
				is_running = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					b.board_edit(event.button.x, event.button.y);
				}
				else if (event.button.button == SDL_BUTTON_RIGHT)
				{
					b.board_initial_cell_set(event.button.x, event.button.y);
				}
				break;
			case SDL_KEYDOWN :
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE :
						is_running = false;
						break;	
					case SDL_SCANCODE_R :		//for board reset
						b.board_reset();
						break;
					case SDL_SCANCODE_C :
						b.board_clear();
						break;	
					case SDL_SCANCODE_F :
						f.fps_displayy();
						break;
					case SDL_SCANCODE_SPACE :
						is_paused = !is_paused;
						break;	
					case SDL_SCANCODE_UP :
						f.fps_increase_speed();
						break;	
					case SDL_SCANCODE_DOWN :
						f.fps_descrease_speed();
						break;	
					default :
						break;	
				}
			default :
				break;
		}
	}
}

void game::game_draw()
{
	SDL_SetRenderDrawColor(r, RENDER_COLOR);
        SDL_RenderClear(r);
	b.board_draw();
        SDL_RenderPresent(r);	
}

void game::game_update()
{
	if (!is_paused)
		b.board_update();
}

game::game()
{
}

game::game(int width, int height, int speed, int sdl_init_flag, int sdl_render_flag) : g_width(width), g_height(height), sdl_init_flags(sdl_init_flag), sdl_render_flags(sdl_render_flag)
{
	init_sdl();
	create_window();
	create_render();
	b.create_board(r, width, height);
	f.fps_set_speed(speed);
}

void game::game_draw_initial()
{
        SDL_SetRenderDrawColor(r, RENDER_COLOR);
        SDL_RenderClear(r);
//       b.board_initial_draw();
	b.board_draw();
        SDL_RenderPresent(r);
}

void game::game_setup()
{
	while (is_paused)
	{
		game_events();
//		game_update();
		game_draw_initial();
//		is_paused = false;
	}
}

void game::game_run()
{
	while (is_running)
	{
		game_events();
		game_update();
		game_draw();
		//SDL_Delay(delay_t * 2);
		f.fps_update();
	}
}

game::~game()
{
	quit_sdl();
	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);
	TTF_Quit();
}

