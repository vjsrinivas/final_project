#include "map.h"

Node::Node(){}

Node::Node(int terr){
	terrain = terr;
}

Map::Map(int width, int height, string filename, SDL_Renderer* gRenderer){
	WIN_WIDTH = width;
	WIN_HEIGHT = height;

	ifstream file_in(filename.c_str());
	int map_x, map_y;

	if(file_in.is_open()){
		cout << "Opened up file" << endl;
		//read in texture paths:
		int texture_id = 0;
		string texture_path;
		
		while(file_in >> texture_id){
			if(texture_id != -1){
				file_in >> texture_path;
				terrain_key.insert(pair<int,string>(texture_id,texture_path));
			}
			else
				break;
		}
		
		int map_buffer;
		file_in >> map_x >> map_y;
		
		int tmp_x = 0;
		int tmp_y = 0;
		
		//resize vector<vector> 3x3:
		for(int i=0; i < map_y; i++){
			vector<Node*> row;
			row.resize(map_y,NULL);
			node_map.push_back(row);
		}

		while(file_in >> map_buffer){
			if(map_buffer != -1){
				if(tmp_x == map_x){
					tmp_x=0;
					tmp_y++;
				}

				tmp_x++;
				Node* entry = new Node(map_buffer);
				node_map[tmp_y][tmp_x-1] = entry;
			}
			else
				break;
		}	
	}
	else{
		printf("Error: file is not opened\n");	
	}

	render = gRenderer;
	loadtextures();
}

Map::Map(int width, int height, SDL_Renderer* gRenderer){
	render = gRenderer;

	LoadMap(width, height);
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
				dirt->render(render,j*30,i*30);
			}
		}
	}
	else{
		for(map<int,string>::iterator it=terrain_key.begin(); it != terrain_key.end(); it++){
			LTexture* texture = new LTexture();

			if(texture->loadFromFile(render, it->second)){
				textures.push_back(texture);
			}
			else
				cout << "err" << endl;
		}

		if(node_map.size() < WIN_WIDTH){
			for(int i=0; i < node_map.size(); i++){
				if(node_map[i].size() < WIN_HEIGHT){
					for(int j=0; j < node_map[i].size(); j++){
						LTexture* texture = textures[node_map[i][j]->terrain];
						texture->render(render, j*30,i*30);
					}
				}
				else{
					for(int j=0; j < WIN_HEIGHT; j++){
						LTexture* texture = textures[node_map[i][j]->terrain];
						texture->render(render, j*30,i*30);
					}
				}
			}
		}
		else{
			for(int i=0; i < WIN_WIDTH; i++){
				for(int j=0; j < WIN_HEIGHT; j++){
					LTexture* texture = textures[node_map[i][j]->terrain];
					texture->render(render,j*30,i*30);
				}
			}
		}
	}
		
}

void Map::ClearMap(){

}

Node* Map::GetNode(int x, int y){
	return node_map[x][y];
}

void Map::Redraw(int max_x, int max_y){
	


	for(int i=0; i < node_map.size(); i++){
		for(int j=0; j < node_map[i].size(); j++){
			LTexture* texture = textures[node_map[i][j]->terrain];
			texture->render(render,j*30,i*30);
		}
	}
}
