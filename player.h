#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

struct Item{
	std::string itemName;
	std::string texturePath;
	int damage = 0;
	int defense = 0;
	std::string func = "";
	std::string type = "";
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

		void addItem(std::string, int, int);
		Item getItem(std::string name);
	private:
		std::vector<Item> items;
};

// Function reads a file and adds to vector of items for retrieval later
void loadItemFile(std::string filename, std::vector<Item*>& items);
