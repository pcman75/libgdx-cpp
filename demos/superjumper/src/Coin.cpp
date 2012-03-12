#include "stdafx.h"
#include "Coin.h"

const float Coin::COIN_WIDTH = 0.5f;
const float Coin::COIN_HEIGHT = 0.8f;
const int Coin::COIN_SCORE = 10;

Coin::Coin(float x, float y) 
	: GameObject(x, y, COIN_WIDTH, COIN_HEIGHT)
{
	stateTime = 0;
}

void Coin::update (float deltaTime) 
{
	stateTime += deltaTime;
}

