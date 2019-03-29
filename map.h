#include <vector>
#include <stdio.h>
#include <map>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Node{
	public:
		int terrain;
};

class Map{
	public:
		Map();
		Map(ifstream& FILE);
		Node* get(int item);
		void clear();
		map<int,int> terrain_key;

	private:
		int width;
		int height;
		vector<Node*> node_map;
};
