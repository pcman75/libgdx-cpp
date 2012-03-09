#include "stdafx.h"
#include "WorldRenderer.h"
#include "Assets.h"


const float WorldRenderer::FRUSTUM_WIDTH = 10;
const float WorldRenderer::FRUSTUM_HEIGHT = 15;

WorldRenderer::WorldRenderer(SpriteBatch* pBatch, World* pWorld)
	: world(pWorld), cam(FRUSTUM_WIDTH, FRUSTUM_HEIGHT),
	batch(pBatch)
{
	this->cam.position.set(FRUSTUM_WIDTH / 2, FRUSTUM_HEIGHT / 2, 0);
}

void WorldRenderer::render()
{
	if(world->bob.position.y > cam.position.y) 
		cam.position.y = world->bob.position.y;
	cam.update();
	batch->setProjectionMatrix(cam.combined);
	renderBackground();
	renderObjects();
}

void WorldRenderer::renderBackground()
{
	batch->disableBlending();
	batch->begin();
	batch->draw(Assets::backgroundRegion, cam.position.x - FRUSTUM_WIDTH / 2, cam.position.y - FRUSTUM_HEIGHT / 2, FRUSTUM_WIDTH, FRUSTUM_HEIGHT);
	batch->end();
}

void WorldRenderer::renderObjects()
{
	batch->enableBlending();
	batch->begin();
	renderBob();
	renderPlatforms();
	renderItems();
	renderSquirrels();
	renderCastle();
	batch->end();
}


void WorldRenderer::renderBob()
{
	TextureRegion* keyFrame;
	if(world->bob.state == Bob::BOB_STATE_FALL)
		keyFrame = Assets::bobFall->getKeyFrame(world->bob.stateTime, true);
	else if(world->bob.state == Bob::BOB_STATE_JUMP)
		keyFrame = Assets::bobJump->getKeyFrame(world->bob.stateTime, true);
	else
		keyFrame = Assets::bobHit;

	float side = world->bob.velocity.x < 0 ? -1 : 1;
	if(side < 0)
		batch->draw(keyFrame, world->bob.position.x + 0.5f, world->bob.position.y - 0.5f, side * 1, 1);
	else
		batch->draw(keyFrame, world->bob.position.x - 0.5f, world->bob.position.y - 0.5f, side * 1, 1);
}

void WorldRenderer::renderPlatforms()
{
	for(std::list<Platform>::iterator platform = world->platforms.begin(); platform != world->platforms.end(); platform++)
	{
		TextureRegion* keyFrame = Assets::platform;
		if(platform->state == Platform::PLATFORM_STATE_PULVERIZING)
		{
			keyFrame = Assets::brakingPlatform->getKeyFrame(platform->stateTime, true);
		}

		batch->draw(keyFrame, platform->position.x - 1, platform->position.y - 0.25f, 2, 0.5f);
	}
}

void WorldRenderer::renderItems()
{
	for(std::list<Spring>::iterator spring = world->springs.begin(); spring != world->springs.end(); spring++)
	{
		batch->draw(Assets::spring, spring->position.x - 0.5f, spring->position.y - 0.5f, 1, 1);
	}

	for(std::list<Coin>::iterator coin = world->coins.begin(); coin != world->coins.end(); coin++)
	{
		TextureRegion* keyFrame = Assets::coinAnim->getKeyFrame(coin->stateTime, true);
		batch->draw(keyFrame, coin->position.x - 0.5f, coin->position.y - 0.5f, 1, 1);
	}
}

void WorldRenderer::renderSquirrels()
{
	for(std::list<Squirrel>::iterator squirrel = world->squirrels.begin(); squirrel != world->squirrels.end(); squirrel++)
	{
		TextureRegion* keyFrame = Assets::squirrelFly->getKeyFrame(squirrel->stateTime, true);
		float side = squirrel->velocity.x < 0 ? -1 : 1;
		if(side < 0)
			batch->draw(keyFrame, squirrel->position.x + 0.5f, squirrel->position.y - 0.5f, side * 1, 1);
		else
			batch->draw(keyFrame, squirrel->position.x - 0.5f, squirrel->position.y - 0.5f, side * 1, 1);
	}
}

void WorldRenderer::renderCastle()
{
	Castle castle = world->castle;
	batch->draw(Assets::castle, castle.position.x - 1, castle.position.y - 1, 2, 2);
}

