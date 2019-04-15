#pragma once
#include <vector>
#include <stdio.h>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "game.h"
#include "ltexture.h"

using namespace std;

class Node{
	public:
		Node();
		Node(int);
		int terrain;
};

class Map{
	public:
		Map(int,int,SDL_Renderer*);
		Map(string,SDL_Renderer*);
		void ClearMap();
		void LoadMap(int,int);
		Node* GetNode(int,int);
		void Redraw(int, int);
			
	private:
		void loadtextures(); 
		SDL_Renderer* render;
		int width;
		int height;
		int BOX_HEIGHT;
		int BOX_WIDTH;

		vector< vector<Node*> > node_map;
		map<int,string> terrain_key;
		vector<LTexture*> textures;
};
