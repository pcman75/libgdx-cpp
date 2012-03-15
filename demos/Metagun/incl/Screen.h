#pragma once

#include "SpriteBatch.h"
#include "TextureRegion.h"
#include "Metagun.h"
#include "Art.h"
class InputMeta;


class Screen 
{
protected: 
  //static Random random = new Random();
  std::vector<std::string> chars;
private: 
  Metagun* metagun;

public: 
  SpriteBatch* spriteBatch;

public:
  Screen();
  virtual void removed () ;

	virtual void init (Metagun* metagun) ;
  
	virtual void setScreen (Screen* screen) ;
  
	virtual void draw( TextureRegion* region, int x, int y) ;
  
	virtual void drawString ( std::string string, int x, int y) ;
  
  virtual void render () = 0;

	virtual void tick (InputMeta* input) ;
};
