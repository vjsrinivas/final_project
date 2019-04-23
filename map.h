#pragma once
#include <vector>
#include <stdio.h>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "game.h"
#include "ltexture.h"
#include "dot.h"

using namespace std;

class Node{
	public:
		Node();
		Node(int);
		int terrain;
		Player* currChar = NULL;
};

class Map{
	public:
		Map(int,int,SDL_Renderer*);
		Map(int,int,int,string,SDL_Renderer*);
		void ClearMap();
		void LoadMap(int,int);
		Node* GetNode(int,int);
		void Redraw(int, int, int);
		int width;
		int height;

	private:
		void loadtextures();
		void loadtextures(int,int,int);
		SDL_Renderer* render;
		
		int min_render_x = 0;
		int min_render_y = 0;
		int max_render_x = 0;
		int max_render_y = 0;

		int WIN_HEIGHT = 0;
		int WIN_WIDTH = 0;

		vector< vector<Node*> > node_map;
		map<int,string> terrain_key;
		vector<LTexture*> textures;
};
