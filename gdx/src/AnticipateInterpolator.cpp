#include "stdafx.h"
#include "AnticipateInterpolator.h"

float AnticipateInterpolator::DEFAULT_TENSION = 2.0f;


AnticipateInterpolator::AnticipateInterpolator(float tension) 
{
	this->tension = tension;
}

AnticipateInterpolator::~AnticipateInterpolator () 
{
}


void AnticipateInterpolator::finished () 
{
	delete this;
}

float AnticipateInterpolator::getInterpolation (float t) 
{
	return t * t * ((tension + 1) * t - tension);
}

Interpolator* AnticipateInterpolator::copy () 
{
	return new AnticipateInterpolator( tension);
}