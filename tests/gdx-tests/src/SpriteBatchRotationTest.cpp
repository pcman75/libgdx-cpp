#include "stdafx.h"
#include "SpriteBatchRotationTest.h"


SpriteBatchRotationTest::SpriteBatchRotationTest()
{
  spriteBatch = NULL;
	texture = NULL;
  angle = 0;
	scale = 1;
	vScale = 1;
}

SpriteBatchRotationTest::~SpriteBatchRotationTest()
{
}


void SpriteBatchRotationTest::create () 
{
	spriteBatch = new SpriteBatch();

  //texture = new Texture( Gdx.files->internalHandle("data/test.png"));
  Pixmap* pPm = new Pixmap( Gdx.files->internalHandle("data/badlogicsmall.jpg"));
  texture = new Texture( pPm);


	// font = Gdx.graphics.newFont("Arial", 12, FontStyle.Plain);

	//ByteBuffer buffer = ByteBuffer.allocateDirect(4);
	//buffer.order(ByteOrder.nativeOrder());
	//pixelBuffer = buffer.asIntBuffer();

}



void SpriteBatchRotationTest::render() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	spriteBatch->begin();
	spriteBatch->draw(texture, 16, 10, 16, 16, 32, 32, 1, 1, 0, 0, 0, texture->getWidth(), texture->getHeight(), false, false);
	spriteBatch->draw(texture, 64, 10, 32, 32, 0, 0, texture->getWidth(), texture->getHeight(), false, false);
	spriteBatch->draw(texture, 112, 10, 0, 0, texture->getWidth(), texture->getHeight());

	spriteBatch->draw(texture, 16, 58, 16, 16, 32, 32, 1, 1, angle, 0, 0, texture->getWidth(), texture->getHeight(), false, false);
	spriteBatch->draw(texture, 64, 58, 16, 16, 32, 32, scale, scale, 0, 0, 0, texture->getWidth(), texture->getHeight(), false,
		false);
	spriteBatch->draw(texture, 112, 58, 16, 16, 32, 32, scale, scale, angle, 0, 0, texture->getWidth(), texture->getHeight(),
		false, false);
	spriteBatch->draw(texture, 160, 58, 0, 0, 32, 32, scale, scale, angle, 0, 0, texture->getWidth(), texture->getHeight(), false,
		false);

	// spriteBatch->drawText(font, "Test", 208, 10, Color.WHITE);
	spriteBatch->end();
	glFlush();

	// if( false )
	// {
	// Gdx.graphics.getGL10().glReadPixels( 16, 10, 1, 1, GL10.GL_RGBA,
	// GL10.GL_UNSIGNED_BYTE, pixelBuffer );
	// if( pixelBuffer.get(0) != 0xff00ff00 )
	// throw new GdxRuntimeException( "not pixel perfect!" );
	// Gdx.graphics.getGL10().glReadPixels( 47, 10, 1, 1, GL10.GL_RGBA,
	// GL10.GL_UNSIGNED_BYTE, pixelBuffer );
	// if( pixelBuffer.get(0) != 0xffff0000 )
	// throw new GdxRuntimeException( "not pixel perfect!" );
	// Gdx.graphics.getGL10().glReadPixels( 16, 41, 1, 1, GL10.GL_RGBA,
	// GL10.GL_UNSIGNED_BYTE, pixelBuffer );
	// if( pixelBuffer.get(0) != 0xff0000ff )
	// throw new GdxRuntimeException( "not pixel perfect!" );
	// }

	//angle += 20 * Gdx.graphics->getDeltaTime();
  angle += 20;

	scale += vScale * Gdx.graphics->getDeltaTime();
	if (scale > 2) {
		vScale = -vScale;
		scale = 2;
	}
	if (scale < 0) {
		vScale = -vScale;
		scale = 0;
	}

}

