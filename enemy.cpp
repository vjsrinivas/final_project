#include <cstdio>
#include <string>
//#include "player.h"
#include "enemy.h"

void Enemy::printPos(){
	
		printf("Enemy is at: [x=%i, y=%i]\n",pos.x, pos.y);

}

Enemy::Enemy(){
	texturePath="./assets/characters/cs317_enemy_2.png";

}

Enemy::Enemy(std::string path){
	texturePath=path;

}

//void Enemy::attack(){

//}

void loadEnemyFile(std::string filename, std::vector<Enemy*>& enemy){
	ifstream file(filename.c_str());
	
	if(file.is_open()){
		int numofenemies;
		std::string enemyname;
		
		file >> numofenemies;
		
		for(int i=0; i < numofenemies; i++){
			Enemy* new_enemy = new Enemy();
			file >> new_enemy->name;
			file >> new_enemy->texturePath;
		}
	}
	else{
		printf("Error in opening enemy file!\n");
	}
}
