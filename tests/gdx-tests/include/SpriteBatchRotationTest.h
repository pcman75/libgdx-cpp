#pragma once
#include "GdxTest.h"
#include "Pixmap.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include "TextureRegion.h"
#include "Sprite.h"

class SpriteBatchRotationTest :public GdxTest 
{
private:
	SpriteBatch* spriteBatch;
	Texture* texture;
	// Font font;
	float angle;
	float scale;
	float vScale;
	//IntBuffer pixelBuffer;

public:
  SpriteBatchRotationTest();
  virtual ~SpriteBatchRotationTest();

  GDX_DEFINE_CREATOR(SpriteBatchRotationTest);

	virtual void render ();
  virtual void create ();
  
	virtual bool needsGL20 () 
  {
		return false;
	}
};
