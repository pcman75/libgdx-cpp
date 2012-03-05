#include "stdafx.h"
#include "DecelerateInterpolator.h"

float DecelerateInterpolator::DEFAULT_FACTOR = 1.0f;

DecelerateInterpolator::DecelerateInterpolator(float factor) 
{
	this->factor = factor;
	this->doubledFactor = factor * 2;
}
DecelerateInterpolator::~DecelerateInterpolator () 
{
}


void DecelerateInterpolator::finished () 
{
	delete this;
}

float DecelerateInterpolator::getInterpolation (float input) 
{
	if (factor == 1.0f) 
  {
		return 1.0f - (1.0f - input) * (1.0f - input);
	} 
  else 
  {
		return (float)(1.0f - pow( ( double) (1.0f - input), doubledFactor));
	}
}

Interpolator* DecelerateInterpolator::copy () 
{
	return new DecelerateInterpolator(factor);
}