/* Final Project - Space Cowboys
 * Created by: Vijay Rajagopal, Josh Spangler, John Pi
 * File purpose: player.h is the header file that declares
 * the protoypes for classes, functions, etc.
 */

#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include "ltexture.h"

// This struct is the basis for all item objects in the game:
struct Item{
	Item(SDL_Renderer*, std::string);
	~Item();

	std::string itemName;
	std::string texturePath;
	int damage = 0;
	int defense = 0;
	std::string func = "";
	std::string type = "";
	LTexture* texture = new LTexture();
};

// Simple struct that contains x,y coordinates
struct Position{
	int x = 0;
	int y = 0;
};

// Player is only used for the main character (player)
class Player{
	public:
		Player();
		Player(std::string path);

		int health = 100;
		void printPos();
		Position pos;
		std::string texturePath;
		void addItem(Item*);
		int radius = 1;
		std::vector<Item*> getItems();
		Item* currWeap = NULL;
		Item* currShield = NULL;

	private:
		std::vector<Item*> items;
};

// Enemy class is only used for enemies
class Enemy{
	public:
		Enemy();
		Enemy(Enemy*);
		Enemy(std::string path);
		void printPos();
		Position pos;
		int health = 10;
		std::string name;
		std::string texturePath;
		LTexture* texture = new LTexture();
		int maxdmg = 0;
		int maxdef = 0;
	private:
		std::vector<Item*> items;
};

// Function reads a file and adds new Enemy objects to a given vector
void loadEnemyFile(std::string, std::vector<Enemy*>&);


// Function reads a file and adds to vector of items for retrieval later
void loadItemFile(SDL_Renderer*, std::string filename, std::vector<Item*>& items);

// Function goes through item's type and executes an action
void executeItem(Item* item, Player*& controller);

// Functions for item catergories:
void LightPotion(Player*& controller);
void HealthPotion(Player*& controller);
