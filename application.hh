#ifndef APPLICATION_HH
#define APPLICATION_HH

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "well.hh"
#include "tetromino.hh"
#include "constants.hh"

class Application
{
public:
	Application();
	int run();

private:
	bool quit = false;
	bool sPressed = false;
	SDL_Event event;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* blocksTexture;

	SDL_Rect uiBlockPos;
	const SDL_Rect uiBlockTex {56,0,8,8};

	TTF_Font *font = NULL;
	const SDL_Color fontColor{0, 0, 0};
	SDL_Texture* scoreTexture = NULL;
	SDL_Rect scoreRect{(Constants::WIDTH+3)*Constants::BLOCK_SIZE,(Constants::HEIGHT/2-2)*Constants::BLOCK_SIZE,100,100};

	SDL_Texture* scoreLabelTexture = NULL;
	SDL_Rect scoreLabelRect{(Constants::WIDTH+3)*Constants::BLOCK_SIZE,(Constants::HEIGHT/2-3)*Constants::BLOCK_SIZE,100,100};

	Well well;
	Tetromino tetromino = nullptr;
	void render();
	void handleEvents();
	void update();
	int speed = 250;
	int score = 0;
};

#endif
