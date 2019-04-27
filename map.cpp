#include "map.h"

	Node::Node(){}

	Node::Node(int terr){
		terrain = terr;
	}

	//reads in a file that will create the map
	Map::Map(int x, int y, int radius, std::string filename, SDL_Renderer* gRenderer, std::vector<Item*> items, std::vector<Enemy*> enemies){
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
			}//checks the terrain type and saves the path to the texture for rendering

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

			file_in >> map_buffer;

			while(file_in >> map_buffer){
				//std::cout << map_buffer << std::endl;
				if(map_buffer != -1){
					int coor_x = 0;
					int coor_y = 0;
					file_in >> coor_x >> coor_y;
					std::cout << "id: " << map_buffer << " " << coor_x << " " << coor_y << std::endl;
					node_map[coor_y][coor_x]->currItem = items[map_buffer];
					//std::cout << node_map[coor_x][coor_y]->currItem << std::endl;
				}
				else
					break;
			}

			//file_in >> map_buffer;
			while(file_in >> map_buffer){
				if(map_buffer != -1){
					int coor_x = 0;
					int coor_y = 0;
					file_in >> coor_x >> coor_y;
					printf("buffer: %i\n", map_buffer);
					Enemy* spawn = new Enemy(enemies[map_buffer]);
					node_map[coor_y][coor_x]->currChar = spawn;
					printf("enemies: %s\n", enemies[map_buffer]->name.c_str());
				}
				else
					break;
			}//creates the enemies and figures out their locations on the map

			std::cout << std::endl;
			for(int i=0; i < node_map.size(); i++){
				for(int j=0; j < node_map[i].size(); j++){
					if(node_map[i][j]->currChar != NULL)
						std::cout << "1 ";
					else
						std::cout << "0 ";
				}
				std::cout << std::endl;
			}//prints a matrix of the map checking which spaces are occupied by an enemy/weapon/player
	}
	else{
		printf("Error: file is not opened\n");
	}

	//load in shimmer texture:
	render = gRenderer;
	shimmer->loadFromFile(render, "./assets/shimmer.png");
	loadtextures(x,y,radius);//renders the shimmer that indicates an item
}

void Map::RemoveItem(int y, int x){
	node_map[y][x]->currItem = NULL;
}//takes an item off the map

Map::Map(int width, int height, SDL_Renderer* gRenderer){
	render = gRenderer;

	LoadMap(width, height);
}//calls the renderer for the map

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
}//renders a "blank" map of dirt if passed no variables

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
}//renders the correct map textures when given the proper parameters

void Map::ClearMap(){

}

Node* Map::GetNode(int x, int y){
	return node_map[x][y];
}//returns a particular node on the map

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

		if(node_map[step_y-1][step_x-1]->currItem != NULL){
			shimmer->render(render, (step_x-1)*30, (step_y-1)*30);
		}
	}

	for(int i=0; i < torender.size(); i++){
		Position resultpos;
		resultpos.x = x+torender[i].x;
		resultpos.y = y+torender[i].y;
		if(resultpos.x >= 0 && resultpos.y >= 0 && resultpos.x < node_map[0].size() && resultpos.y < node_map.size()){
			//std::cout << resultpos.x << " " << resultpos.y << std::endl;
			LTexture* texture = textures[node_map[resultpos.y][resultpos.x]->terrain];
			texture->render(render, resultpos.x*30, resultpos.y*30);
			if(node_map[resultpos.y][resultpos.x]->currItem != NULL){
				//std::cout << "item: " << node_map[resultpos.y][resultpos.x]->currItem->itemName << std::endl;
				//LTexture* itemTexture;
				//itemTexture->loadFromFile(render, node_map[resultpos.y][resultpos.x]->currItem->texturePath);
				LTexture* itemTexture = node_map[resultpos.y][resultpos.x]->currItem->texture;
				itemTexture->render(render, resultpos.x*30, resultpos.y*30);
			}

			if(node_map[resultpos.y][resultpos.x]->currChar != NULL){
				LTexture* character = node_map[resultpos.y][resultpos.x]->currChar->texture;
				character->render(render, resultpos.x*30, resultpos.y*30);
			}
		}
	}
}//since our game only shows you a certain sized area at a time, this function renders a particular area around the player, determined by the given parameters



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
		//controller->movesLeft--;
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

void Dot::move(Map*& map)
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
		//std::cout << "trying at positon: " << controller->pos.y << ", " << controller->pos.x << std::endl;
		Node* curr_node = map->GetNode(controller->pos.y, controller->pos.x);
		if(curr_node->terrain == 2 || curr_node->currChar != NULL){
			mPosX -= mVelX;
			controller->pos.x -= mVelX/30;

			mPosY -= mVelY;
			controller->pos.y -= mVelY/30;
		}
	}
	//printf("mposx: %i | mposy: %i | mvelx: %i | mvely: %i | dotheight: %i | screenheight %i\n", mPosX, mPosY, mVelX, mVelY, DOT_HEIGHT, SCREEN_HEIGHT);
	//controller->printPos();
	//printf("Real location is: %i %i\n", mPosX, mPosY);

	// Item detection:
	// maybe move to seperate function:
	if(map->GetNode(controller->pos.y, controller->pos.x)->currItem != NULL){
		itemPickup(map, controller->pos.y, controller->pos.x);
		printf("item picked up!\n");
	}


	mVelX = 0;
	mVelY = 0;
}//handles the player running into iteams or walls

//add to player's inventory, use if potion
void Dot::itemPickup(Map*& map, int y, int x){
	Item* item = map->GetNode(y,x)->currItem;
	executeItem(item, controller);
	controller->addItem(item);

	// TEMP:
	if(item->type == "weapon")
		controller->currWeap = item;
	else if(item->type == "shield")
		controller->currWeap = item;
	map->RemoveItem(y,x);
}

void Dot::render(LTexture& gDotTexture, SDL_Renderer* gRenderer)
{
	//Show the player
	gDotTexture.render(gRenderer, mPosX, mPosY );
}
