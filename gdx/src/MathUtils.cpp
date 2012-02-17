#include "StdAfx.h"
#include "MathUtils.h"
#include "NumberUtils.h"



MathUtils  MathUtils::m_self;

float MathUtils::PI;

int MathUtils::SIN_BITS; // Adjust for accuracy.
int MathUtils::SIN_MASK;
int MathUtils::SIN_COUNT;

float MathUtils::m_radFull;
float MathUtils::m_degFull;
float MathUtils::m_radToIndex;
float MathUtils::m_degToIndex;

float MathUtils::radiansToDegrees;
float MathUtils::degreesToRadians;

float* MathUtils::m_sin;
float* MathUtils::m_cos;

int MathUtils::ATAN2_BITS; // Adjust for accuracy.
int MathUtils::ATAN2_BITS2;
int MathUtils::ATAN2_MASK;
int MathUtils::ATAN2_COUNT;
int MathUtils::ATAN2_DIM;
float MathUtils::INV_ATAN2_DIM_MINUS_1;
float* MathUtils::m_atan2;


// ---

int MathUtils::BIG_ENOUGH_INT;
double MathUtils::BIG_ENOUGH_FLOOR;
double MathUtils::CEIL;
double MathUtils::BIG_ENOUGH_CEIL;
double MathUtils::BIG_ENOUGH_ROUND;

MathUtils::MathUtils()
{
  PI = 3.1415927f;

  SIN_BITS = 13; // Adjust for accuracy.
  SIN_MASK = ~(-1 << SIN_BITS);
  SIN_COUNT = SIN_MASK + 1;

  m_radFull = PI * 2;
  m_degFull = 360;
  m_radToIndex = SIN_COUNT / m_radFull;
  m_degToIndex = SIN_COUNT / m_degFull;

  radiansToDegrees = 180.f / PI;
  degreesToRadians = PI / 180;


  ATAN2_BITS = 7; // Adjust for accuracy.
  ATAN2_BITS2 = ATAN2_BITS << 1;
  ATAN2_MASK = ~(-1 << ATAN2_BITS2);
  ATAN2_COUNT = ATAN2_MASK + 1;
  ATAN2_DIM = (int)sqrt((float)ATAN2_COUNT);
  INV_ATAN2_DIM_MINUS_1 = 1.0f / (ATAN2_DIM - 1);
  // ---
  BIG_ENOUGH_INT = 16 * 1024;
  BIG_ENOUGH_FLOOR = BIG_ENOUGH_INT;
  CEIL = 0.9999999;
  BIG_ENOUGH_CEIL = NumberUtils::longBitsToDouble(NumberUtils::doubleToLongBits(BIG_ENOUGH_INT + 1) - 1);
  BIG_ENOUGH_ROUND = BIG_ENOUGH_INT + 0.5f;





	//initialize random seed:
	srand((unsigned)time(NULL));

	m_sin = new float[SIN_COUNT];
	m_cos = new float[SIN_COUNT];
	for (int i = 0; i < SIN_COUNT; i++)
	{
		float a = (i + 0.5f) / SIN_COUNT * m_radFull;
		MathUtils::m_sin[i] = ::sin(a);
		MathUtils::m_cos[i] = ::cos(a);
	}
	for (int i = 0; i < 360; i += 90)
	{
		MathUtils::m_sin[(int)(i * m_degToIndex) & SIN_MASK] = ::sin(i * degreesToRadians);
		MathUtils::m_cos[(int)(i * m_degToIndex) & SIN_MASK] = ::cos(i * degreesToRadians);
	}

  m_atan2 = new float[ATAN2_COUNT];
	for (int i = 0; i < ATAN2_DIM; i++)
	{
		for (int j = 0; j < ATAN2_DIM; j++)
		{
			float x0 = (float)i / ATAN2_DIM;
			float y0 = (float)j / ATAN2_DIM;
			MathUtils::m_atan2[j * ATAN2_DIM + i] = ::atan2(y0, x0);
		}
	}
}

float MathUtils::sin(float rad)
{
	return m_sin[(int)(rad * m_radToIndex) & SIN_MASK];
}

float MathUtils::cos (float rad)
{
	return m_cos[(int)(rad * m_radToIndex) & SIN_MASK];
}

float MathUtils::sinDeg (float deg)
{
	return m_sin[(int)(deg * m_degToIndex) & SIN_MASK];
}

float MathUtils::cosDeg (float deg)
{
	return m_cos[(int)(deg * m_degToIndex) & SIN_MASK];
}

float MathUtils::atan2 (float y, float x)
{
	float add, mul;
	if (x < 0)
	{
		if (y < 0)
		{
			y = -y;
			mul = 1;
		}
		else
			mul = -1;
		x = -x;
		add = -PI;
	}
	else
	{
		if (y < 0)
		{
			y = -y;
			mul = -1;
		}
		else
			mul = 1;
		add = 0;
	}
	float invDiv = 1 / ((x < y ? y : x) * INV_ATAN2_DIM_MINUS_1);
	int xi = (int)(x * invDiv);
	int yi = (int)(y * invDiv);
	return (m_atan2[yi * ATAN2_DIM + xi] + add) * mul;
}

/** Returns a random number between 0 (inclusive) and the specified value (inclusive). */
int MathUtils::random(int range)
{
		return rand() % (range + 1);
}

/** Returns a random number between start (inclusive) and end (inclusive). */
int MathUtils::random(int start, int end)
{
	return start + random(end - start);
}

bool MathUtils::randomBoolean()
{
	return random(1) == 0;
}

float MathUtils::randomFloat()
{
	return (float)rand()/(float)RAND_MAX;
}

/** Returns a random number between 0 (inclusive) and the specified value (inclusive). */
float MathUtils::randomFloat(float range)
{
	return randomFloat() * range;
}

/** Returns a random number between start (inclusive) and end (inclusive). */
float MathUtils::randomFloat(float start, float end)
{
	return start + randomFloat() * (end - start);
}

// ---

int MathUtils::nextPowerOfTwo (int value)
{
	if (value == 0) return 1;
	value--;
	value |= value >> 1;
	value |= value >> 2;
	value |= value >> 4;
	value |= value >> 8;
	value |= value >> 16;
	return value + 1;
}

bool MathUtils::isPowerOfTwo (int value)
{
	return value != 0 && (value & value - 1) == 0;
}

// ---

int MathUtils::clamp (int value, int min, int max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

short MathUtils::clamp (short value, short min, short max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

float MathUtils::clamp (float value, float min, float max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}


/** Returns the largest integer less than or equal to the specified float. This method will only properly floor floats from
* -(2^14) to (Float.MAX_VALUE - 2^14). */
int MathUtils::floor (float x)
{
	return (int)(x + BIG_ENOUGH_FLOOR) - BIG_ENOUGH_INT;
}

/** Returns the largest integer less than or equal to the specified float. This method will only properly floor floats that are
* positive. Note this method simply casts the float to int. */
int MathUtils::floorPositive (float x)
{
	return (int)x;
}

/** Returns the smallest integer greater than or equal to the specified float. This method will only properly ceil floats from
* -(2^14) to (Float.MAX_VALUE - 2^14). */
int MathUtils::ceil (float x)
{
	return (int)(x + BIG_ENOUGH_CEIL) - BIG_ENOUGH_INT;
}

/** Returns the smallest integer greater than or equal to the specified float. This method will only properly ceil floats that
* are positive. */
int MathUtils::ceilPositive (float x)
{
	return (int)(x + CEIL);
}

/** Returns the closest integer to the specified float. This method will only properly round floats from -(2^14) to
* (Float.MAX_VALUE - 2^14). */
int MathUtils::round (float x)
{
	return (int)(x + BIG_ENOUGH_ROUND) - BIG_ENOUGH_INT;
}

/** Returns the closest integer to the specified float. This method will only properly round floats that are positive. */
int MathUtils::roundPositive (float x)
{
	return (int)(x + 0.5f);
}
