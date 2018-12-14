#include "tetromino.hh"
#include <iostream>

#include <stdlib.h>     
#include <time.h>  

Tetromino::Tetromino(Well* well):
	well(well),
	x(Constants::WIDTH/2 -5/2),
	y(-2),
	angle(0)
{
	srand (time(NULL));
	type = Type(rand()%7);
}

void Tetromino::move(int direction)
{
	checkRotation();
	if(direction == 0)
	{
		if(checkLeftSide())
		{
		x--;
		}
	}
	else
	{
		if(checkRightSide())
		{
		x++;
		}
	}
}

void Tetromino::rotate()
{
	if(checkRotation())
	{
		if(angle == 3)
			angle = 0;
		else
			angle++;
	}
}

void Tetromino::reset()
{	

	for(auto j=0; j<5; ++j)
		for(auto i=0; i<5; ++i)
		{
			if(shapes[type][angle][j][i] != 0)
			{
				well->data[x+i][y+j] = shapes[type][angle][j][i];
			}
		}

	int scoreCounter = 0;

	for(auto j=0; j<Constants::HEIGHT; j++)
	{
		int counter = 0;
		for(auto i=0; i<Constants::WIDTH; i++)
		{
			if(well->data[i][j] != 0)
			{
				counter++;
			}
		}
		if(counter == Constants::WIDTH)
		{
			for(auto k=0; k<Constants::WIDTH; k++)
				well->data[k][j] = 0;

			for(auto n=j; n>1; n--)
				for(auto m=0; m<Constants::WIDTH; m++)
				{
				well->data[m][n] = well->data[m][n-1];
				}
			scoreCounter++;
		}
	}

	switch(scoreCounter)
	{
		case 1:
			score += 40;
			break;
		case 2:
			score += 100;
			break;
		case 3:
			score += 300;
			break;
		case 4:
			score += 1200;
			break;
	}



	x = Constants::WIDTH/2 -4/2;
	y = -2;
	angle = 0;
	type = Type(rand()%7);



}

bool Tetromino::checkRotation()
{
	int check;
	if(angle==3)
		check = 0;
	else
		check = angle + 1;

	for(auto j=0; j<5; j++)
		for(auto i=0; i<5; i++)
			if(shapes[type][check][j][i] !=0)
			{
				if((x+i<0)||(x+i>=Constants::WIDTH))
					return false;
				if(well->data[x+i][y+j] != 0)
					return false;
			}

	return true;	

}
bool Tetromino::checkLeftSide()
{
	for(auto j=0; j<5; j++)
		for(auto i=0; i<5; i++)
		{
			if(shapes[type][angle][j][i] != 0)
			{
				if(x+i == 0)
					return false;
			
			else if(well->data[x+i-1][y+j] != 0)
			{
				return false;
			}
			}
		}
	return true;
}

bool Tetromino::checkRightSide()
{
	for(auto j=0; j<5; j++)
		for(auto i=0; i<5; i++)
		{
			if(shapes[type][angle][j][i] != 0)
			{
				if(x+i+1 == Constants::WIDTH)
					return false;
			
			else if(well->data[x+i+1][y+j] != 0)
			{
				return false;
			}
			}
		}
	return true;
}

bool Tetromino::checkDownCollision()
{
	for(auto j=0; j<5; j++)
		for(auto i=0; i<5; i++)
		{
			if(shapes[type][angle][j][i] != 0)
			{
			if(j+y == Constants::HEIGHT-1)
			{
				reset();
				return true;
			}

			else if(well->data[i+x][j+y+1] != 0)
			{
				if(j+y>0)
				reset();
				else
				{
					for(auto k=0;k<Constants::WIDTH;k++)
						for(auto l=0; l<Constants::HEIGHT; l++)
							well->data[k][l] = 0;
					score = 0;
				}
				return true;
			}
			}

		}

	return false;
}

void Tetromino::update()
{
	if(!checkDownCollision())
	{
		y++;
	}

}




void Tetromino::draw(SDL_Renderer* renderer, SDL_Texture* blocksTexture)
{
	for(auto i=0; i<5; i++)
		for(auto j=0; j<5; j++)
		{
			if(shapes[type][angle][j][i] != 0)
			{
				SDL_Rect posRect{(x+i+1)*Constants::BLOCK_SIZE, (y+j)*Constants::BLOCK_SIZE, Constants::BLOCK_SIZE, Constants::BLOCK_SIZE};
				//SDL_Rect posRect{0, 0, Constants::BLOCK_SIZE, Constants::BLOCK_SIZE};
				SDL_Rect texRect{(type)*8, 0, 8, 8};
				SDL_RenderCopy(renderer, blocksTexture, &texRect, &posRect);
			}
		}
}
