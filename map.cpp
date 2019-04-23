#include "map.h"

	Node::Node(){}

	Node::Node(int terr){
		terrain = terr;
	}

	Map::Map(int x, int y, int radius, string filename, SDL_Renderer* gRenderer){
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
			width = map_x;
			height = map_y;
			//cout << "x:y:" << map_x << " " << map_y << endl;

			int tmp_x = 0;
			int tmp_y = 0;
			
			//resize vector<vector> 3x3:
			for(int i=0; i < map_y; i++){
				vector<Node*> row;
				row.resize(map_x,NULL);
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
				//cout << "tmpx: " << tmp_x << " tmpy: " << tmp_y << endl;
			}
			else
				break;
		}	
	}
	else{
		printf("Error: file is not opened\n");	
	}

	//cout << "test" << endl;

	/*
	for(int i=0; i < node_map.size(); i++){
		for(int j=0; j < node_map[i].size(); j++){
			cout << node_map[i][j]->terrain << " ";
		}
		cout << endl;
	}*/

	render = gRenderer;
	loadtextures(x,y,radius);
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
	LTexture* dirt = new LTexture();

	if(dirt->loadFromFile(render, "./assets/dirt.png"))
		textures.push_back(dirt);
	else
		cout << "err" << endl;

	for(int i=0; i < node_map.size(); i++){
		for(int j=0; j < node_map[i].size(); j++){
			dirt->render(render, j*30, i*30);
		}
	}
}

void Map::loadtextures(int x, int y, int radius){
		for(map<int,string>::iterator it=terrain_key.begin(); it != terrain_key.end(); it++){
			LTexture* texture = new LTexture();

			if(texture->loadFromFile(render, it->second)){
				textures.push_back(texture);
			}
			else
				cout << "err" << endl;
		}

		cout << "node size: " << node_map.size() << " " << node_map[0].size() << endl;
		
		//i <- y
		//j <- x
		for(int i=0; i < node_map.size(); i++){
			for(int j=0; j < node_map[i].size(); j++){
				//cout << "trying: [" << i << ", " << j << "]" <<  endl;
				if(j < y+radius && j > y-radius && i < x+radius || i > x-radius){
					LTexture* texture = textures[node_map[i][j]->terrain];
					texture->render(render,j*30,i*30);
				}
				else{
					LTexture* texture = textures[textures.size()-1];
					texture->render(render,j*30,i*30);
				}
			}
		}		
}

void Map::ClearMap(){

}

Node* Map::GetNode(int x, int y){
	return node_map[x][y];
}

void Map::Redraw(int x, int y, int radius){
	//compute which blocks to render:
	vector<Position> torender;
	Position original; original.x = 0; original.y = 0;
	torender.resize((2*radius+1)*(2*radius+1), original);
	
	int step_x = -1*(radius);
	int step_y = -1*(radius);

	for(int i=0; i < (2*radius+1); i++){
		for(int j=0; j < (2*radius+1); j++){
			Position pos; pos.x = step_x; pos.y = step_y;
			torender[j+(2*radius+1)*i] = pos;
			step_x++;
		}
		step_x = -1*radius;
		step_y++;
	}

	

	for(int i=0; i < torender.size(); i++){
		Position resultpos;
		resultpos.x = x+torender[i].x; resultpos.y = y+torender[i].y;
		if(resultpos.x >= 0 && resultpos.y >= 0){
			//cout << resultpos.x << " " << resultpos.y << endl;
			LTexture* texture = textures[node_map[resultpos.x][resultpos.y]->terrain];
			texture->render(render, resultpos.x*30, resultpos.y*30);
		}
	}
//	cout << endl;

	/*
	for(int i=0; i < node_map.size(); i++){
		for(int j=0; j < node_map[i].size(); j++){
			//cout << "trying: [" << i << ", " << j << "]" <<  endl;
				if((j < y+radius && j > y-radius) && (i < x+radius && i > x-radius)){
					LTexture* texture = textures[node_map[i][j]->terrain];
					texture->render(render,j*30,i*30);
				}
				else{
					LTexture* texture = textures[textures.size()-1];
					texture->render(render,j*30,i*30);
				}
		}
	}*/
}
