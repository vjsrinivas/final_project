#include <cstdio>
#include <string>
#include <vector>

struct Item{
	std::string itemName;
	int damage = 0;
	int defense = 0;
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
