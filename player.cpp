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

void loadItemFile(std::string filename, std::vector<Item*>& items){
	std::ifstream file(filename.c_str());

	if(file.is_open()){
		int numofitems = 0;
		file >> numofitems;
		std::string holder;
		for(int i=0; i < numofitems; i++){
			Item* new_item = new Item();
			file >> new_item->itemName;
			file >> new_item->texturePath;
			if(file >> holder)
				printf("Entering %s of %s\n", holder.c_str(), new_item->itemName.c_str());
			file >> new_item->damage;
			if(file>> holder)
				printf("Entering %s of %s\n", holder.c_str(), new_item->itemName.c_str());
			file >> new_item->defense;
			if(file >> holder)
				printf("Entering %s of %s\n", holder.c_str(), new_item->itemName.c_str());
			file >> new_item->func;
			if(file >> holder)
				printf("Entering %s of %s\n", holder.c_str(), new_item->itemName.c_str());
			file >> new_item->type;
		}
	}
	else{
		printf("Item file did not open\n");
	}
}
