#ifndef TETROMINO_HH
#define TETROMINO_HH
#include <SDL2/SDL.h>
#include "constants.hh"
#include "well.hh"
class Tetromino
{
public:
	Tetromino(Well* well);
	void update();
	void move(int direction);
	void rotate();
	void draw(SDL_Renderer* renderer, SDL_Texture* blocksTexture);
	int score = 0;
private:
	Well* well;
	Type type;
	char shape[4][5][5];
	int x;
	int y;
	int angle; // 0-0deg, 1-90deg, 2-180deg, 3-270-deg

	bool checkDownCollision();
	bool checkLeftSide();
	bool checkRightSide();
	bool checkRotation();
	void reset();

};




#endif

