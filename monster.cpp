#include "monster.h"

using namespace std;

class Skeleton : public Monster{
	public:
		Skeleton(){
//			this->name="Skeleton";
			this->health=1;
			this->damage=1;
			this->speed=1;
//			this->position= ; 
		}
		void attack(){
			if(){//if player character is 1 block away
				//player health - this->monster_damage 	
			}
		}
}

class Zombie : public Monster{
	public:
		Zombie(){
//			this->name="Zombie"
			this->health=2;
			this->damage=2;
			this->speed=1;
//			this->position= ; 
		}
		void attack(){
			if(){
			
			}
		}
}

class Boss : public Monster{
	public:
		Boss(){
			this->health=4;
			this->damage=4;
			this->speed=1;
		}
		void attack(){
			if(){

			}
		}
}
