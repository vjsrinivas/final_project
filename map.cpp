#include "map.h"
#include "ltexture.h"

Node::Node(){}

Node::Node(int terr){
	terrain = terr;
}

Map::Map(string filename, SDL_Renderer* gRenderer){
	ifstream file_in(filename.c_str());
	if(file_in.is_open()){
		string buffer;
		while(cin >> buffer){
			printf("%s", buffer.c_str());
		}
	}
	else{
		printf("Error: file is not opened\n");	
	}
}

Map::Map(int width, int height, SDL_Renderer* gRenderer){
	render = gRenderer;

	LoadMap(width, height);
	
	/*
	LTexture* dirt = new LTexture();

	if(dirt->loadFromFile(render, "./assets/dirt.png"))
		textures.push_back(dirt);
	else
		cout << "err" << endl;

	src.x = src.y = 0;
	dst.x = dst.y = 0;
	src.w = src.h = BOX_WIDTH;
	dst.w = dst.h = BOX_HEIGHT;
	dirt->render(gRenderer,100,100);
	*/
}

void Map::LoadMap(int width, int height){
	if(width > 0 && height > 0){
     for(int i=0; i < height; i++){
			vector<Node*> width_v;
			for(int j=0; j < width; j++){
				Node* default_value = new Node(0); 
				width_v.push_back(default_value);
			}
			node_map.push_back(width_v);
		}
	}
	else{
		cout << "Error! Map size is not above zero" << endl;
		exit(-1);
	}

	loadtextures();
}

void Map::loadtextures(){
	if(terrain_key.size() == 0){
		//render all dirt bruh:
		LTexture* dirt = new LTexture();
		
		if(dirt->loadFromFile(render, "./assets/dirt.png"))
			textures.push_back(dirt);
		else
			cout << "err" << endl;
		for(int i=0; i < node_map.size(); i++){
			for(int j=0; j < node_map[i].size(); j++){
				//node_map[i][j]
				dirt->render(render,j*30,i*30);
			}
		}
	}
	else{
		for(int i=0; i < node_map.size(); i++){
			LTexture* text = new LTexture();
		}
	}
		
}

void Map::ClearMap(){

}

Node* Map::GetNode(int x, int y){
	return node_map[x][y];
}
