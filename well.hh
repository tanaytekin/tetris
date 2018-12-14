#ifndef WELL_HH
#define WELL_HH
#include <SDL2/SDL.h>
#include "constants.hh"
struct Well
{
	Well();
	void draw(SDL_Renderer* renderer, SDL_Texture* blocksTexture);
	char data[Constants::WIDTH][Constants::HEIGHT];
};



#endif
