#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include "ltexture.h"

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

struct Position{
	int x = 0;
	int y = 0;
};

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

void loadEnemyFile(std::string, std::vector<Enemy*>&);


// Function reads a file and adds to vector of items for retrieval later
void loadItemFile(SDL_Renderer*, std::string filename, std::vector<Item*>& items);

void executeItem(Item* item, Player*& controller);

// Functions for item catergories:
void LightPotion(Player*& controller);
void HealthPotion(Player*& controller);
