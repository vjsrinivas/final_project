	/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
	and may not be redistributed without written permission.*/

	//Using SDL, SDL_image, standard IO, and strings
#include <stdio.h>
#include <string>
#include "dot.h"
#include "ltimer.h"
#include "ltexture.h"
#include "map.h"
	
	class GameState{
		public:
			~GameState();
			GameState();
			GameState(string enemyFile);
			bool playing = 1;
			int score;
			void moveEnemies(Map* map);
			bool isPlayOver;
			void addEnemy(string texturePath);
			void removeEnemy(int position);
		private:
			vector<Player*> enemies;
	};

	GameState::GameState() {}
	GameState::~GameState() {}

	void GameState::moveEnemies(Map* map){
		//dijistraks movement	
	}

	void GameState::addEnemy(string texturePath){
		Player* newEnemy = new Player(texturePath);
		enemies.push_back(newEnemy);
	}

	struct KillLog{
		string enemyName;
		int enemeyID;
	};


	//Screen dimension constants
	const int SCREEN_WIDTH = 1200;
	const int SCREEN_HEIGHT = 600;

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
	
		printf( "Failed to load dot texture!\n" );
		//success = false;

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

void HUD(LTexture& text, string str_say){
	TTF_Init();
	TTF_Font *gFont = TTF_OpenFont("lazy.ttf", 28);
	
	if(gFont == NULL){
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}

	string score_text = "score: ";        
	SDL_Color textColor = { 255, 255, 255, 0 };
	/*
	if(!text.loadFromRenderedText(gRenderer, str_say, textColor, gFont)){
		
	}*/



}

int main( int argc, char* args[] )
{
	// Create map system:
	Map* map_struct;

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
			//Setup map (move to init later):
			//map_struct = new Map(30,30,gRenderer);
			map_struct = new Map("test_map.txt", gRenderer);

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dot dot(SCREEN_WIDTH, SCREEN_HEIGHT, "./assets/characters/cs317_enemy_1.png");
			printf("loading main character.. path: %s\n", dot.controller->texturePath.c_str());
			if(!gDotTexture.loadFromFile(gRenderer, dot.controller->texturePath))
				exit(-1);
			SDL_Rect bottomViewport;
			SDL_Rect upperViewport;

			GameState* game = new GameState();
			LTexture text_place;

			//While application is running
			while( game->playing )
			{
				//Handle events on queue
				if(game->isPlayOver){
					// do combat stuff here:

				}
				else{
					while( SDL_PollEvent( &e ) != 0 )
					{
						//User requests quit
						if( e.type == SDL_QUIT )
						{
							game->playing = true;
						}	

						//Handle input for the dot
						dot.handleEvent( e );
					}

					//Move the dot
					dot.move();
					game->moveEnemies(map_struct);
				}
					
				//Clear screen	
				SDL_RenderClear( gRenderer );
				map_struct->Redraw(0,0);

				//Render objects
				dot.render(gDotTexture, gRenderer);

				/*
				upperViewport.x = 0;
				upperViewport.y = 0;
				upperViewport.w = SCREEN_WIDTH;
				upperViewport.h = (SCREEN_HEIGHT*4)/5;
				SDL_RenderSetViewport(gRenderer, &upperViewport);

				bottomViewport.x = 0;
				bottomViewport.y = SCREEN_HEIGHT-(SCREEN_HEIGHT/5);
				bottomViewport.w = SCREEN_WIDTH;
				bottomViewport.h = SCREEN_HEIGHT/5;
				SDL_RenderSetViewport(gRenderer, &bottomViewport);
				*/

				HUD(text_place, "hey");
				//Update screen
				SDL_RenderPresent( gRenderer );
			}
			delete game;
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
