#pragma once
#include <vector>
#include <stdio.h>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "game.h"
#include "ltexture.h"
#include "player.h"

class Node{
	public:
		Node();
		Node(int);
		int terrain;
		Player* currChar = NULL;
		Item* currItem = NULL;
};

class Map{
	public:
		Map(int,int,SDL_Renderer*);
		Map(int,int,int,std::string,SDL_Renderer*, std::vector<Item*>);
		void ClearMap();
		void LoadMap(int,int);
		Node* GetNode(int,int);
		void RemoveItem(int y, int x);
		void Redraw(int, int, int);
		int width;
		int height;

	private:
		void loadtextures();
		void loadtextures(int,int,int);
		SDL_Renderer* render;
		
		std::vector< std::vector<Node*> > node_map;
		std::map<int,std::string> terrain_key;
		std::vector<LTexture*> textures;
};


//The dot that will move around on the screen
	class Dot
	{
		public:
			//The dimensions of the dot
			static const int DOT_WIDTH = 30;
			static const int DOT_HEIGHT = 30;

			//Maximum axis velocity of the dot
			static const int DOT_VEL = 30;
			
			Player* controller;

			//Initializes the variables
			Dot();
		    Dot(const int, const int, std::string);

			//Takes key presses and adjusts the dot's velocity
			void handleEvent( SDL_Event& e);

			//Moves the dot
			void move(Map*&);

			//Shows the dot on the screen
			void render(LTexture& gDotTexture, SDL_Renderer* gRenderer);

		private:
			//The X and Y offsets of the dot
			int mPosX, mPosY;	
			//The velocity of the dot
			int mVelX, mVelY;
			int SCREEN_WIDTH;
			int SCREEN_HEIGHT;
			void itemPickup(Map*&, int, int);
	};
