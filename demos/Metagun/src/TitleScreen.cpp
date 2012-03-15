#include "stdafx.h"
#include "TitleScreen.h"
#include "MathUtils.h"
#include "InputMeta.h"
#include "SoundMeta.h"
#include "GameScreen.h"
#include "ExpositionScreen.h"

TitleScreen::TitleScreen()
{
  time = 0;
}

void TitleScreen::render () 
{
	int yOffs = 480 - time * 2;
	if (yOffs < 0) yOffs = 0;
	spriteBatch->begin();
	draw( &Art::bg, 0, 0);
	draw( &Art::titleScreen, 0, -yOffs);
	if (time > 240) 
  {
		std::string msg;
		/*if( Gdx.app.getType() == ApplicationType.Android)
			msg = "TOUCH TO START";
		else*/
		msg = "PRESS X TO START";
		drawString( msg, 160 - msg.length() * 3, 140 - 3 - (int)( /*Math.*/abs(MathUtils::sin(time * 0.1) * 10)));

	}
	if (time >= 0) 
  {
		std::string msg = "COPYRIGHT MOJANG 2010";
		drawString( msg, 2, 240 - 6 - 2);
	}
	spriteBatch->end();
}

void TitleScreen::tick( InputMeta* input) 
{
	time++;
	if (time > 240) 
  {
		if (input->buttons[InputMeta::SHOOT] && !input->oldButtons[InputMeta::SHOOT] || Gdx.input->isTouched()) 
    {
			//SoundMeta::startgame->play();
			setScreen( new GameScreen());
			input->releaseAllKeys();
		}
	}
	if (time > 60 * 10) 
  {
		setScreen(new ExpositionScreen());
	}
}