#include "Game.h"



Game::Game()
{

}


Game::~Game()
{

}

void Game::_init(const char* title, int xpos, int ypos, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Initialized subsystems." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		for (int j = 0; j < 60; ++j)
		{
			for (int i = 0; i < 60; ++i)
			{
				currentBoard[i][j] = 0;
			}
		}
		isRunning = true;
		isSetUp = false;
	}
	else
		isRunning = false;
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			int x, y, boardX, boardY;
			SDL_GetMouseState(&x, &y);
			boardX = std::floor((double)x / 10);
			boardY = std::floor((double)y / 10);
			if (currentBoard[boardX][boardY] == 0)
			{
				currentBoard[boardX][boardY] = 1;
				nextBoard[boardX][boardY] = 1;
			}
			else
			{
				currentBoard[boardX][boardY] = 0;
				nextBoard[boardX][boardY] = 0;
			}
		}
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			if (isSetUp == false)
			{
				isSetUp = true;
				SDL_SetWindowTitle(window, "Game of Life (running)");
			}
			else
			{
				isSetUp = false;
				SDL_SetWindowTitle(window, "Game of Life (set up)");
				for (int j = 0; j < 60; ++j)
				{
					for (int i = 0; i < 60; ++i)
					{
						currentBoard[i][j] = 0;
						nextBoard[i][j] = 0;
					}
				}
			}
		}
		break;
	default:
		break;
	}
}

void Game::update()
{
	if (isSetUp == true)
	{
		for (int j = 0; j < 60; ++j)
		{
			for (int i = 0; i < 60; ++i)
			{
				int numNeighbors = neighbors(i, j);
				if (numNeighbors < 2 && currentBoard[i][j] == 1)
					nextBoard[i][j] = 0;
				else if (numNeighbors > 3 && currentBoard[i][j] == 1)
					nextBoard[i][j] = 0;
				else if (numNeighbors == 3 && currentBoard[i][j] == 0)
					nextBoard[i][j] = 1;
			}
		}
		for (int j = 0; j < 60; ++j)
		{
			for (int i = 0; i < 60; ++i)
			{
				currentBoard[i][j] = nextBoard[i][j];
			}
		}
		SDL_Delay(100);
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

	for (int i = 0; i < 60; ++i)
	{
		SDL_RenderDrawLine(renderer, 0, i * 10, 600, i*10);
		SDL_RenderDrawLine(renderer, i * 10, 0, i * 10, 600);
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int j = 0; j < 60; ++j)
	{
		for (int i = 0; i < 60; ++i)
		{
			if (currentBoard[i][j] == 1)
			{
				SDL_Rect aliveCell = { i * 10, j * 10, 10, 10 };
				SDL_RenderFillRect(renderer, &aliveCell);
			}
		}
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

}
//x and y are the current coordinates
int Game::neighbors(int x, int y)
{
	int aliveNeighbors = 0;
	if (x != 0 && currentBoard[x][y-1] == 1) //check to the left
		aliveNeighbors++;
	if (x != 59 && currentBoard[x][y+1] == 1) //check to the right
		aliveNeighbors++;
	if (y != 0 && currentBoard[x - 1][y] == 1) //check above
		aliveNeighbors++;
	if (y != 59 && currentBoard[x + 1][y] == 1) //check below
		aliveNeighbors++;
	if (x != 0 && y != 0 && currentBoard[x - 1][y - 1] == 1) //check upper left
		aliveNeighbors++;
	if (x != 59 && y != 0 && currentBoard[x - 1][y + 1] == 1) //check upper right
		aliveNeighbors++;
	if (x != 0 && y != 59 && currentBoard[x + 1][y - 1] == 1) //check lower left
		aliveNeighbors++;
	if (x != 59 && y != 59 && currentBoard[x + 1][y + 1] == 1) // check lower right
		aliveNeighbors++;
	return aliveNeighbors;
}
