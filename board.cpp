#include "board.hpp"

board::board()
{
}

void board::board_reset()
{
        int r, c;
        for (r = 0; r < rows; r++)
        {
                for (c = 0; c < columns; c++)
                        game_board[r * columns + c] = (rand() % 2) ? true : false;
        }
}

void board::board_clear()
{
        int r, c;
        for (r = 0; r < rows; r++)
        {
                for (c = 0; c < columns; c++)
                        game_board[r * columns + c] = false;
        }
}

void board::create_board(SDL_Renderer* r, int width, int height)
{
	b_renderer = r;
	rows = height / cell_size;
	columns = width / cell_size;
	errno = 0;
	game_board = (bool*)malloc(rows * columns);
	if (!game_board)
	{
		perror("Failed to allocate game_board. board::board()->malloc()\n");
		exit(1);
	}
        next_board = (bool*)malloc(rows * columns);
        if (!next_board)
        {
                perror("Failed to allocate next_board. board::board()->malloc()\n");
                exit(1);
        }
#if 0	
	srand(time(NULL));	
	board_reset();
#endif	
	board_clear();
}

void board::board_draw()
{
	int r, c;
	SDL_Rect rect = {0, 0, cell_size - cell_padding , cell_size - cell_padding};
	SDL_SetRenderDrawColor(b_renderer, CELL_COLOR);
	for (r = 0; r < rows; r++)
	{
		rect.y = cell_size * r;
		for (c = 0; c < columns; c++)
		{
			rect.x = cell_size * c;
			if (game_board[r * columns + c])
			{
				SDL_RenderFillRect(b_renderer, &rect);
			}
		}
	}
}

void board::board_edit(int x, int y)
{
	int c_column = x / cell_size;
	int r_row = y / cell_size;
	int index = r_row * columns + c_column;
	game_board[index] = !game_board[index];
}

void board::board_initial_cell_set(int x, int y)
{
		cords.c = x / cell_size;
		cords.r = y / cell_size;
		game_board[cords.r * columns + cords.c] = true;
}

void board::board_initial_draw()
{
        int r, c;
        SDL_Rect rect = {0, 0, cell_size - cell_padding , cell_size - cell_padding};
        SDL_SetRenderDrawColor(b_renderer, CELL_COLOR);
        rect.y = cell_size * cords.r;
        rect.x = cell_size * cords.c;
        SDL_RenderFillRect(b_renderer, &rect);
}

//correct this function 41
void board::board_update()
{
        int r, c, index, count_neighbour, r2, c2, wrap_r, wrap_c;
	bool* old_board;
        for (r = 0; r < rows; r++)
        {
                for (c = 0; c < columns; c++)
                {
			index = r * columns + c;
			count_neighbour = 0;
			for (r2 = r - 1; r2 <= r + 1; r2++)
			{
				for(c2 = c - 1; c2 <= c + 1; c2++)
				{
					if (r2 != r || c2 != c)
					{
						wrap_r = (r2 + rows) % rows;
						wrap_c = (c2 + columns) % columns;
						count_neighbour += game_board[wrap_r * columns + wrap_c];
					}
				}
			}
			if (count_neighbour == 3)
			{
				next_board[index] = true;
			}
			else if (game_board[index] && count_neighbour == 2)
			{
				next_board[index] = true;
			}
			else
			{
				next_board[index] = false;
			}
		}
        }
	old_board = game_board;
	game_board = next_board;
	next_board = old_board;
}

board::~board()
{
	if (game_board)
		free(game_board);
	if (next_board)
		free(next_board);
	b_renderer = NULL;
}

