#include "stdafx.h"
#include "SignReadScreen.h"
#include "InputMeta.h"

SignReadScreen::SignReadScreen (Screen* parent, int id) 
{
  std::vector<std::string> temp0;
  temp0.push_back( "READING");
  temp0.push_back( "");
  temp0.push_back( "PRESS UP TO READ SIGNS");

  std::vector<std::string> temp1;
  temp1.push_back( "JUMPING");
  temp1.push_back( "");
  temp1.push_back( "PRESS Z TO JUMP");
  temp1.push_back( "YOU CAN JUMP HIGHER BY");
  temp1.push_back( "GETTING A RUNNING START");
  temp1.push_back( "OR HOLDING DOWN Z");
  
  std::vector<std::string> temp2;
  temp2.push_back( "PROGRESSING");
  temp2.push_back( "");
  temp2.push_back( "LEAVE A ROOM THROUGH ANY");
  temp2.push_back( "EXIT TO CONTINUE YOUR");
  temp2.push_back( "ADVENTURE");


  std::vector<std::string> temp3;
  temp3.push_back( "DYING");
  temp3.push_back( "");
  temp3.push_back( "IF YOU DIE, YOU RESTART");
  temp3.push_back( "AT THE BEGINNING OF THE");
  temp3.push_back( "CURRENT ROOM");

  std::vector<std::string> temp4;
  temp4.push_back( "DODGING"); 
  temp4.push_back( "");
  temp4.push_back( "THE GUNNERS DON'T LIKE YOU");
  temp4.push_back( "AND SHOOT AT YOU.");
  temp4.push_back( "IT WOULD BE WISE TO STAY AWAY");

  std::vector<std::string> temp5;
  temp5.push_back( "THE LAUNCHER");
  temp5.push_back( "");
  temp5.push_back( "AS YOU PICK UP THE LAUNCHER,");
  temp5.push_back( "YOU REALIZE IT'S NOT YOUR");
  temp5.push_back( "AVERAGE LAUNCHER.");
  temp5.push_back( "");
  temp5.push_back( "PRESS UP AND DOWN TO AIM");
  temp5.push_back( "PRESS X TO FIRE THE LAUNCHER");

  std::vector<std::string> temp6;
  temp6.push_back( "JONESING"); 
  temp6.push_back( "");
  temp6.push_back( "DON'T FORGET YOUR FEDORA!");

  std::vector<std::string> temp7;
  temp7.push_back( "EXPLODING");
  temp7.push_back("");
  temp7.push_back("TNT BLOCKS ARE HIGHLY");
  temp7.push_back("EXPLOSIVE, AND WILL");
  temp7.push_back("REACT POORLY TO BEING");
  temp7.push_back("SHOT.");

  std::vector<std::string> temp8;
  temp8.push_back( "PUSHING");
  temp8.push_back( "");
  temp8.push_back( "THE CAMARADERIE BOX IS");
  temp8.push_back( "SOMETHING SOMETHING");
  temp8.push_back( "");
  temp8.push_back( "IT'S FROM PORTAL.");

  std::vector<std::string> temp9;
  std::vector<std::string> temp10;
  std::vector<std::string> temp11;
  std::vector<std::string> temp12;
  std::vector<std::string> temp13;
  /*
  signs =
  {
		{"BATTLING", "", "THE GREMLIN IS LARGE", "AND IN YOUR WAY.", "OVERHEAT IT TO DESTROY", "IT AND CLAIM YOUR PRIZE",},
		{"EVADING", "", "THE GUNNERS SHOTS WILL", "PASS THROUGH GLASS.", "YOU, HOWEVER, WILL NOT",},
		{"SWEATING", "", "THESE SLIGHTLY MORE", "SOPHISTICATED GREMLINS", "HAVE LEARNED A NEW", "TRICK",},
		{"CONVEYING", "", "TIME TO BURN OFF SOME", "FAT AND HAVE FUN WHILE", "DOING IT!",},
		{"BOSSFIGHTING", "", "BEHIND THIS DOOR, MEGAN", "AWAITS! WHO IS MEGAN?", "ARE YOU MEGAN?",},
		{"THE NEW LAUNCHER", "", "WELL, THIS IS BAD."},
		{"FEEDING", "", "THE JABBERWOCKY IS", "HUNGRY, AND WILL EAT", "WAY MORE THAN IT SHOULD", "", "PLEASE DO NOT FEED!",},
		{"HOVERING", "", "THE RECOIL ON THE NEW", "LAUNCHER SURE IS", "POWERFUL!",},
		{"FLYING", "", "SERIOUSLY, THE RECOIL", "IS OUT OF THIS WORLD!",},
		{"WINNING", "", "YOUR FINAL CHALLENGE", "IS RIGHT DOWN THIS", "HALLWAY.",},
		{"FRESHERERST", "", "BIG ADAM, GIANT SISTER.", "IT IS KNOWN BY MANY NAMES", "BUT JUDITH 4HRPG BLUEBERRY.", "", "FISSION MAILED!",
    },
  };
  */


  signs.push_back( temp0);
  signs.push_back( temp1);
  signs.push_back( temp2);
  signs.push_back( temp3);
  signs.push_back( temp4);
  signs.push_back( temp5);
  signs.push_back( temp6);
  signs.push_back( temp7);
  signs.push_back( temp8);

  delay = 15;
	this->parent = parent;
	this->id = id;
}

void SignReadScreen::render () 
{
	parent->render();
	spriteBatch->begin();
	int xs = 0;
	int ys = signs[id].size() + 3;
	for (int y = 0; y < signs[id].size(); y++) 
  {
		int s = signs[id][y].length();
		if (s > xs) xs = s;
	}
	int xp = 160 - xs * 3;
	int yp = 120 - ys * 3;
	for (int x = 0 - 1; x < xs + 1; x++) 
  {
		for (int y = 0 - 1; y < ys + 1; y++) 
    {
			int xf = 1;
			int yf = 12;
			if (x < 0) xf--;
			if (y < 0) yf--;
			if (x >= xs) xf++;
			if (y >= ys) yf++;
			draw(Art::guys[xf][yf], xp + x * 6, yp + y * 6);
		}
	}
	for (int y = 0; y < signs[id].size(); y++) 
  {
		drawString(signs[id][y], xp, yp + y * 6);
	}
	if (delay == 0) drawString("PRESS X", xp + (xs - 8) * 6, yp + (signs[id].size() + 2) * 6);

	spriteBatch->end();
}

void SignReadScreen::tick (InputMeta* input) 
{
	if (!input->oldButtons[InputMeta::ESCAPE] && input->buttons[InputMeta::ESCAPE]) 
  {
		setScreen(parent);
		return;
	}
	if (delay > 0) delay--;
	if (delay == 0 && input->buttons[InputMeta::SHOOT] && !input->oldButtons[InputMeta::SHOOT]) 
  {
		setScreen(parent);
	}
}