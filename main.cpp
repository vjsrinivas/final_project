		/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
		and may not be redistributed without written permission.*/

		//Using SDL, SDL_image, standard IO, and strings
#include <stdio.h>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "ltimer.h"
#include "ltexture.h"
#include "map.h"

using namespace std;

		class GameState{
			public:
				GameState();
				GameState(string filename,string enemyFile, SDL_Renderer*);
				~GameState();
				bool playing = 1;
				int score = 0;
				bool fightEnemies(Player*& controller, vector<Position>& pos, Map*& map);
				bool isPlayOver;
				void addEnemy(string texturePath);
				void removeEnemy(int position);
				void placeItem(int item_pos, int x, int y);
				vector<Item*> get_items();
				vector<Enemy*> get_enemies();
			private:
				void loadenemytextures();
				vector<Item*> items;
				SDL_Renderer* render;
				vector<Enemy*> enemies;
		};

		void GameState::loadenemytextures(){
			for(int i=0; i < enemies.size(); i++){
				enemies[i]->texture->loadFromFile(render, enemies[i]->texturePath);
			}
		}

		bool GameState::fightEnemies(Player*& controller, vector<Position>& pos, Map*& map){
			//fight one and then the other:
			srand(time(NULL));
			while(pos.size() != 0){
				for(int i=0; i < pos.size(); i++){
					// attack player
					Node* enemy_node = map->GetNode(pos[i].y, pos[i].x);
					int damageTaken = rand()%enemy_node->currChar->maxdmg + 1;
					int damageBlocked = 0; //shield value
					damageTaken -= damageBlocked;
					controller->health -= damageTaken;

					//attack enemy:
					if(controller->currWeap != NULL){
						int damageGiven = controller->currWeap->damage;
						if(controller->currShield != NULL){
							int damageLost = rand()%enemy_node->currChar->maxdef+1; //shield
							damageGiven -= damageLost;
						}
						if(damageGiven != 0)
							enemy_node->currChar->health -= rand()%damageGiven+1;
					}

					if(enemy_node->currChar->health <= 0){
						delete enemy_node->currChar;
						enemy_node->currChar = NULL;
						pos.erase(pos.begin()+i);
					}
					SDL_Delay(500);
				}

				if(controller->health <= 0){
					printf("\n\nYou lost the game :(\n\n");
					return false;	
				}
			}
			return true;
		}

		vector<Item*> GameState::get_items(){
			return items;
		}

		vector<Enemy*> GameState::get_enemies(){
			return enemies;
		}

		void GameState::placeItem(int item_pos, int x, int y){
			LTexture item_icon;
			if(item_icon.loadFromFile(render, items[item_pos]->texturePath)){
				item_icon.render(render,x*30,y*30);
			}
			else{
				printf("Error! failed to load texture for: %s\n", items[item_pos]->itemName.c_str());
			}

		}

		GameState::GameState() {}

		GameState::GameState(string filename, string enemyFile, SDL_Renderer* gRenderer){
			render = gRenderer;
			loadItemFile(render, filename, items);
			loadEnemyFile("enemy.txt", enemies);
			loadenemytextures();
			
			for(int i=0; i < items.size(); i++){
				cout << items[i]->itemName << endl;
			}
		}

		GameState::~GameState() {}

		void GameState::addEnemy(string texturePath){
			Enemy* newEnemy = new Enemy(texturePath);
			enemies.push_back(newEnemy);
		}

		struct KillLog{
			string enemyName;
			int enemeyID;
		};


		//Screen dimension constants
		const int SCREEN_WIDTH = 1080;
		const int SCREEN_HEIGHT = 1080;

		//Starts up SDL and creates window
		bool init();

		//Loads media
		bool loadMedia();

		//Frees media and shuts down SDL
		void close();

		//The window we'll be rendering to
		SDL_Window* gWindow = NULL;
    //SDL_Window* bWindow = NULL;

		//The window renderer
		SDL_Renderer* gRenderer = NULL;
    //SDL_Renderer* bRenderer = NULL;

    //Scene textures
		LTexture gDotTexture;
    //LTexture shieldTexture;
   // LTexture swordTexture;

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
				gWindow = SDL_CreateWindow( "SDL Tutorial", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS );
				//bWindow = SDL_CreateWindow( "Inventory", 0, 0, SCREEN_WIDTH-440, SCREEN_HEIGHT-600, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);

        if( gWindow == NULL )//|| bWindow == NULL)
				{
					printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
					success = false;
				}
				else
				{
					//Create vsynced renderer for window
					gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
					//bRenderer = SDL_CreateRenderer(bWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
					//gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED);

          if( gRenderer == NULL )//|| bRenderer == NULL )
					{
						printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
						success = false;
					}

					else
					{
						//Initialize renderer color
						SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            //SDL_SetRenderDrawColor(bRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

						//Initialize PNG loading
						int imgFlags = IMG_INIT_PNG;
						if( !( IMG_Init( imgFlags ) & imgFlags ) )
						{
							printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
							success = false;
						}

            //Initialize SDL_ttf
    				if( TTF_Init() == -1 )
    				{
    					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
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
    //shieldTexture.free();
    //swordTexture.free();

		//Destroy window
		SDL_DestroyRenderer( gRenderer );
		SDL_DestroyWindow( gWindow );
		gWindow = NULL;
		gRenderer = NULL;

    //SDL_DestroyRenderer(bRenderer);
    //SDL_DestroyWindow(bWindow);
    //bWindow = NULL;
    //bRenderer = NULL;

		//Quit SDL subsystems
		IMG_Quit();
		SDL_Quit();
	}
	

  bool checkBattle(Player* controller, Map*& map, vector<Position>& battle){
		//compute which blocks to render:
    int radius = 1;
  	std::vector<Position> torender;
  	Position original; original.x = 0; original.y = 0;
  	torender.resize((2*radius+1)*(2*radius+1), original);
  	
  	int step_x = -1*(radius);
  	int step_y = -1*(radius);
  
  	for(int i=0; i < (2*radius+1); i++){
  		for(int j=0; j < (2*radius+1); j++){
  			Position pos; pos.x = step_x; pos.y = step_y;
  			torender[j+(2*radius+1)*i] = pos;
  			step_x++;
  		}
  		step_x = -1*radius;
  		step_y++;
  	}
  
  	step_x=0;
  	step_y=1;
    bool havetobattle = false;
   
     for(int i=0; i < torender.size(); i++){
  		Position resultpos;
  		resultpos.x = controller->pos.x+torender[i].x; 
  		resultpos.y = controller->pos.y+torender[i].y;
  		if(resultpos.x >= 0 && resultpos.y >= 0 && resultpos.x < map->width && resultpos.y < map->height){
  			if(map->GetNode(resultpos.y, resultpos.x)->currChar != NULL){
          battle.push_back(resultpos);
          havetobattle = true;
       }
  		}
  	}
   
     return havetobattle;
  }

  void HUD(string str_say, TTF_Font* gFont, int offset=0){
    LTexture text_place;
		//TTF_Font *gFont = TTF_OpenFont("OpenSans-Bold.ttf", 14);

	  if( gFont == NULL )
  	{
  		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
  	}
  	else
  	{
  		//Render text
  		SDL_Color textColor = { 0, 0, 0 };
  		if( !text_place.loadFromRenderedText( gRenderer, str_say, textColor, gFont ) )
  		{
  			printf( "Failed to render text texture!\n" );
  		}
  	}
   //draw rectangle:
   SDL_Rect bg; bg.x = 900; bg.y = 0+offset; bg.w = 150; bg.h = 48;
   SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF,0xFF);
   SDL_RenderFillRect(gRenderer, &bg);
    //place text over it:
    text_place.render(gRenderer, 910, 15+offset);
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
				//map_struct = new Map(0, 0, 2, "test_map.txt", gRenderer);

				//Event handler
				SDL_Event e;

				//The dot that will be moving around on the screen
				Dot dot(SCREEN_WIDTH, SCREEN_HEIGHT, "./assets/characters/cs317_enemy_1.png");
				if(!gDotTexture.loadFromFile(gRenderer, dot.controller->texturePath))
					exit(-1);

        //shieldTexture.loadFromFile(bRenderer, "./assets/items/shield.png");
        //swordTexture.loadFromFile(bRenderer, "./assets/items/sword.png");
        //work on making them buttons

				GameState* game = new GameState("items.txt", "enemies.txt", gRenderer);
				game->isPlayOver = false;
				TTF_Font* gFont = TTF_OpenFont("OpenSans-Bold.ttf", 14);
        vector<Position> battle;
				map_struct = new Map(0,0,2,"test_map.txt", gRenderer, game->get_items(), game->get_enemies());

				//While application is running
				while( game->playing )
				{
					//Handle events on queue
					if(game->isPlayOver){
						// do combat stuff here:
						game->playing = game->fightEnemies(dot.controller, battle, map_struct);
						if(battle.size() == 0)
							game->isPlayOver = false;
					}
					else{
						while( SDL_PollEvent( &e ) != 0 )
						{
							//User requests quit
							if( e.type == SDL_QUIT )
							{
								game->playing = false;
							}

							//Handle input for the dot
							dot.handleEvent( e );
						}

						//Move the dot
						dot.move(map_struct);
						game->isPlayOver = checkBattle(dot.controller, map_struct, battle);
					}

					//Clear screen
					SDL_RenderClear( gRenderer );
          //SDL_RenderClear(bRenderer);

					map_struct->Redraw(dot.controller->pos.x, dot.controller->pos.y, dot.controller->radius);

					//Render objects
					dot.render(gDotTexture, gRenderer);
		      //button render statement here

					HUD("health: " + to_string(dot.controller->health), gFont);
					HUD("score: " + to_string(game->score), gFont, 30);
					//Update screen
					SDL_RenderPresent( gRenderer );
				  //SDL_RenderPresent(bRenderer);
        }
			delete game;
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
