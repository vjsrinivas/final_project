#include <cstdio>
#include <string>
#include <vector>

struct Item{
	std::string itemName;
	int damage;
	int defense;
};

struct Position{
	int x;
	int y;
};

class Player{
	public:
		Player();
		Player(std::string path);
		
		int health;
		void printPos();
		Position pos;
		int movesLeft;
		std::string texturePath;

		void addItem(std::string, int, int);
		Item getItem(std::string name);
	private:
		std::vector<Item> items;
};
