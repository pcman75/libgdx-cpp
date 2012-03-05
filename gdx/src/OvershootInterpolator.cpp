#include "stdafx.h"
#include "OvershootInterpolator.h"

float OvershootInterpolator::DEFAULT_FACTOR = 1.0f;

OvershootInterpolator::OvershootInterpolator (float factor) 
{
	this->factor = factor;
	this->doubledFactor = factor * 2;
}
OvershootInterpolator::~OvershootInterpolator () 
{
}


void OvershootInterpolator::finished () 
{
	delete this;
}

float OvershootInterpolator::getInterpolation (float t) 
{
	t -= 1.0f;
	return t * t * ((factor + 1) * t + factor) + 1.0f;
}

Interpolator* OvershootInterpolator::copy () 
{
	return new OvershootInterpolator(factor);
}