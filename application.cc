#include "application.hh"
#include <stdexcept>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

Application::Application()
{
	auto res = SDL_Init(SDL_INIT_VIDEO);
	if(res != 0)
		throw std::runtime_error(SDL_GetError());

	if(!IMG_Init(IMG_INIT_PNG))
		throw std::runtime_error(SDL_GetError());

	if(TTF_Init() == -1)
		throw std::runtime_error(SDL_GetError());



	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::BLOCK_SIZE * (Constants::WIDTH+6), Constants::BLOCK_SIZE * Constants::HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);


	auto surface = IMG_Load("assets/blocks.png");
	if(!surface)
		throw std::runtime_error(SDL_GetError());
	blocksTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	tetromino = Tetromino(&well);


	uiBlockPos.w = Constants::BLOCK_SIZE;
	uiBlockPos.h = Constants::BLOCK_SIZE;


	font = TTF_OpenFont("assets/font.ttf",26);
	

	SDL_Surface* tmpSurface = TTF_RenderText_Solid(font, "SCORE", fontColor);
	scoreLabelTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	
	scoreLabelRect.w = tmpSurface->w;
	scoreLabelRect.h = tmpSurface->h;
	SDL_FreeSurface(tmpSurface);


	SDL_Surface* tmpSurface2 = TTF_RenderText_Solid(font, "0", fontColor);
	scoreTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface2);
	
	scoreRect.w = tmpSurface2->w;
	scoreRect.h = tmpSurface2->h;
	SDL_FreeSurface(tmpSurface2);


}

void Application::handleEvents()
{
	while(SDL_PollEvent(&event) != 0)
	{
		switch(event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_d:
						tetromino.move(1);
						break;
					case SDLK_a:
						tetromino.move(0);
						break;
					case SDLK_f:
						tetromino.rotate();
						break;
					case SDLK_s:
						sPressed = true;
						break;
				}
				break;


			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					case SDLK_s:
						sPressed = false;
						break;
				}
				break;
		}
	}
	
}
void Application::render()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	uiBlockPos.x = 0;	
	for(auto i=0; i<Constants::HEIGHT; i++)
	{
		uiBlockPos.y = i*Constants::BLOCK_SIZE;
		SDL_RenderCopy(renderer, blocksTexture, &uiBlockTex, &uiBlockPos);
	}
	
	uiBlockPos.x = (Constants::WIDTH+1)*Constants::BLOCK_SIZE;
	for(auto i=0; i<Constants::HEIGHT; i++)
	{
		uiBlockPos.y = i*Constants::BLOCK_SIZE;
		SDL_RenderCopy(renderer, blocksTexture, &uiBlockTex, &uiBlockPos);
	}

	well.draw(renderer, blocksTexture);
	tetromino.draw(renderer, blocksTexture);


	SDL_RenderCopy(renderer, scoreLabelTexture, NULL, &scoreLabelRect);
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

	SDL_RenderPresent(renderer);

}

void Application::update()
{
	tetromino.update();
	if(score != tetromino.score)
	{
		score = tetromino.score;

		
		SDL_Surface* tmpSurface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), fontColor);
		SDL_DestroyTexture(scoreTexture);
		scoreTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	
	scoreRect.w = tmpSurface->w;
	scoreRect.h = tmpSurface->h;
	SDL_FreeSurface(tmpSurface);





	}
	
}

int Application::run()
{
	auto frameTime = 0;
	auto prevTicks = SDL_GetTicks();
	while(!quit)
	{

		handleEvents();
		if(sPressed)
			speed = 100;
		else
			speed = 250;
		if(SDL_GetTicks()-prevTicks >= speed)
		{

		update();
		prevTicks = SDL_GetTicks();
		}
		render();

		frameTime = (SDL_GetTicks()/1000.f - frameTime);
		if(frameTime < 1000.f/60.f)
			SDL_Delay((1000.f/60.f)-frameTime);
		
	}
	return 1;
}
