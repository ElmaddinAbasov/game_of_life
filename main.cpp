#include "game.hpp"
int main(int argc, char** argv)
{
	if (argc < 4)
	{
		fprintf(stderr, "ERROR: Provide window width or height or game speed\n");
		exit(1);
	}
	game g(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), sdl_init_flag, sdl_render_flag);
	g.game_setup();
	g.game_run();
	_exit(0);
}
