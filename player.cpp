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

void Enemy::printPos(){
		//printf("Enemy is at: [x=%i, y=%i]\n",pos.x, pos.y);
}

Enemy::Enemy(){
	texturePath="./assets/characters/cs317_enemy_2.png";

}

Enemy::Enemy(std::string path){
	texturePath=path;

}

Enemy::Enemy(Enemy* newspawn){
	printf("copying... %s", newspawn->name.c_str());
	name = newspawn->name;
	texturePath = newspawn->texturePath;
	texture = newspawn->texture;
	health = newspawn->health;
	maxdmg = newspawn->maxdmg;
}

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
		//do nothing? maybe add 
	}
	else if(type == "other"){
		//execute function immediately
		if(item->func == "LightPotion"){
			LightPotion(controller);
		}
		else if(item->func == "HealthPotion"){
			HealthPotion(controller);
		}
	}
	else{
		printf("error! item type not right!\n");
	}
}

void LightPotion(Player*& controller){
	controller->radius += 1;
}

void HealthPotion(Player*& controller){
	if(controller->health <= 80)
		controller->health += 20;
	else if(controller->health > 80 && controller->health <= 100)
		controller->health = 100;
}


