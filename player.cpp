#include "player.h"

void Player::printPos(){
	printf("Player is at: [x=%i, y=%i]\n",pos.x, pos.y); 
}

Player::Player(){
	texturePath = "./assets/characters/cs317_enemy_1.png";
}

Player::Player(std::string path){
	texturePath = path;
}

void Player::addItem(std::string name, int damage, int defense){
	Item newItem;
	newItem.itemName = name;
	newItem.damage = damage;
	newItem.defense = defense;
	items.push_back(newItem);
}

Item Player::getItem(std::string name){
	//search or whatever;
	//
	Item newItem;
	return newItem;
}
