#include "map.h"

	Node::Node(){}

	Node::Node(int terr){
		terrain = terr;
	}

	Map::Map(int x, int y, int radius, std::string filename, SDL_Renderer* gRenderer, std::vector<Item*> items){
		std::ifstream file_in(filename.c_str());
		int map_x, map_y;

		if(file_in.is_open()){
			std::cout << "Opened up file" << std::endl;
			//read in texture paths:
			int texture_id = 0;
			std::string texture_path;
			
			while(file_in >> texture_id){
				if(texture_id != -1){
					file_in >> texture_path;
					terrain_key.insert(std::pair<int,std::string>(texture_id,texture_path));
				}
				else
					break;
			}
			
			int map_buffer;
			file_in >> map_x >> map_y;
			width = map_x;
			height = map_y;
			
			int tmp_x = 0;
			int tmp_y = 0;
			
			//resize vector:
			for(int i=0; i < map_y; i++){
				std::vector<Node*> row;
				row.resize(map_x,NULL);
				node_map.push_back(row);
			}

			std::cout << "size of node: " << node_map.size() << " " <<node_map[0].size() << std::endl;

			for(int i=0; i < map_y; i++){
				for(int j=0; j < map_x; j++){
					file_in >> map_buffer;
					Node* new_node = new Node(map_buffer);
					node_map[i][j] = new_node;
					std::cout << map_buffer << " ";
				}
				std::cout << std::endl;
			}	

			while(file_in >> map_buffer){
				if(map_buffer != -1){
					int coor_x = 0; 
					int coor_y = 0;
					file_in >> coor_x >> coor_y;
					//std::cout << "id: " << map_buffer << " " << coor_x << " " << coor_y << std::endl;
					node_map[coor_x][coor_y]->currItem = items[map_buffer];
				}
				else
					break;
			}
	}
	else{
		printf("Error: file is not opened\n");	
	}


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
			std::vector<Node*> width_v;
			for(int j=0; j < width; j++){
				Node* default_value = new Node(0); 
				width_v.push_back(default_value);
			}
			node_map.push_back(width_v);
		}
	}
	else{
		std::cout << "Error! Map size is not above zero" << std::endl;
		exit(-1);
	}

	loadtextures();
}

void Map::loadtextures(){
	LTexture* dirt = new LTexture();

	if(dirt->loadFromFile(render, "./assets/dirt.png"))
		textures.push_back(dirt);
	else
		std::cout << "err" << std::endl;

	for(int i=0; i < node_map.size(); i++){
		for(int j=0; j < node_map[i].size(); j++){
			dirt->render(render, j*30, i*30);
		}
	}
}

void Map::loadtextures(int x, int y, int radius){
		for(std::map<int,std::string>::iterator it=terrain_key.begin(); it != terrain_key.end(); it++){
			LTexture* texture = new LTexture();

			if(texture->loadFromFile(render, it->second)){
				textures.push_back(texture);
			}
			else
				std::cout << "err" << std::endl;
		}

		std::cout << "node size: " << node_map.size() << " " << node_map[0].size() << std::endl;
		
		//i <- y
		//j <- x
		for(int i=0; i < node_map.size(); i++){
			for(int j=0; j < node_map[i].size(); j++){
				//std::cout << "trying: [" << i << ", " << j << "]" <<  std::endl;
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
	std::vector<Position> torender;
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

	step_x=0;
	step_y=1;

	for(int i=0; i < node_map.size()*node_map[0].size(); i++){
		if(node_map[0].size()==step_x){
			step_x=0;
			step_y++;
		}
		step_x++;

		LTexture* texture = textures[textures.size()-1];
		texture->render(render, (step_x-1)*30,(step_y-1)*30);
	}

	for(int i=0; i < torender.size(); i++){
		Position resultpos;
		resultpos.x = x+torender[i].x; 
		resultpos.y = y+torender[i].y;
		if(resultpos.x >= 0 && resultpos.y >= 0 && resultpos.x < node_map[0].size() && resultpos.y < node_map.size()){
			std::cout << resultpos.x << " " << resultpos.y << std::endl;
			LTexture* texture = textures[node_map[resultpos.y][resultpos.x]->terrain];
			texture->render(render, resultpos.x*30, resultpos.y*30);
		}
	}
}


Dot::Dot()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	controller = new Player();
}

Dot::Dot(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, std::string texturePath){
  //Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
 
	controller = new Player(texturePath);

  //set screen size:
  this->SCREEN_WIDTH = SCREEN_WIDTH;
  this->SCREEN_HEIGHT = SCREEN_HEIGHT;
}

void Dot::handleEvent( SDL_Event& e)
{
	//If a key was pressed
	/*
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
			case SDLK_UP: mVelY -= DOT_VEL; break;
			case SDLK_DOWN: mVelY += DOT_VEL; break;
			case SDLK_LEFT: mVelX -= DOT_VEL; break;
			case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}*/
	//If a key was released
	//else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	
	if(e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		controller->movesLeft--;
		//std::cout << "key let go" << std::endl;
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
			case SDLK_UP: mVelY -= DOT_VEL; break;
			case SDLK_DOWN: mVelY += DOT_VEL; break;
			case SDLK_LEFT: mVelX -= DOT_VEL; break;
			case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}
}

void Dot::move(Map* map)
{
	bool isBorder = false;

	if(mVelX != 0){
		mPosX += mVelX;
		controller->pos.x += mVelX/30;
	}
	else if(mVelY != 0){
		mPosY += mVelY;
		controller->pos.y += mVelY/30;
	}

	////
	////
	//Move the dot left or right
	//mPosX += mVelX;

	//If the dot went too far to the left or right
	if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > map->width*DOT_WIDTH ))
	{
		//Move back
		mPosX -= mVelX;
		controller->pos.x -= mVelX/30;
		isBorder = true;
	}

	//Move the dot up or down
	//mPosY += mVelY;

	//If the dot went too far up or down
	if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > map->height*DOT_HEIGHT ) )
	{
		//Move back
		mPosY -= mVelY;
		controller->pos.y -= mVelY/30;
		isBorder = true;
	}


	if(!isBorder){
		std::cout << "trying at positon: " << controller->pos.y << ", " << controller->pos.x << std::endl;
		Node* curr_node = map->GetNode(controller->pos.y, controller->pos.x);
		if(curr_node->terrain == 2){
			mPosX -= mVelX;
			controller->pos.x -= mVelX/30;

			mPosY -= mVelY;
			controller->pos.y -= mVelY/30;
		}
	}
	//printf("mposx: %i | mposy: %i | mvelx: %i | mvely: %i | dotheight: %i | screenheight %i\n", mPosX, mPosY, mVelX, mVelY, DOT_HEIGHT, SCREEN_HEIGHT);
	//controller->printPos();
	//printf("Real location is: %i %i\n", mPosX, mPosY);
	mVelX = 0;
	mVelY = 0;
}

void Dot::render(LTexture& gDotTexture, SDL_Renderer* gRenderer)
{
	//Show the dot
	gDotTexture.render(gRenderer, mPosX, mPosY );
}
