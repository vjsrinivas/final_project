	/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
	and may not be redistributed without written permission.*/

	//Using SDL, SDL_image, standard IO, and strings
#include <stdio.h>
#include <string>
#include "map.cpp"
#include "ltexture.cpp"
#include "dot.cpp"

	//Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	//The application time based timer
	class LTimer
	{
		public:
			//Initializes variables
			LTimer();

			//The various clock actions
			void start();
			void stop();
			void pause();
			void unpause();

			//Gets the timer's time
			Uint32 getTicks();

			//Checks the status of the timer
			bool isStarted();
			bool isPaused();

		private:
			//The clock time when the timer started
			Uint32 mStartTicks;

			//The ticks stored when the timer was paused
			Uint32 mPausedTicks;

			//The timer status
			bool mPaused;
			bool mStarted;
	};

	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	//Frees media and shuts down SDL
	void close();

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Scene textures
	LTexture gDotTexture;

	bool init()
	{
		//Initialization flag
		bool success = true;

		//Initialize SDL
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Set texture filtering to linear
			if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			{
				printf( "Warning: Linear texture filtering not enabled!" );
			}

			//Create window
			gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
			if( gWindow == NULL )
			{
				printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Create vsynced renderer for window
				gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
				if( gRenderer == NULL )
				{
					printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
					success = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if( !( IMG_Init( imgFlags ) & imgFlags ) )
					{
						printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
						success = false;
					}
				}
			}
		}

		return success;
	}

	bool loadMedia()
	{
		//Loading success flag
		bool success = true;

		//Load dot texture
		if( !gDotTexture.loadFromFile(gRenderer, "cs317_char.bmp") )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gDotTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	// Create map system:
	Map* map_struct = new Map();

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dot dot(SCREEN_WIDTH, SCREEN_HEIGHT);

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the dot
					dot.handleEvent( e );
				}

				//Move the dot
				dot.move();

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render objects
				dot.render(gDotTexture, gRenderer);

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}