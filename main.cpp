		/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
		and may not be redistributed without written permission.*/

		//Using SDL, SDL_image, standard IO, and strings
#include <stdio.h>
#include <string>
#include <vector>
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
							int damageLost = 0; //shield
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

    const int BUTTON_WIDTH = 128;
    const int BUTTON_HEIGHT = 128;
    const int TOTAL_BUTTONS = 10;

    enum LButtonSprite{
      BUTTON_SPRITE_MOUSE_DOWN = 0,
      BUTTON_SPRITE_MOUSE_UP = 1,
      BUTTON_SPRITE_TOTAL = 2
    };

		//Starts up SDL and creates window
		bool init();

		//Loads media
		bool loadMedia();

		//Frees media and shuts down SDL
		void close();

		//The window we'll be rendering to
		SDL_Window* gWindow = NULL;
    SDL_Window* bWindow = NULL;

		//The window renderer
		SDL_Renderer* gRenderer = NULL;
    SDL_Renderer* bRenderer = NULL;

    //Scene textures
		LTexture gDotTexture;
    LTexture shieldTexture;
    LTexture swordTexture;

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
				bWindow = SDL_CreateWindow( "Inventory", 0, 0, SCREEN_WIDTH-440, SCREEN_HEIGHT-600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if( gWindow == NULL || bWindow == NULL)
				{
					printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
					success = false;
				}
				else
				{
					//Create vsynced renderer for window
					gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
					bRenderer = SDL_CreateRenderer(bWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
					//gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED);

          if( gRenderer == NULL || bRenderer == NULL )
					{
						printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
						success = false;
					}

					else
					{
						//Initialize renderer color
						SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_SetRenderDrawColor(bRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

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
    shieldTexture.free();
    swordTexture.free();

		//Destroy window
		SDL_DestroyRenderer( gRenderer );
		SDL_DestroyWindow( gWindow );
		gWindow = NULL;
		gRenderer = NULL;

    SDL_DestroyRenderer(bRenderer);
    SDL_DestroyWindow(bWindow);
    bWindow = NULL;
    bRenderer = NULL;

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

  SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];

  //The mouse button
  class LButton
  {
  public:
	  //Initializes internal variables
	  LButton();

	  //Sets top left position
	  void setPosition(int x, int y);

	  //Handles mouse event
	  void handleEvent(SDL_Event* e, Item* item, Dot &dot);

	  //Shows button sprite
	  void swordRender();

    void shieldRender();

  private:
	  //Top left position
	  SDL_Point mPosition;

	  //Currently used global sprite
	  LButtonSprite mCurrentSprite;
  };

  LButton::LButton()
  {
	  mPosition.x = 0;
	  mPosition.y = 0;

	  mCurrentSprite = BUTTON_SPRITE_MOUSE_UP; //was out
  }

  void LButton::setPosition(int x, int y)
  {
	  mPosition.x = x;
	  mPosition.y = y;
  }

  void LButton::handleEvent(SDL_Event* e, Item* item, Dot &dot)
  {
	  //If mouse event happened
	  if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	  {
		  //Get mouse position
		  int x, y;
		  SDL_GetMouseState(&x, &y);

		  //Check if mouse is in button
		  bool inside = true;

		  //Mouse is left of the button
		  if (x < mPosition.x)
		  {
			  inside = false;
		  }
		//Mouse is right of the button
		  else if (x > mPosition.x + BUTTON_WIDTH)
		  {
			  inside = false;
		  }
		  //Mouse above the button
		  else if (y < mPosition.y)
		  {
			  inside = false;
		  }
		//Mouse below the button
		  else if (y > mPosition.y + BUTTON_HEIGHT)
		  {
			  inside = false;
		  }

		  //Mouse is outside button
		  if (!inside)
		  {
			  mCurrentSprite = BUTTON_SPRITE_MOUSE_UP; //was out
		  }
		  //Mouse is inside button
		  else
		  {

			//Set mouse over sprite
			  switch (e->type)
			  {
			//case SDL_MOUSEMOTION:
				//mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				//break;

			  case SDL_MOUSEBUTTONDOWN:
				  mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				  break;

			  case SDL_MOUSEBUTTONUP:
          //call equip function here????
				  mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
          if(item->type == "weapon"){                 
            dot.controller->currWeap = item;
          }
          if(item->type == "shield"){
            dot.controller->currShield = item;
          }
          printf("item was equipped\n");
				  break;
			  }
		  }
	  }
  }

  void LButton::swordRender()
  {
	  //Show current button sprite
	  swordTexture.render(bRenderer, mPosition.x, mPosition.y);//was gSpriteClips[mCurrentSprite]
  }

  void LButton::shieldRender(){
    shieldTexture.render(bRenderer, mPosition.x, mPosition.y);
  }

  LButton gButtons[TOTAL_BUTTONS];

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

        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = BUTTON_WIDTH;
        gSpriteClips[0].h = BUTTON_HEIGHT;
        gSpriteClips[1].x = 0;
        gSpriteClips[1].y = 0;
        gSpriteClips[1].w = BUTTON_WIDTH;
        gSpriteClips[1].h = BUTTON_HEIGHT;

        for(int i = 0; i < TOTAL_BUTTONS; i++){
          if(i < 5){
            gButtons[i].setPosition(BUTTON_WIDTH * i, 0);
          }
          else{
            gButtons[i].setPosition(BUTTON_WIDTH * (i-5), BUTTON_HEIGHT * 2);
          }
        }

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

              vector<Item*> playerstuff = dot.controller->getItems();
              
              if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
                for(int i = 0; i < playerstuff.size(); i++){
                  //if(playerstuff[i] != NULL){
                    gButtons[i].handleEvent(&e, playerstuff[i], dot );
                  //}
                }
              }
              else{
							//Handle input for the dot
							  dot.handleEvent( e );
						  }
            }

						//Move the dot
						dot.move(map_struct);
						game->isPlayOver = checkBattle(dot.controller, map_struct, battle);
					}

					//Clear screen
					SDL_RenderClear( gRenderer );
          SDL_RenderClear(bRenderer);

					map_struct->Redraw(dot.controller->pos.x, dot.controller->pos.y, dot.controller->radius);

					//Render objects
					dot.render(gDotTexture, gRenderer);
		      //button render statement here
          vector<Item*> stuff = dot.controller->getItems();

          for(int i = 0; i < stuff.size(); i++){
            if(stuff[i]->type == "weapon"){
              swordTexture.loadFromFile(bRenderer, stuff[i]->texturePath);
              gButtons[i].swordRender();
            }
            else if(stuff[i]->type == "shield"){
              shieldTexture.loadFromFile(bRenderer, stuff[i]->texturePath);
              gButtons[i].shieldRender();
            }
          }

					HUD("health: " + to_string(dot.controller->health), gFont);
					HUD("score: " + to_string(game->score), gFont, 30);
					//Update screen
					SDL_RenderPresent( gRenderer );
				  SDL_RenderPresent(bRenderer);
        }
			delete game;
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
