#pragma once
#include "game.h"

//The dot that will move around on the screen
	class Dot
	{
		public:
			//The dimensions of the dot
			static const int DOT_WIDTH = 30;
			static const int DOT_HEIGHT = 30;

			//Maximum axis velocity of the dot
			static const int DOT_VEL = 30;

			//Initializes the variables
			Dot();
      Dot(const int, const int);

			//Takes key presses and adjusts the dot's velocity
			void handleEvent( SDL_Event& e );

			//Moves the dot
			void move();

			//Shows the dot on the screen
			void render(LTexture& gDotTexture, SDL_Renderer* gRenderer);

		private:
			//The X and Y offsets of the dot
			int mPosX, mPosY;

			//The velocity of the dot
			int mVelX, mVelY;
      int SCREEN_WIDTH;
      int SCREEN_HEIGHT;
	};
