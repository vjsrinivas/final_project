/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int BUTTON_WIDTH = SCREEN_WIDTH / 10;
const int BUTTON_HEIGHT = SCREEN_HEIGHT / 5;
const int TOTAL_BUTTONS = 10;
//button constants, ten along bottom viewport

enum LButtonSprite{
	BUTTON_SPRITE_MOUSE_DOWN = 0;
	BUTTON_SPRITE_MOUSE_UP = 1;
}
//handles events for clicking

//Texture wrapper class
class LTexture{
	public:
		LTexture();
		~LTexture();

		bool loadFromFile(std::string path);

		void free();

		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		void setBlendMode(SDL_BlendMode blending);

		void setAlpha(Uint8 alpha);

		void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RenderFlip flip = SDL_FLIP_NONE);

		int GetWidth();
		int GetHeight();

	private:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
}

class LButton{
	public:
		LButton();

		void setPosition(int x, int y)

		void handleEvent(SDL_Event *e);

		void render();

	private:
		SDL_Point mPosition;
		LButtonSprite mCurrentSprite;
}

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
LTexture gButtonSpriteSheetTexture;

LButton gButtons[TOTAL_BUTTONS];

LTexture::LTexture(){
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture(){
	free();
}

bool LTexture::loadFromFile(std::string path){

	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if(loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

		if(newTexture == NULL){
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;

}

void LTexture::free(){
	if(mTexture != NULL){
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending){
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha){
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point * center, SDL_RendererFlip flip){

	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	if(clip != NULL){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth(){
	return mWidth;
}

int LTexture::getHeight(){
	return mHeight;
}

LButton::Lbutton(){
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
}

void LButton::setPosition(int x, int y){
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e){

	if(e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;
		//check if mouse is inside buttons
		if(x < mPosition.x){
			inside = false;
		}

		else if(x > mPosition.x + BUTTON_WIDTH){
			inside = false;
		}

		else if(y < mPosition.y){
			inside = false;
		}
		else if(y > mPosition.y + BUTTON_HEIGHT){
			inside = false;
		}

		if(!inside){
			mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
		}

		else{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
		}
	}
}


void LButton::render(){
	gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load texture
	gTexture = loadTexture("viewport.png");
	if (gTexture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	if(!gButtonSpriteSheetTexture.loadFromFile("button.png")){
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else{
		for(int i = 0; i < BUTTON_SPRITE_TOTAL; i++){
			gSpriteClips[i].x = 0;
			gSpriteClips[i].y = SCREEN_HEIGHT / 5;
			gSpriteClips[i].w = BUTTON_WIDTH;
			gSpriteClips[i].h = BUTTON_HEIGHT;
		}

		gButtons[0].setPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
		gButtons[1].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
		gButtons[2].setPosition(SCREEN_WIDTH - BUTTON_WIDTH * 2, SCREEN_HEIGHT - BUTTON_HEIGHT);
		gButtons[3].setPosition(SCREEN_WIDTH - BUTTON_WIDTH * 3, SCREEN_HEIGHT - BUTTON_HEIGHT);
		gButtons[4].setPosition(SCREEN_WIDTH - BUTTON_WIDTH * 4, SCREEN_HEIGHT - BUTTON_HEIGHT);
		gButtons[5].setPosition(SCREEN_WIDTH - BUTTON_WIDTH * 5, SCREEN_HEIGHT - BUTTON_HEIGHT);
		gButtons[6].setPosition(SCREEN_WIDTH - BUTTON_WIDTH * 6, SCREEN_HEIGHT - BUTTON_HEIGHT);
		gButtons[7].setPosition(SCREEN_WIDTH - BUTTON_WIDTH * 7, SCREEN_HEIGHT - BUTTON_HEIGHT);
		gButtons[8].setPosition(SCREEN_WIDTH - BUTTON_WIDTH * 8, SCREEN_HEIGHT - BUTTON_HEIGHT);
		gButtons[9].setPosition(SCREEN_WIDTH - BUTTON_WIDTH * 9, SCREEN_HEIGHT - BUTTON_HEIGHT);
	}
	//Nothing to load
	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	gButtonSpriteSheetTexture.free();

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					for(int i = 0; i < TOTAL_BUTTONS; i++){
						gButtons[i].handleEvent(&e);
					}

				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Top left corner viewport
				SDL_Rect topLeftViewport;
				topLeftViewport.x = 0;
				topLeftViewport.y = 0;
				topLeftViewport.w = SCREEN_WIDTH;
				topLeftViewport.h = (SCREEN_HEIGHT*4) / 5;
				SDL_RenderSetViewport(gRenderer, &topLeftViewport);

				//Render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);


				//Top right viewport
				//SDL_Rect topRightViewport;
				//topRightViewport.x = SCREEN_WIDTH / 2;
				//topRightViewport.y = 0;
				//topRightViewport.w = SCREEN_WIDTH / 2;
				//topRightViewport.h = (SCREEN_HEIGHT*4) / 2;
				//SDL_RenderSetViewport(gRenderer, &topRightViewport);

				//Render texture to screen
				//SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);


				//Bottom viewport
				/*
				SDL_Rect bottomViewport;
				bottomViewport.x = 0;
				bottomViewport.y = SCREEN_HEIGHT-(SCREEN_HEIGHT / 5);
				bottomViewport.w = SCREEN_WIDTH;
				bottomViewport.h = SCREEN_HEIGHT / 5;
				SDL_RenderSetViewport(gRenderer, &bottomViewport);
				*/

				//Render texture to screen
				//SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_renderClear(gRenderer);

				for(int i = 0; i < TOTAL_BUTTONS; i++){
					gButtons[i].render();
				}

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
