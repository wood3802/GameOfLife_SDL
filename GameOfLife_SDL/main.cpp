#include "SDL.h"
#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();

	game->_init("Game of Life (set up)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600);

	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();

	return 0;
}