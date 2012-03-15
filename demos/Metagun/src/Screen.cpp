#include "stdafx.h"
#include "Screen.h"



Screen::Screen()
{
  chars.push_back( "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
  chars.push_back( ".,!?:;\"'+-=/\\< ");

  metagun = NULL;
  spriteBatch = NULL;
}

void Screen::removed () 
{
	spriteBatch->dispose();
}

void Screen::init (Metagun* metagun) 
{
	this->metagun = metagun;
	Matrix4 projection;
	projection.setToOrtho(0, 320, 240, 0, -1, 1);

	spriteBatch = new SpriteBatch(100);
	spriteBatch->setProjectionMatrix(projection);
}

void Screen::setScreen (Screen* screen) 
{
	metagun->setScreen(screen);
}

	

void Screen::draw( TextureRegion* region, int x, int y) 
{
	int width = region->getRegionWidth();
	if (width < 0) width = -width;
	spriteBatch->draw(region, x, y, width, -region->getRegionHeight());
}

void Screen::drawString ( std::string string, int x, int y) 
{
  //string = string.toUpperCase();
  for (int i = 0; i < string.length(); i++)
  {
    string[i] = toupper(string[i]);
  }

	for (int i = 0; i < string.length(); i++) 
  {
    char ch = string[i];
		for (int ys = 0; ys < chars.size(); ys++) 
    {
			//int xs = chars[ys].indexOf(ch);
      const char* found = strchr( chars[ys].c_str(), ch);
      int xs = ( NULL != found) ? found - chars[ys].c_str() : -1;

			if (xs >= 0) 
      {
				draw(Art::guys[xs][ys + 9], x + i * 6, y);
			}
		}
	}
}

void Screen::tick (InputMeta* input) 
{
}