#include "stdafx.h"
#include "Art.h"

TextureRegion*** Art::guys = NULL;
TextureRegion*** Art::player1 = NULL;
TextureRegion*** Art::player2 = NULL;
TextureRegion*** Art::walls = NULL;
TextureRegion*** Art::gremlins = NULL;
TextureRegion Art::bg;
Pixmap* Art::level = NULL;
TextureRegion Art::titleScreen;
TextureRegion Art::shot;
TextureRegion*** Art::buttons = NULL;

TextureRegion Art::winScreen1;
TextureRegion Art::winScreen2;



void Art::load () 
{
	bg = load("res/background.png", 320, 240);
	level = new Pixmap(Gdx.files->internalHandle("res/levels.png"));
	titleScreen = load("res/titlescreen.png", 320, 740);
	guys = split("res/guys.png", 6, 6);
	player1 = split("res/player.png", 16, 32);
	player2 = split("res/player.png", 16, 32, true);
	walls = split("res/walls.png", 10, 10);
	gremlins = split("res/gremlins.png", 30, 30);
	buttons = split("res/buttons.png", 32, 32);
	shot = new TextureRegion(guys[0][0]->getTexture(), 3, 27, 2, 2);
	winScreen1 = load("res/winscreen1.png", 320, 240);
	winScreen2 = load("res/winscreen2.png", 320, 240);
}

TextureRegion*** Art::split (std::string name, int width, int height) 
{
	return split(name, width, height, false);
}

TextureRegion*** Art::split (std::string name, int width, int height, bool flipX) 
{
	Texture* texture = new Texture(Gdx.files->internalHandle(name));
	int xSlices = texture->getWidth() / width;
	int ySlices = texture->getHeight() / height;

	TextureRegion*** res = new TextureRegion**[xSlices];

	for (int x = 0; x < xSlices; x++) 
  {
    res[x] = new TextureRegion*[ySlices];
		for (int y = 0; y < ySlices; y++) 
    {
			res[x][y] = new TextureRegion(texture, x * width, y * height, width, height);
			res[x][y]->flip(flipX, true);
		}
	}
	return res;
}

TextureRegion Art::load (std::string name, int width, int height) 
{
  Texture* texture = new Texture(Gdx.files->internalHandle(name));
	TextureRegion* region = new TextureRegion(texture, 0, 0, width, height);
	region->flip(false, true);
	return region;
}