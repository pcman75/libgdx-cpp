#include "stdafx.h"
#include "Player.h"
#include "Art.h"
#include "SoundMeta.h"
#include "InputMeta.h"
#include "Level.h"
#include "Hat.h"
#include "PlayerGore.h"
#include "Gore.h"
#include "Bullet.h"
#include "Gunner.h"
#include "Sign.h"
#include "Stats.h"
#include "Screen.h"

Player::Player (int x, int y) 
{
  dir = 1;
	yAim = 0;
	frame = 0;
	noHurtTime = 0;
  shootTime = 0;
  gunLevel = 0;
	breadSign = false;
  hatCount = 1;
	damage = 0;

	this->x = x;
	this->y = y;
	w = 8;
	h = 18;
	bounce = 0;
}

void Player::tick () 
{
}

void Player::render (Screen* g, Camera* camera) 
{
	// g.setColor(Color.GREEN);
	int xp = (int)x - (16 - w) / 2;
	int yp = (int)y - 2;
	// g.fillRect(xp, yp, w, h);

	int stepFrame = frame / 4 % 4;

	TextureRegion*** sheet = dir == 1 ? Art::player1 : Art::player2;
	if (!onGround) 
  {
		int yya = (int)MathUtils::round(-ya);
		stepFrame = 4;
		if (yya < -1) stepFrame = 5;
		yp += yya;
	}
	g->draw(sheet[3 + stepFrame][hatCount > 0 ? 0 : 1], xp, yp);

	yp += (stepFrame == 3 ? 1 : 0);
	for (int i = 1; i < hatCount; i++) 
  {
		g->draw(sheet[0][1], xp, yp - i * 2);
	}

	if (gunLevel > 0) 
  {
		if (!onGround) 
    {
			int yya = (int)MathUtils::round(-ya);
			if (yya < -1) yya = -1;
			if (yya > 1) yya = 1;
			yp += yya;
		}
		g->draw(sheet[1 + yAim][(gunLevel - 1) * 2], xp, yp);
	}
}

void Player::tick (InputMeta* input) 
{
	breadSign = true; // onGround && input->buttons[InputMeta::UP] && !input->oldButtons[InputMeta::UP];
	if (noHurtTime > 0) noHurtTime--;
	double speed = 0.4;
	double aimAngle = -0.2;
	yAim = 0;
	if (input->buttons[InputMeta::UP]) 
  {
		aimAngle -= 0.8;
		yAim--;
	}
	if (input->buttons[InputMeta::DOWN]) 
  {
		aimAngle += 0.8;
		yAim++;
	}
	bool walk = false;
	if (input->buttons[InputMeta::LEFT]) 
  {
		walk = true;
		xa -= speed;
		dir = -1;
	}
	if (input->buttons[InputMeta::RIGHT]) 
  {
		walk = true;
		xa += speed;
		dir = 1;
	}
	if (walk)
		frame++;
	else
		frame = 0;
	if (input->buttons[InputMeta::JUMP] && !input->oldButtons[InputMeta::JUMP] && onGround) 
  {
		//SoundMeta::jump->play();
		ya -= 2 + fabs(xa) * 0.5;
	}

	tryMove(xa, ya);

	xa *= 0.7;
	if (ya < 0 && input->buttons[InputMeta::JUMP]) 
  {
		ya *= 0.992;
		ya += Level::GRAVITY * 0.5;
	} else {
		ya *= Level::FRICTION;
		ya += Level::GRAVITY;
	}

	bool shooting = false;
	if (gunLevel > 0 && input->buttons[InputMeta::SHOOT] && !input->oldButtons[InputMeta::SHOOT]) shooting = true;
	if (gunLevel > 1 && input->buttons[InputMeta::SHOOT] && (!input->oldButtons[InputMeta::SHOOT] || shootTime > 0)) 
  {
		shooting = shootTime++ % 3 == 0;
	} else {
		shootTime = 0;
	}
	if (shooting) 
  {
		double pow = 3;
		//SoundMeta::launch->play();

		double xx = x + w / 2.0 - 2.5 + dir * 7;
		double yy = y + h / 2.0 - 2.5 + yAim * 2;
		for (int i = 0; i < 4; i++) 
    {
			double xAim = MathUtils::cos(aimAngle + 0.2) * dir * pow;
			double yAim = MathUtils::sin(aimAngle + 0.2) * pow;
			double xxa = xa + xAim * 0.2;
			double yya = ya + yAim * 0.2;
			level->add(new Spark(xx, yy + (-2 + i) * 0.5, xxa, yya));
		}
		double xAim = MathUtils::cos(aimAngle) * dir * pow;
		double yAim = MathUtils::sin(aimAngle) * pow;
		double xxa = xa + xAim;
		double yya = ya + yAim;
		if (gunLevel == 2) 
    {
			xa -= xAim * 0.1;
			ya -= yAim * 0.1;
		}
		xx = x + w / 2.0 - 2.5;
		Stats::instance.shots++;
		level->add(new Gunner(xx, yy, xxa, yya));
	}

	if (y < 5) level->transition(0, -1);
	if (y > 240 - w + 10 - 5) level->transition(0, 1);
	if (x < 0 + 5) level->transition(-1, 0);
	if (x > 320 - h + 10 - 5) level->transition(1, 0);
}

void Player::hitSpikes () 
{
	die();
}

void Player::die () 
{
	if (removed) return;
	if (hatCount > 0) 
  {
		level->add(new Hat(x, y - hatCount * 2));
		hatCount--;
	}
	//SoundMeta::death->play();
	for (int i = 0; i < 16; i++) 
  {
		level->add(new PlayerGore(x + MathUtils::randomFloat(1) * w, y + MathUtils::randomFloat(1) * h));
	}
	Stats::instance.deaths++;
	remove();
}

bool Player::shot (Bullet* bullet) 
{
	//SoundMeta::pew->play();
	xa += bullet->xa * 0.5;
	ya += bullet->ya * 0.5;
	for (int i = 0; i < 4; i++) 
  {
		double xd = (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 4 - bullet->xa * 3;
		double yd = (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * 4 - bullet->ya * 3;
		level->add(new Gore(bullet->x, bullet->y, xa + xd, ya + yd));
	}
	if (noHurtTime != 0) return true;

	if (hatCount > 0) 
  {
		while (hatCount > 0) 
    {
			Hat* hat = new Hat(x, y);
			hat->ya -= hatCount * 0.05;
			hat->xxa = (MathUtils::randomFloat(1) - MathUtils::randomFloat(1)) * (hatCount - 1) * 0.5;
			hat->time += hatCount * 6;
			level->add(hat);
			hat->tryMove(0, -hatCount * 2);
			hatCount--;
		}
		noHurtTime = 20;
	} 
  else 
  {
		//SoundMeta::oof->play();
		damage++;
		noHurtTime = 20;
		if (damage == 4) 
    {
			//SoundMeta::death->play();
			for (int i = 0; i < 16; i++) 
      {
				level->add(new PlayerGore(x + MathUtils::randomFloat(1) * w, y + MathUtils::randomFloat(1) * h));
			}
			remove();
		} 
    else 
    {
			level->add(new PlayerGore(bullet->x, bullet->y));
		}
	}

	return true;
}

void Player::readSign (Sign* sign) 
{
	if (sign->autoRead || breadSign) 
  {
		sign->autoRead = false;
		if (sign->id == 6) 
    {
			sign->remove();
			gunLevel = 1;
			level->getGun(1);
		}
		if (sign->id == 15) 
    {
			sign->remove();
			gunLevel = 2;
			level->getGun(2);
		}
		level->readSign(sign);
	}
	sign->remove();
}

void Player::outOfBounds () 
{
}

void Player::explode (Explosion* explosion) 
{
	die();
}

void Player::collideMonster (Entity* e) 
{
	die();
}

