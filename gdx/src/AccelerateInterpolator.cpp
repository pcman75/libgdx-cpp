#include "stdafx.h"
#include "AccelerateInterpolator.h"

float AccelerateInterpolator::DEFAULT_FACTOR = 1.0f;

AccelerateInterpolator::AccelerateInterpolator(float factor) 
{
	this->factor = factor;
	this->doubledFactor = factor * 2;
}

AccelerateInterpolator::~AccelerateInterpolator () 
{
}


void AccelerateInterpolator::finished () 
{
	delete this;
}

float AccelerateInterpolator::getInterpolation (float input) 
{
	if (factor == 1.0f) 
  {
		return input * input;
	} 
  else 
  {
		return (float) pow( ( double) input, doubledFactor);
	}
}

Interpolator* AccelerateInterpolator::copy () 
{
	return new AccelerateInterpolator(factor);
}