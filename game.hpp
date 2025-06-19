#ifndef GAME_HPP
#define GAME_HPP
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "consts.hpp"
#include "board.hpp"
#include "fps.hpp"
enum {sdl_init_flag = SDL_INIT_EVERYTHING};
enum {sdl_render_flag = SDL_RENDERER_ACCELERATED};
class game
{
	enum {delay_t = 16};
	int g_width;
	int g_height;
        int sdl_init_flags;
        int sdl_render_flags;	
        const char* game_name = "Game of Life\n";	
        SDL_Window* w;
        SDL_Renderer* r;
        SDL_Event event;
        bool is_running = true;	
#if 0	
	bool is_paused = false;
#else
	bool is_paused = true;
#endif	
	board b;
	fps f;
	void init_sdl();
	void create_window();
	void create_render();
	void ttf_init();
	void quit_sdl();
	void game_events();
	void game_draw();
	void game_update();
	void game_draw_initial();
public:	
	game();
	game(int width, int height, int speed, int sdl_init_flag, int sdl_render_flag);
	void game_setup();
	void game_run();
	~game();
};
#endif
