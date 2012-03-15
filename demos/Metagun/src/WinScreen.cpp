#include "stdafx.h"
#include "WinScreen.h"
#include "Art.h"
#include "InputMeta.h"
#include "Stats.h"
#include "TitleScreen.h"

WinScreen::WinScreen()
{
  time = 0;
}

void WinScreen::render () 
{
	spriteBatch->begin();
	int w = 240 * 8; // Art.bg.getHeight();
	draw(&Art::bg, 0, -(time * 2 % w));
	draw(&Art::bg, 0, -(time * 2 % w) + w);

	int offs0 = 500 - time * 10;
	if (offs0 < 0) offs0 = 0;
	int offs1 = 1200 - time * 16;
	if (offs1 < 0) offs1 = 0;
	int yOffs = 600 - time * 5;
	if (yOffs < -120) yOffs = -120;
	if (yOffs > 0) yOffs = 0;
	draw(&Art::winScreen1, offs0, yOffs + 30);
	draw(&Art::winScreen2, -offs1, yOffs * 2 / 3 + 30);

	int tt = time - (60 * 2 + 30);
	int yo = 130;
	int xo = 120 - 8 * 3;
	if (tt >= 0) 
  {
    std::stringstream str;
    //drawString("       TIME: " + Stats::instance.getTimeString(), xo, yo + 0 * 6);
    str << "       TIME: " << Stats::instance.getTimeString();
    drawString( str.str().c_str(), xo, yo + 0 * 6);
		
		//drawString("     DEATHS: " + Stats::instance.deaths, xo, yo + 1 * 6);
    str.clear();
    str << "     DEATHS: " << Stats::instance.deaths;
    drawString(str.str().c_str(), xo, yo + 1 * 6);

		//drawString("    FEDORAS: " + Stats::instance.hats + "/" + 7, xo, yo + 2 * 6);
    str.clear();
    str << "    FEDORAS: " << Stats::instance.hats << "/" << 7;
    drawString(str.str().c_str(), xo, yo + 2 * 6);

		//drawString("SHOTS FIRED: " + Stats::instance.shots, xo, yo + 3 * 6);
    str.clear();
    str << "SHOTS FIRED: " << Stats::instance.shots;
    drawString(str.str().c_str(), xo, yo + 3 * 6);

		//drawString("FINAL SCORE: " + timeScale(Stats::instance.getFinalScore(), tt - 30 * 5), xo, yo + 5 * 6);
    str.clear();
    str << "FINAL SCORE: " << timeScale(Stats::instance.getFinalScore(), tt - 30 * 5);
    drawString(str.str().c_str(), xo, yo + 5 * 6);
    
		//drawString(timeHideScale(Stats::instance.getSpeedScore(), tt - 30 * 1), xo + 20 * 6, yo + 0 * 6);
    str.clear();
    str << timeHideScale(Stats::instance.getSpeedScore(), tt - 30 * 1);
    drawString(str.str().c_str(), xo + 20 * 6, yo + 0 * 6);

		//drawString(timeHideScale(Stats::instance.getDeathScore(), tt - 30 * 2), xo + 20 * 6, yo + 1 * 6);
    str.clear();
    str << timeHideScale(Stats::instance.getDeathScore(), tt - 30 * 2);
    drawString(str.str().c_str(), xo + 20 * 6, yo + 1 * 6);

		//drawString(timeHideScale(Stats::instance.getHatScore(), tt - 30 * 3), xo + 20 * 6, yo + 2 * 6);
    str.clear();
    str << timeHideScale(Stats::instance.getHatScore(), tt - 30 * 3);
    drawString(str.str().c_str(), xo + 20 * 6, yo + 2 * 6);

		//drawString(timeHideScale(Stats::instance.getShotScore(), tt - 30 * 4), xo + 20 * 6, yo + 3 * 6);
    str.clear();
    str << timeHideScale(Stats::instance.getShotScore(), tt - 30 * 4);
    drawString(str.str().c_str(), xo + 20 * 6, yo + 3 * 6);

	}

	if (time > 60 * 7 && (time / 30 % 2 == 0)) 
  {
		std::string msg = "PRESS X TO RESET THE GAME";
		drawString( msg, 160 - msg.length() * 3, yo + 10 * 6);
	}
	spriteBatch->end();
}

std::string WinScreen::timeHideScale (int val, int time) 
{
	if (time < 10) return "";
// if (time>60+60) return "";
	if (time < 0) time = 0;
	if (time > 60) time = 60;
	return "+" + val * time / 60;
}

std::string WinScreen::timeScale (int val, int time) 
{
	if (time < 0) time = 0;
	if (time > 60) time = 60;

  std::stringstream ret;
  ret << "" << val * time / 60;
  return ret.str().c_str();
}

void WinScreen::tick (InputMeta* input) 
{
	time++;
	if (time > 60 * 7) 
  {
		if (input->buttons[InputMeta::SHOOT] && !input->oldButtons[InputMeta::SHOOT]) 
    {
			setScreen(new TitleScreen());
		}
	}
}