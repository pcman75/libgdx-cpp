#include "stdafx.h"
#include "Block.h"

const float Block::BLOCK_RADIUS = 0.5f;

Block::Block(const Vector3& position)
{
	this->position.set(position);
}

