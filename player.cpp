#include "player.h"

Item::Item(SDL_Renderer* gRenderer, std::string path){
	if(!texture->loadFromFile(gRenderer, path))
		printf("Error loading texture!\n");
	//if(texture == NULL) { printf("Error loading texture!\n");
}

void Player::printPos(){
	printf("Player is at: [x=%i, y=%i]\n",pos.x, pos.y);
}

Player::Player(){
	texturePath = "./assets/characters/cs317_enemy_1.png";
}

Player::Player(std::string path){
	texturePath = path;
}

void Player::addItem(Item* currItem){
	items.push_back(currItem);
}

void loadItemFile(SDL_Renderer* render, std::string filename, std::vector<Item*>& items){
	std::ifstream file(filename.c_str());

	if(file.is_open()){
		int numofitems = 0;
		file >> numofitems;

		std::string holder;
		std::string name;

		for(int i=0; i < numofitems; i++){
			file >> name >> holder;
			Item* new_item = new Item(render, holder);
			new_item->itemName = name;
			new_item->texturePath = holder;

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
			items.push_back(new_item);
		}
	}
	else{
		printf("Item file did not open\n");
	}
}
