/* Final Project - Space Cowboys
 * Created by: Vijay Rajagopal, Josh Spangler, John Pi
 * This is the main file that launches the game
 */

#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include "ltimer.h"
#include "ltexture.h"
#include "map.h"

using namespace std;

class GameState
{
public:
    GameState();
    GameState(string filename, string enemyFile, SDL_Renderer*);
    ~GameState();
    bool playing = 1;
    bool fightEnemies(Player*& controller, vector<Position>& pos, Map*& map);
    bool isPlayOver;
    void addEnemy(string texturePath);
    void removeEnemy(int position);
    void placeItem(int item_pos, int x, int y);
    vector<Item*> get_items();
    vector<Enemy*> get_enemies();

private:
    LTexture dmgPopup;
    TTF_Font* dmgFont;
    void damageIndicator(std::string dmg, int, int);
    void loadenemytextures();
    vector<Item*> items;
    SDL_Renderer* render;
    vector<Enemy*> enemies;
};
// gamestate class holds most of the functions needed while the game is actually running

void GameState::damageIndicator(std::string dmg, int pos_x, int pos_y)
{
    if (dmgFont == NULL)
        printf("Error! could not read dmgFont\n");
    else
    {
        SDL_Color textColor = { 100, 0, 0 };

        if (!dmgPopup.loadFromRenderedText(render, dmg, textColor, dmgFont))
        {
            printf("Failed to render text texture!\n");
        }

        dmgPopup.render(render, pos_y, pos_x); 
    }
} // renders text to indicate when the player has taken damage

void GameState::loadenemytextures()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->texture->loadFromFile(render, enemies[i]->texturePath);
    }
} // calls render function for each enemy in the game

bool GameState::fightEnemies(Player*& controller, vector<Position>& pos, Map*& map)
{
    // fight one and then the other:
    srand(time(NULL));
    while (pos.size() != 0)
    {
        for (int i = 0; i < pos.size(); i++)
        {
            // Logic of enemy when they attack the player:
            Node* enemy_node = map->GetNode(pos[i].y, pos[i].x);
            int damageTaken = 0;
            int damageBlocked = 0;
            // Determine damage against player based on the maxdmg of enemy
            if (enemy_node->currChar->maxdmg != 0)
                damageTaken = rand() % enemy_node->currChar->maxdmg + 1;

            // Player's shield taking some damage off:
            if(controller->currShield != NULL){
              damageBlocked = rand() % controller->currShield->defense;
            }

            damageTaken -= damageBlocked;
			if(damageTaken >= 0)
				controller->health -= damageTaken;
            damageIndicator("-" + std::to_string(damageTaken), controller->pos.x, controller->pos.y + 10);

            // attack enemy:
            if (controller->currWeap != NULL)
            {
                int damageGiven = controller->currWeap->damage;
                if (enemy_node->currChar->maxdef != 0)
                {
                    int damageLost = rand() % enemy_node->currChar->maxdef + 1; // shield
                    damageGiven -= damageLost;
                }
                if (damageGiven != 0)
                {
                    int original_health = enemy_node->currChar->health;
                    enemy_node->currChar->health -= rand() % damageGiven + 1;
                    damageIndicator(std::to_string(enemy_node->currChar->health) + "/"
                            + std::to_string(original_health),
                        pos[i].x, pos[i].y + 10);
                }
            } // fighting is automated and based off a random value obtained from enemies max attack
              // and defense

            if (enemy_node->currChar->health <= 0)
            {
				controller->score += 10;
				if (enemy_node->currChar->name == "Key_Boy")
                {
                    printf("You won :-)\n");
                    exit(-1);
                }
                delete enemy_node->currChar;
                enemy_node->currChar = NULL;
                pos.erase(pos.begin() + i);
            }
        }

        if (controller->health <= 0)
        {
            printf("\n\nYou lost the game :(\n\n");
            return false;
        }
    }
    return true;
}

vector<Item*> GameState::get_items()
{
    return items;
}

vector<Enemy*> GameState::get_enemies()
{
    return enemies;
}

void GameState::placeItem(int item_pos, int x, int y)
{
    LTexture item_icon;
    if (item_icon.loadFromFile(render, items[item_pos]->texturePath))
    {
        item_icon.render(render, x * 30, y * 30);
    }
    else
    {
        printf("Error! failed to load texture for: %s\n", items[item_pos]->itemName.c_str());
    }

} // renders items at each location on the map

GameState::GameState()
{
}

GameState::GameState(string filename, string enemyFile, SDL_Renderer* gRenderer)
{
    render = gRenderer;
    loadItemFile(render, filename, items);
    loadEnemyFile("enemy.txt", enemies);
    loadenemytextures();
    dmgFont = TTF_OpenFont("OpenSans-Bold.ttf", 10);
    for (int i = 0; i < items.size(); i++)
    {
        cout << items[i]->itemName << endl;
    }
} // sets up renderer, enemies, and items from text files. Also sets the font from a ttf file

GameState::~GameState()
{
}

void GameState::addEnemy(string texturePath)
{
    Enemy* newEnemy = new Enemy(texturePath);
    enemies.push_back(newEnemy);
}

struct KillLog
{
    string enemyName;
    int enemeyID;
};


// Screen dimension constants
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 1080;

const int BUTTON_WIDTH = 128;
const int BUTTON_HEIGHT = 128;
const int TOTAL_BUTTONS = 10;

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_DOWN = 0,
    BUTTON_SPRITE_MOUSE_UP = 1,
    BUTTON_SPRITE_TOTAL = 2
}; // setting size of buttons and the inputs they'll read

// Starts up SDL and creates window
bool init();

// Frees media and shuts down SDL
void close();

// The windows we'll be rendering to
SDL_Window* gWindow = NULL;
SDL_Window* bWindow = NULL;

// The window renderers
SDL_Renderer* gRenderer = NULL;
SDL_Renderer* bRenderer = NULL;

// Scene textures
LTexture gDotTexture;
LTexture shieldTexture;
LTexture swordTexture;

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        // Create windows
        gWindow = SDL_CreateWindow("SDL Tutorial", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
        bWindow = SDL_CreateWindow("Inventory", 0, 0, SCREEN_WIDTH-440, SCREEN_HEIGHT-600,
            SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);

        if (gWindow == NULL || bWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create vsynced renderers for windows
            gRenderer = SDL_CreateRenderer(
                gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            bRenderer = SDL_CreateRenderer(
                bWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (gRenderer == NULL || bRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }

            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_SetRenderDrawColor(bRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }

                // Initialize SDL_ttf
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

void close()
{
    // Free loaded images
    gDotTexture.free();
    shieldTexture.free();
    swordTexture.free();

    // Destroy windows
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    SDL_DestroyRenderer(bRenderer);
    SDL_DestroyWindow(bWindow);
    bWindow = NULL;
    bRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


bool checkBattle(Player* controller, Map*& map, vector<Position>& battle)
{
    // compute whether or not there is somebody to fight:
    int radius = 1;
    std::vector<Position> torender;
    Position original;
    original.x = 0;
    original.y = 0;
    torender.resize((2 * radius + 1) * (2 * radius + 1), original);

    int step_x = -1 * (radius);
    int step_y = -1 * (radius);

    //Generate a block of coordinates with a radius of 1 from the center to check against:
    for (int i = 0; i < (2 * radius + 1); i++)
    {
        for (int j = 0; j < (2 * radius + 1); j++)
        {
            Position pos;
            pos.x = step_x;
            pos.y = step_y;
            torender[j + (2 * radius + 1) * i] = pos;
            step_x++;
        }
        step_x = -1 * radius;
        step_y++;
    }

    step_x = 0;
    step_y = 1;

    bool havetobattle = false;

    // This is the main code snippet that checks whether there's an enemy within that block
    for (int i = 0; i < torender.size(); i++)
    {
        Position resultpos;
        resultpos.x = controller->pos.x + torender[i].x;
        resultpos.y = controller->pos.y + torender[i].y;
        if (resultpos.x >= 0 && resultpos.y >= 0 && resultpos.x < map->width
            && resultpos.y < map->height)
        {
            if (map->GetNode(resultpos.y, resultpos.x)->currChar != NULL)
            {
                battle.push_back(resultpos);
                havetobattle = true;
            }
        }
    }

    return havetobattle;
} // function decides if the player is close enough to an enemy to initiate combat

void HUD(string str_say, TTF_Font* gFont, int offset = 0)
{
    LTexture text_place;

    if (gFont == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        // Render text
        SDL_Color textColor = { 0, 0, 0 };
        if (!text_place.loadFromRenderedText(gRenderer, str_say, textColor, gFont))
        {
            printf("Failed to render text texture!\n");
        }
    }
    // draw rectangle:
    SDL_Rect bg;
    bg.x = 900;
    bg.y = 0 + offset;
    bg.w = 150;
    bg.h = 48;
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(gRenderer, &bg);
    // place text over it:
    text_place.render(gRenderer, 910, 15 + offset);
}

SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];

// The mouse button
class LButton
{
public:
    // Initializes internal variables
    LButton();

    // Sets top left position
    void setPosition(int x, int y);

    // Handles mouse event
    void handleEvent(SDL_Event* e, Item* item, Dot dot);

    // Shows button sprite
    void swordRender();

    void shieldRender();

private:
    // Top left position
    SDL_Point mPosition;

    // Currently used global sprite
    LButtonSprite mCurrentSprite;
};

LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
}

void LButton::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
} // places button at specified location

void LButton::handleEvent(SDL_Event* e, Item* item, Dot dot)
{
    // If mouse event happened
    if (e->type == SDL_MOUSEBUTTONDOWN
        || e->type == SDL_MOUSEBUTTONUP)
    {
        // Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Check if mouse is in button
        bool inside = true;

        // Mouse is left of the button
        if (x < mPosition.x)
        {
            inside = false;
        }
        // Mouse is right of the button
        else if (x > mPosition.x + BUTTON_WIDTH)
        {
            inside = false;
        }
        // Mouse above the button
        else if (y < mPosition.y)
        {
            inside = false;
        }
        // Mouse below the button
        else if (y > mPosition.y + BUTTON_HEIGHT)
        {
            inside = false;
        }

        // Mouse is outside button
        if (!inside)
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_UP; // was out
        }
        // Mouse is inside button
        else
        {

            // Set mouse over sprite
            switch (e->type)
            {

                case SDL_MOUSEBUTTONDOWN:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;

                case SDL_MOUSEBUTTONUP:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                    if (item->type == "weapon")
                    {
                        dot.controller->currWeap = item;
                    }
                    else if (item->type == "shield")
                    {
                        dot.controller->currShield = item;
                    }
                    printf("item was equipped\n");
                    break;
            } // equips weapon/shield if mouse goes back up over a button
        }
    }
}

void LButton::swordRender()
{
    swordTexture.render(bRenderer, mPosition.x, mPosition.y);
}

void LButton::shieldRender()
{
    shieldTexture.render(bRenderer, mPosition.x, mPosition.y);
} // renders both item textures in player's inventory

LButton gButtons[TOTAL_BUTTONS]; // creates the button array

int main(int argc, char* args[])
{
    // Create map system:
    Map* map_struct;

    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Event handler
        SDL_Event e;

        // The dot that will be moving around on the screen
        Dot dot(SCREEN_WIDTH, SCREEN_HEIGHT, "./assets/characters/cs317_enemy_1.png");
        if (!gDotTexture.loadFromFile(gRenderer, dot.controller->texturePath))
            exit(-1);

        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = BUTTON_WIDTH;
        gSpriteClips[0].h = BUTTON_HEIGHT;
        gSpriteClips[1].x = 0;
        gSpriteClips[1].y = 0;
        gSpriteClips[1].w = BUTTON_WIDTH;
        gSpriteClips[1].h = BUTTON_HEIGHT;

        for (int i = 0; i < TOTAL_BUTTONS; i++)
        {
            if (i < 5)
            {
                gButtons[i].setPosition(BUTTON_WIDTH * i, 0);
            }
            else
            {
                gButtons[i].setPosition(BUTTON_WIDTH * (i - 5), BUTTON_HEIGHT * 2);
            }
        } // sets ten buttons in two rows of five in inventory window

        GameState* game = new GameState("items.txt", "enemies.txt", gRenderer);
        game->isPlayOver = false;
        TTF_Font* gFont = TTF_OpenFont("OpenSans-Bold.ttf", 14);
        vector<Position> battle;
        map_struct
            = new Map(0, 0, 2, "test_map.txt", gRenderer, game->get_items(), game->get_enemies());
	SDL_ShowWindow(bWindow);

	// While application is running
        while (game->playing)
        {
            // Handle events on queue
            if (game->isPlayOver)
            {
                // do combat stuff here:
                game->playing = game->fightEnemies(dot.controller, battle, map_struct);
                if (battle.size() == 0)
                    game->isPlayOver = false;
            }
            else
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    // User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        game->playing = false;
                    }

                    vector<Item*> playerstuff = dot.controller->getItems();

                    if (bRenderer != NULL && (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP))
                    {
                        for (int i = 0; i < playerstuff.size(); i++)
                        {
                            gButtons[i].handleEvent(&e, playerstuff[i], dot);
                        }
                    } // if the event is a mouse movement passes to button function for inventory
                    else
                    {
                        // Handles input for movement
                        dot.handleEvent(e);
                    }
                }

                // Move the player
                dot.move(map_struct);
                game->isPlayOver = checkBattle(dot.controller, map_struct, battle);

                // Clear screens
                SDL_RenderClear(gRenderer);
                SDL_RenderClear(bRenderer);

                map_struct->Redraw(
                    dot.controller->pos.x, dot.controller->pos.y, dot.controller->radius);

                // Render objects
                dot.render(gDotTexture, gRenderer);
                // button render statement here
            }
            vector<Item*> stuff = dot.controller->getItems();

            for (int i = 0; i < stuff.size(); i++)
            {
                if (stuff[i]->type == "weapon")
                {
                    swordTexture.loadFromFile(bRenderer, stuff[i]->texturePath);
                    gButtons[i].swordRender();
                }
                else if (stuff[i]->type == "shield")
                {
                    shieldTexture.loadFromFile(bRenderer, stuff[i]->texturePath);
                    gButtons[i].shieldRender();
                }
            } // runs through player items vector and renders the relevant one to the inventory screen

            // Updates the HUD of the game:
            HUD("health: " + to_string(dot.controller->health), gFont);
            HUD("score: " + to_string(dot.controller->score), gFont, 30);

            // Update screen
            SDL_RenderPresent(gRenderer);
            SDL_RenderPresent(bRenderer);
        }
        delete game;
    }

    // Free resources and close SDL
    close();

    return 0;
}
