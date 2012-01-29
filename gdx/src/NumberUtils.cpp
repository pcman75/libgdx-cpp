#include "stdafx.h"
#include "NumberUtils.h"

NumberUtils::utype NumberUtils::u;
NumberUtils::lutype NumberUtils::lu;

int NumberUtils::floatToIntBits(float value)
{
	if (_isnan(value)) 
	{
		return 0x7fc00000;
	} 
	else 
	{
		u.f = value;
		return u.i;
	}
}

int NumberUtils::floatToRawIntBits(float value)
{
	u.f = value;
	return u.i;
}

int NumberUtils::floatToIntColor(float value)
{
	return floatToRawIntBits(value);
}

float NumberUtils::intToFloatColor(int value)
{
	// This mask avoids using bits in the NaN range. See Float.intBitsToFloat javadocs.
	// This unfortunately means we don't get the full range of alpha.
	return intBitsToFloat(value & 0xfeffffff);
}

float NumberUtils::intBitsToFloat (int value)
{
	u.i = value;
	return u.f;
}

uint64_t NumberUtils::doubleToLongBits (double value)
{
	lu.df = value;
	return lu.li;
}

double NumberUtils::longBitsToDouble (uint64_t value)
{
	lu.li = value;
	return lu.df;
}
