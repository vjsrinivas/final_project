#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Item{
	Public:
	Item();
	~Item();


	Private:
	string Name;
	int damage;
	int health;
//	int location;
	void pickup();
}
