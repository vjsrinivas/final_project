#include <iostream>
#include <string>

using namespace std;

class Monster{
	Public:
	Monster();
	~Monster();

	Private:
//	string name;
	int health;
	int damage;
	int speed;
	int position;	
	void attack();
}

