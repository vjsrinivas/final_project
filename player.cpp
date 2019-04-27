/* Final Project - Space Cowboys
 * Created by: Vijay Rajagopal, Josh Spangler, John Pi
 * File purpose: player.cpp is the implementation of 
 * prototypes of functions found in player.h
 */

#include "player.h"

// Item constructor makes sure that item textures are loaded in before anything else
Item::Item(SDL_Renderer* gRenderer, std::string path){
	if(!texture->loadFromFile(gRenderer, path))
		printf("Error loading texture!\n");
}

// Debug function to figure out where the player is
void Player::printPos(){
	printf("Player is at: [x=%i, y=%i]\n",pos.x, pos.y);
}

// Player constructor that assigns default texture
Player::Player(){
	texturePath = "./assets/characters/cs317_enemy_1.png";
}

// Optional constructor that allows you to change main char's texture
Player::Player(std::string path){
	texturePath = path;
}

// Helper function to add item to player's inventory
void Player::addItem(Item* currItem){
	items.push_back(currItem);
}

// Helper function that returns the 
std::vector<Item*> Player::getItems(){
	return items;
}

// Implementation from header file - reads item file, creates new item objects, and puts them in given vector
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

			// file >> holder is used to get rid of the descriptors in the txt file
			// (ex): dmg: 30 (file >> holder) gets rid of dmg from the stream
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

// Enemy constructor to default to a certain texture
Enemy::Enemy(){
	texturePath="./assets/characters/cs317_enemy_2.png";

}

// Enemy constructor that allows you to assign a specific texture path for Enemy objects
Enemy::Enemy(std::string path){
	texturePath=path;

}

// Construct that copies details from another Enemy object (used during enemy creation)
Enemy::Enemy(Enemy* newspawn){
	name = newspawn->name;
	texturePath = newspawn->texturePath;
	texture = newspawn->texture;
	health = newspawn->health;
	maxdmg = newspawn->maxdmg;
}

// Similar function to loadItemsFile but for enemies (will contain a certain amount of enemy types to later be called)
void loadEnemyFile(std::string filename, std::vector<Enemy*>& enemy){
	std::ifstream file(filename.c_str());

	if(file.is_open()){
		int numofenemies;
		std::string holder;

		file >> numofenemies;

		for(int i=0; i < numofenemies; i++){
			Enemy* new_enemy = new Enemy();
			file >> new_enemy->name;
			file >> new_enemy->texturePath;
			if(file >> holder)
				printf("looking for %s...\n", holder.c_str());
			file >> new_enemy->health;
			if(file >> holder)
				printf("looking for %s...\n", holder.c_str());
			file >> new_enemy->maxdmg;
			if(file >> holder)
				printf("looking for %s...\n", holder.c_str());
			file >> new_enemy->maxdef;
			enemy.push_back(new_enemy);
		}
	}
	else{
		printf("Error in opening enemy file!\n");
	}
}

void executeItem(Item* item, Player*& controller){
	std::string type = item->type;

	if(type == "weapon"){
		// Do nothing? maybe add inventory functionality
	}
	else if(type == "other"){
		// Execute function immediately
		if(item->func == "LightPotion"){
			LightPotion(controller);
		}
		else if(item->func == "HealthPotion"){
			HealthPotion(controller);
		}
	}
	else if(type=="shield"){
		printf("Picked up shield\n");
	}
	else{
		printf("error! item type not right!\n");
	}
}

// Light potion increases the viewability of a player
void LightPotion(Player*& controller){
	controller->radius += 1;
}

// Health potion increases health (if already at 100, it gives you extra 20 instead of 30)
void HealthPotion(Player*& controller){
	if(controller->health <= 80)
		controller->health += 30;
	else if(controller->health > 80)
		controller->health += 20;
}


