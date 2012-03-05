#include "stdafx.h"
#include "AccelerateDecelerateInterpolator.h"
#include "MathUtils.h"

float AccelerateDecelerateInterpolator::DEFAULT_FACTOR = 1.0f;


AccelerateDecelerateInterpolator::AccelerateDecelerateInterpolator(float factor)
{
	this->factor = factor;
	this->doubledFactor = factor * 2;
}
AccelerateDecelerateInterpolator::~AccelerateDecelerateInterpolator ()
{
}


void AccelerateDecelerateInterpolator::finished ()
{
	delete this;
}

float AccelerateDecelerateInterpolator::getInterpolation (float input)
{
	return (float)(MathUtils::cos((input + 1) * MathUtils::PI) / 2.0f) + 0.5f;
}

Interpolator* AccelerateDecelerateInterpolator::copy ()
{
	return new AccelerateDecelerateInterpolator(factor);
}