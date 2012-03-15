#include "stdafx.h"
#include "Level.h"
#include "Art.h"
#include "BossPart.h"
#include "Boss.h"
#include "BossNeck.h"
#include "Gremlin.h"
#include "Jabberwocky.h"
#include "Hat.h"
#include "Sign.h"
#include "Gunner.h"
#include "Player.h"
#include "Camera.h"
#include "Screen.h"
#include "Explosion.h"
#include "SoundMeta.h"
#include "GameScreen.h"

double Level::FRICTION = 0.99;
double Level::GRAVITY = 0.10;

Level::Level (GameScreen* screen, int w, int h, int xo, int yo, int xSpawn, int ySpawn) 
{
	walls = NULL;
  respawnTime = 0;
  ntick = 0;
	
	this->screen = screen;
// int[] pixels = new int[32 * 24];
	this->xSpawn = xSpawn;
	this->ySpawn = ySpawn;

// Art.level.getRGB(xo * 31, yo * 23, 32, 24, pixels, 0, 32);

	walls = new unsigned char[w * h];
  //entityMap = new std::vector<Entity*>[w * h];
  entityMap.assign( w * h, std::list<Entity*>());

	this->width = w;
	this->height = h;

	for (int y = 0; y < h; y++) 
  {
		for (int x = 0; x < w; x++) 
    {
			//entityMap[x + y * w] = new std::vector<Entity*>;

// int col = pixels[x + y * w] & 0xffffff;
			//int col = (Art::level->getPixel(x + xo * 31, y + yo * 23) & 0xffffff00) >>> 8;
      int col = (Art::level->getPixel(x + xo * 31, y + yo * 23) & 0xffffff00);
      col = col >> 8;
      col &= 0x00ffffff;


			unsigned char wall = 0;

			if (col == 0xffffff)
				wall = 1;
			else if (col == 0xFF00FF)
				wall = 2;
			else if (col == 0xffff00)
				wall = 3;
			else if (col == 0xff0000)
				wall = 4;
			else if (col == 0xB7B7B7)
				wall = 5;
			else if (col == 0xFF5050)
				wall = 6;
			else if (col == 0xFF5051)
				wall = 7;
			else if (col == 0x383838)
				wall = 8;
			else if (col == 0xA3FFFF)
				wall = 9;
			else if (col == 0x83FFFF) 
      {
				BossPart* prev = new Boss(x * 10 - 2, y * 10 - 2);
				int timeOffs = MathUtils::random(60);
				((Boss*)prev)->time = timeOffs;
				add(prev);
				for (int i = 0; i < 10; i++) 
        {
					BossNeck* b = new BossNeck(x * 10 - 1, y * 10 - 1, prev);
					b->time = i * 10 + timeOffs;
					prev = b;
					add(prev);
				}
			} 
      else if (col == 0x80FFFF) 
      {
				Gremlin* g = new Gremlin(0, x * 10 - 10, y * 10 - 20);
				g->jumpDelay = MathUtils::random(50);
				add(g);
			} 
      else if (col == 0x81FFFF) 
      {
				Gremlin* g = new Gremlin(1, x * 10 - 10, y * 10 - 20);
				g->jumpDelay = MathUtils::random(50);
				add(g);
			} 
      else if (col == 0x82FFFF) 
      {
				Jabberwocky* g = new Jabberwocky(x * 10 - 10, y * 10 - 10);
				g->slamTime = MathUtils::random(30);
				add(g);
			} 
      else if (col == 0xFFADF8) 
      {
				add(new Hat(x * 10 + 1, y * 10 + 5, xo * 31 + x, yo * 23 + y));
			} 
      else if ((col & 0x00ffff) == 0x00ff00 && (col & 0xff0000) > 0) 
      {
				add(new Sign(x * 10, y * 10, (col >> 16) & 0xff));
			} 
      else if (col == 0x0000ff) 
      {
				// if (xSpawn == 0 && ySpawn == 0) {
				this->xSpawn = x * 10 + 1;
				this->ySpawn = y * 10 - 8;
				// }
			} 
      else if (col == 0x00FFFF) 
      {
				Gunner* e = new Gunner(x * 10 + 2, y * 10 + 10 - 6, 0, 0);
				e->chargeTime = MathUtils::random(Gunner.CHARGE_DURATION / 2);
				e->xa = e->ya = 0;

				add(e);
			}
			walls[x + y * w] = wall;
		}
	}
	player = new Player(this->xSpawn, this->ySpawn);
	add(player);
}

void Level::add (Entity* e) 
{
	entities.push_back(e);
	e->init(this);

	e->xSlot = (int)((e->x + e->w / 2.0) / 10);
	e->ySlot = (int)((e->y + e->h / 2.0) / 10);
	if (e->xSlot >= 0 && e->ySlot >= 0 && e->xSlot < width && e->ySlot < height) 
  {
		entityMap[e->xSlot + e->ySlot * width].push_back(e);
	}
}

void Level::tick () 
{
	ntick++;
	if (player->removed) 
  {
		respawnTime++;
		if (respawnTime == 20) 
    {
			screen->mayRespawn = true;
		}
	}

  std::vector<Entity*> toRemove;
  std::list<Entity*>::iterator it;
	//for (int i = 0; i < entities.size(); i++) 
  for( it = entities.begin(); it != entities.end(); it++)
  {
		Entity* e = *it;
		int xSlotOld = e->xSlot;
		int ySlotOld = e->ySlot;
		if (!e->removed) e->tick();
		e->xSlot = (int)((e->x + e->w / 2.0) / 10);
		e->ySlot = (int)((e->y + e->h / 2.0) / 10);
		if (e->removed) 
    {
			if (xSlotOld >= 0 && ySlotOld >= 0 && xSlotOld < width && ySlotOld < height) 
      {
				entityMap[xSlotOld + ySlotOld * width].remove(e);
			}
			//entities.remove(i--);
      toRemove.push_back( e);
		} 
    else 
    {
			if (e->xSlot != xSlotOld || e->ySlot != ySlotOld) 
      {
				if (xSlotOld >= 0 && ySlotOld >= 0 && xSlotOld < width && ySlotOld < height) 
        {
					entityMap[xSlotOld + ySlotOld * width].remove(e);
				}
				if (e->xSlot >= 0 && e->ySlot >= 0 && e->xSlot < width && e->ySlot < height) 
        {
					entityMap[e->xSlot + e->ySlot * width].push_back(e);
				} 
        else 
        {
					e->outOfBounds();
				}

			}
		}
	}

  for( int i = 0; i<toRemove.size(); i++)
  {
    entities.remove( toRemove[i]);
  }

}

	

std::vector<Entity*> Level::getEntities (double xc, double yc, double w, double h) 
{
	hits.clear();
	int r = 20;
	int x0 = (int)((xc - r) / 10);
	int y0 = (int)((yc - r) / 10);
	int x1 = (int)((xc + w + r) / 10);
	int y1 = (int)((yc + h + r) / 10);
	for (int x = x0; x <= x1; x++)
		for (int y = y0; y <= y1; y++) {
			if (x >= 0 && y >= 0 && x < width && y < height) 
      {
				std::list<Entity*> es = entityMap[x + y * width];
        std::list<Entity*>::iterator it;
				//for (int i = 0; i < es.size(); i++) 
        for( it = es.begin(); it != es.end(); it++)
        {
					Entity* e = *it;
					double xx0 = e->x;
					double yy0 = e->y;
					double xx1 = e->x + e->w;
					double yy1 = e->y + e->h;
					if (xx0 > xc + w || yy0 > yc + h || xx1 < xc || yy1 < yc) continue;

					hits.push_back(e);
				}
			}
		}
	return hits;
}

	

void Level::render (Screen* screen, Camera* camera) 
{
	matrix.idt();
	matrix.setToTranslation(camera->x, camera->y, 0);
	screen->spriteBatch->setTransformMatrix(matrix);
	screen->spriteBatch->begin();
	// g.translate(-camera->x, -camera->y);

	int xo = 0;
	int yo = 0;
	for (int x = xo; x <= xo + camera->width / 10; x++) 
  {
		for (int y = yo; y <= yo + camera->height / 10; y++) 
    {
			if (x >= 0 && y >= 0 && x < width && y < height) 
      {
				int ximg = 0;
				int yimg = 0;
				unsigned char w = walls[x + y * width];
				if (w == 0) yimg = 1;
				if (w == 1) ximg = 0;
				if (w == 2) ximg = 2;
				if (w == 3) ximg = 1;
				if (w == 9) ximg = 7;
				if (w == 8) 
        {
					ximg = 4;
					yimg = 1;
				}
				if (w == 5) 
        {
					ximg = 1;
					yimg = 1;
				}
				if (w == 6) 
        {
					ximg = (ntick / 4 + x * 2) & 3;
					yimg = 2;
				}
				if (w == 7) 
        {
					ximg = (-ntick / 4 + x * 2) & 3;
					yimg = 3;
				}
				if (w == 4) 
        {
					if (walls[x + (y - 1) * width] == 1) 
          {
						yimg++;
					}
					ximg = 3;
				}

				if (w == 0) continue;

				screen->draw(Art::walls[ximg][yimg], x * 10, y * 10);
			}
		}
	}

  std::list<Entity*>::reverse_iterator it;
	//for (int i = entities.size() - 1; i >= 0; i--) 
  for( it = entities.rbegin(); it != entities.rend(); it++)
  {
		Entity* e = *it;
		e->render(screen, camera);
	}

	screen->spriteBatch->end();
}

bool Level::isFree (Entity* ee, double xc, double yc, int w, int h, double xa, double ya) 
{
	if (ee->interactsWithWorld) 
  {
		return isBulletFree(ee, xc, yc, w, h);
	}
	double e = 0.1;
	int x0 = (int)(xc / 10);
	int y0 = (int)(yc / 10);
	int x1 = (int)((xc + w - e) / 10);
	int y1 = (int)((yc + h - e) / 10);
	bool ok = true;
	for (int x = x0; x <= x1; x++)
		for (int y = y0; y <= y1; y++) {
			if (x >= 0 && y >= 0 && x < width && y < height) 
      {
				unsigned char ww = walls[x + y * width];
				if (ww != 0) ok = false;
				if (ww == 8) ok = true;
				if (ww == 4 && ya != 0) ee->hitSpikes();
				if (ww == 6) 
        {
					ee->xa += 0.12;
				}
				if (ww == 7) 
        {
					ee->xa -= 0.12;
				}
			}
		}

	return ok;
}

bool Level::isBulletFree (Entity* bullet, double xc, double yc, int w, int h) 
{
	double e = 0.1;
	int x0 = (int)(xc / 10);
	int y0 = (int)(yc / 10);
	int x1 = (int)((xc + w - e) / 10);
	int y1 = (int)((yc + h - e) / 10);
	bool ok = true;
	for (int x = x0; x <= x1; x++)
		for (int y = y0; y <= y1; y++) 
    {
			if (x >= 0 && y >= 0 && x < width && y < height) 
      {
				unsigned char ww = walls[x + y * width];
				if (ww != 0) ok = false;
				if (ww == 5) ok = true;
				if (ww == 2) {
					int xPush = 0;
					int yPush = 0;

					if ( abs(bullet->xa) > abs(bullet->ya)) 
          {
						if (bullet->xa < 0) xPush = -1;
						if (bullet->xa > 0) xPush = 1;
					} 
          else 
          {
						if (bullet->ya < 0) yPush = -1;
						if (bullet->ya > 0) yPush = 1;
					}
					double r = 0.5;
					if (walls[(x + xPush) + (y + yPush) * width] == 0
						&& getEntities((x + xPush) * 10 + r, (y + yPush) * 10 + r, 10 - r * 2, 10 - r * 2).size() == 0) 
          {
						walls[x + y * width] = 0;
						walls[(x + xPush) + (y + yPush) * width] = 2;
					}
					bullet->remove();
				}
				if (ww == 3) 
        {
					//SoundMeta::boom->play();
					for (int i = 0; i < 16; i++) 
          {
						double dir = i * MathUtils::PI * 2 / 8.0;
						double xa = MathUtils::sin(dir);
						double ya = MathUtils::cos(dir);
						double dist = (i / 8) + 1;
						add(new Explosion(1, i * 3, x * 10 + 5 + xa * dist, y * 10 + 5 + ya * dist, xa, ya));
					}
					bullet->remove();
					walls[x + y * width] = 0;
				}
				if (ww == 9) 
        {
          Explosion* explosion = dynamic_cast<Explosion*>( bullet);

					if((NULL != explosion) && (explosion->power > 0) )
          {
						//SoundMeta::boom->play();
						for (int i = 0; i < 16; i++) 
            {
							double dir = i * MathUtils::PI * 2 / 8.0;
							double xa = MathUtils::sin(dir);
							double ya = MathUtils::cos(dir);
							double dist = (i / 8) + 1;
							add(new Explosion(1, i * 3, x * 10 + 5 + xa * dist, y * 10 + 5 + ya * dist, xa, ya));
						}
						bullet->remove();
						walls[x + y * width] = 0;
					}
				}
			}
		}

	return ok;
}

void Level::readSign (Sign* sign) 
{
	screen->readSign(sign->id - 1);
}

void Level::transition (int x, int y) 
{
	screen->transition(x, y);
}

void Level::getGun (int level) 
{
	screen->getGun(level);
}