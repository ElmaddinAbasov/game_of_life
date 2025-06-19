#ifndef BOARD_HPP
#define BOARD_HPP
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "consts.hpp"
class board
{
	enum {cell_size = 10};
	enum {cell_padding = 2};
	SDL_Renderer* b_renderer;
	bool* game_board;		//game board
	bool* next_board;		//generate a new board 
	int rows;
	int columns;
	struct cord
	{
		int r = 1;			//rows
		int c = 1;			//columns
	}cords;
public:	
	board();
	void create_board(SDL_Renderer* r, int width, int height);
	void board_reset();
	void board_clear();
	void board_draw();
	void board_edit(int x, int y);
	void board_initial_cell_set(int x, int y);
	void board_initial_draw();
	void board_update();
	~board();
};
#endif
