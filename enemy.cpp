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


