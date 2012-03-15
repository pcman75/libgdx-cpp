#include "stdafx.h"
#include "ExpositionScreen.h"
#include "InputMeta.h"
#include "TitleScreen.h"

ExpositionScreen::ExpositionScreen () 
{
  time = 0;

  /*
	try 
  {
    BufferedReader br = new BufferedReader(new InputStreamReader(Gdx.files.internal("res/exposition.txt").read()));

		std::string line = "";
		while ((line = br.readLine()) != NULL) 
    {
			lines.push_back(line);
		}
		br.close();
	} 
  catch (Exception e) 
  {
		e.printStackTrace();
	}
  */
}

void ExpositionScreen::render () 
{
	int w = -Art::bg.getRegionHeight();
	spriteBatch->begin();
	draw(& Art::bg, 0, -(time / 8 % w));
	draw(& Art::bg, 0, -(time / 8 % w) + w);

	int yo = time / 4;
	for (int y = 0; y <= 240 / 6; y++) 
  {
		int yl = yo / 6 - 240 / 6 + y;
		if (yl >= 0 && yl < lines.size()) 
    {
			drawString(lines[yl], (320 - 40 * 6) / 2, y * 6 - yo % 6);
		}
	}
	spriteBatch->end();
}

void ExpositionScreen::tick (InputMeta* input) 
{
	time++;
	if (time / 4 > lines.size() * 6 + 250) 
  {
		setScreen( new TitleScreen());
	}
	if( input->buttons[InputMeta::SHOOT] && !input->oldButtons[InputMeta::SHOOT] || Gdx.input->isTouched()) 
  {
		setScreen( new TitleScreen());
	}
	if (input->buttons[InputMeta::ESCAPE] && !input->oldButtons[InputMeta::ESCAPE]) 
  {
		setScreen(new TitleScreen());
	}
}