#include <GL\glew.h>
#include <iostream>
#include <Windows.h>
#include <SDL\SDL.h>
#include "Game.h"
#include "Input.h"
#include "global_variables.h"

using namespace std;

int screen_width = 1080;
int screen_height = 720;

int main(int argc, char** argv) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = nullptr;

	bool running = true;

	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	//gWidth = dm.w - 2;
	//gHeight = dm.h - 60;
	gWidth = screen_width - 2;
	gHeight = screen_height - 60;

	window = SDL_CreateWindow("Try hard!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gWidth, gHeight, SDL_WINDOW_OPENGL); // can get the border & titlebar sizes to fix a more precise windowed "fullscreen"
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
		std::cout << "SDLFEL";
	GLenum error = glewInit();
	if (error != GLEW_OK)
		std::cout << "GlewFel!";
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	glClearColor(0.7f, 0.7f, 1.0f, 1.0);
	glEnable(GL_DEPTH_TEST);

	Input input(window);
	Game game;
	
	SDL_GL_SetSwapInterval( 1 );

	float dt = 0;
	int timeStamp = SDL_GetTicks(); int temp;
	bool actionMode = true;
	while (running)
	{
		temp = SDL_GetTicks();
		dt = (float)(temp - timeStamp) / 1000.f;
		timeStamp = temp;
		running = input.update();

		if (input.keyPressed(SDLK_t))
			actionMode = !actionMode;

		if (actionMode)
			game.run(&input, dt);
		else
			game.tacticalRun(&input, dt);


		if( input.keyPressed( SDLK_ESCAPE ) )
			running = false;
		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}