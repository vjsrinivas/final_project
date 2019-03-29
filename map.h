#include <vector>
#include <stdio.h>
#include <map>

using namespace std;

class Node{
	public:
		int terrain;
};

class Map{
	public:
		Map();
		Map(FILE*);
		Node* get(int item);
		void clear();
		map<int,int> terrain_key;

	private:
		int width;
		int height;
		vector<Node*> node_map;
};
