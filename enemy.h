#include <cstdio>
#include <string>
#include "ltexture.h"
//#include "player.h"

	
class Enemy{
	public:
		Enemy();
		Enemy(std::string path);
		void printPos();
		Position pos;
		int health=10;

//		void dead();
//		void spawn();
	private:
//		void attack();
}

void loadEnemyFile(std::string, std::vector<Enemy*>&);
