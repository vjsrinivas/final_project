#include "dot.h"

Dot::Dot()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	controller = new Player();
}

Dot::Dot(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, std::string texturePath){
  //Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
 
	controller = new Player(texturePath);

  //set screen size:
  this->SCREEN_WIDTH = SCREEN_WIDTH;
  this->SCREEN_HEIGHT = SCREEN_HEIGHT;
}

void Dot::handleEvent( SDL_Event& e)
{
	//If a key was pressed
	/*
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
			case SDLK_UP: mVelY -= DOT_VEL; break;
			case SDLK_DOWN: mVelY += DOT_VEL; break;
			case SDLK_LEFT: mVelX -= DOT_VEL; break;
			case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}*/
	//If a key was released
	//else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	
	if(e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		controller->movesLeft--;
		//cout << "key let go" << endl;
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
			case SDLK_UP: mVelY -= DOT_VEL; break;
			case SDLK_DOWN: mVelY += DOT_VEL; break;
			case SDLK_LEFT: mVelX -= DOT_VEL; break;
			case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}
}

void Dot::move()
{
	if(mVelX != 0){
		mPosX += mVelX;
		controller->pos.x += mVelX/30;
	}
	else if(mVelY != 0){
		mPosY += mVelY;
		controller->pos.y += mVelY/30;
	}

	////
	////
	//Move the dot left or right
	//mPosX += mVelX;

	//If the dot went too far to the left or right
	if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
	{
		//Move back
		mPosX -= mVelX;
		controller->pos.x -= mVelX/30;
	}

	//Move the dot up or down
	//mPosY += mVelY;

	//If the dot went too far up or down
	if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
	{
		//Move back
		mPosY -= mVelY;
		controller->pos.y -= mVelY/30;
	}

	//printf("mposx: %i | mposy: %i | mvelx: %i | mvely: %i | dotheight: %i | screenheight %i\n", mPosX, mPosY, mVelX, mVelY, DOT_HEIGHT, SCREEN_HEIGHT);
	//controller->printPos();
	//printf("Real location is: %i %i\n", mPosX, mPosY);
	mVelX = 0;
	mVelY = 0;
}

void Dot::render(LTexture& gDotTexture, SDL_Renderer* gRenderer)
{
	//Show the dot
	gDotTexture.render(gRenderer, mPosX, mPosY );
}
