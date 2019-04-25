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
		int movesLeft;
		std::string texturePath;

		void addItem(Item*);
		int radius = 1;
		//vector<Item*> getItems();

	private:
		std::vector<Item*> items;
};

// Function reads a file and adds to vector of items for retrieval later
void loadItemFile(SDL_Renderer*, std::string filename, std::vector<Item*>& items);

void executeItem(Item* item, Player*& controller);

// Functions for item catergories:
void LightPotion(Player*& controller);

