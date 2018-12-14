#include "well.hh"
#include <iostream>

Well::Well():
	data{0}
{
	/*for(auto i=0;i<Constants::WIDTH; i++)
		for(auto j=0; j<Constants::HEIGHT; j++)
			data[i][j] = 6;*/
}

void Well::draw(SDL_Renderer* renderer, SDL_Texture* blocksTexture)
{
	for(auto x=0; x<Constants::WIDTH; ++x)
		for(auto y=0; y<Constants::HEIGHT; ++y)
		{
			if(data[x][y] != 0)
			{
				SDL_Rect posRect{(x+1)*Constants::BLOCK_SIZE, y*Constants::BLOCK_SIZE, Constants::BLOCK_SIZE, Constants::BLOCK_SIZE};
				SDL_Rect texRect{(data[x][y]-1)*8, 0, 8, 8};
				SDL_RenderCopy(renderer, blocksTexture, &texRect, &posRect);
			}
		}
}

