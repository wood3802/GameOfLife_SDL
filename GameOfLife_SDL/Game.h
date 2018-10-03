#pragma once
#include <iostream>
#include "SDL.h"

class Game
{
public:
	Game();
	~Game();

	void _init(const char* title, int xpos, int ypos, int width, int height);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	int neighbors(int x, int y);
	

private:
	bool isRunning;
	bool isSetUp;
	SDL_Window *window;
	SDL_Renderer *renderer;
	int currentBoard[60][60];
	int nextBoard[60][60];
	SDL_Rect positions[60][60];
};

