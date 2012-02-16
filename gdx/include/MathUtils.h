/*******************************************************************************
 * Copyright 2011 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

/** Utility and fast math functions.<br>
 * <br>
 * Thanks to Riven on JavaGaming.org for sin/cos/atan2/floor/ceil.<br> */

#pragma once

class MathUtils
{
public:
	static float PI;
	static const float radiansToDegrees;
	static const float degreesToRadians;

private:
	static MathUtils m_self;

	static const int SIN_BITS;
	static const int SIN_MASK;
	static const int SIN_COUNT;

	static const float m_radFull;
	static const float m_degFull;
	static const float m_radToIndex;
	static const float m_degToIndex;

	static float* m_sin;
	static float* m_cos;
	
	static const int ATAN2_BITS;
	static const int ATAN2_BITS2;
	static const int ATAN2_MASK;
	static const int ATAN2_COUNT;
	static const int ATAN2_DIM;
	static const float INV_ATAN2_DIM_MINUS_1;
	static float* m_atan2;

		
	static const int BIG_ENOUGH_INT;
	static const double BIG_ENOUGH_FLOOR;
	static const double CEIL;
	static const double BIG_ENOUGH_CEIL;
	static const double BIG_ENOUGH_ROUND;

private:
	MathUtils();

public:
	static float sin(float rad);

	static float cos(float rad);

	static float sinDeg(float deg);

	static float cosDeg(float deg);

	static float atan2 (float y, float x);

	/** Returns a random number between 0 (inclusive) and the specified value (inclusive). */
	static int random (int range);

	/** Returns a random number between start (inclusive) and end (inclusive). */
	static int random (int start, int end);

	static bool randomBoolean ();

	static float randomFloat();

	/** Returns a random number between 0 (inclusive) and the specified value (inclusive). */
	static float randomFloat(float range);

	/** Returns a random number between start (inclusive) and end (inclusive). */
	static float randomFloat(float start, float end);

	// ---

	static int nextPowerOfTwo (int value);

	static bool isPowerOfTwo (int value);

	// ---

	static int clamp (int value, int min, int max);

	static short clamp (short value, short min, short max);

	static float clamp (float value, float min, float max);

	/** Returns the largest integer less than or equal to the specified float. This method will only properly floor floats from
	 * -(2^14) to (Float.MAX_VALUE - 2^14). */
	static int floor (float x);

	/** Returns the largest integer less than or equal to the specified float. This method will only properly floor floats that are
	 * positive. Note this method simply casts the float to int. */
	static int floorPositive (float x);

	/** Returns the smallest integer greater than or equal to the specified float. This method will only properly ceil floats from
	 * -(2^14) to (Float.MAX_VALUE - 2^14). */
	static int ceil (float x);

	/** Returns the smallest integer greater than or equal to the specified float. This method will only properly ceil floats that
	 * are positive. */
	static int ceilPositive (float x);

	/** Returns the closest integer to the specified float. This method will only properly round floats from -(2^14) to
	 * (Float.MAX_VALUE - 2^14). */
	static int round (float x);

	/** Returns the closest integer to the specified float. This method will only properly round floats that are positive. */
	static int roundPositive (float x);
};

inline float min(float a, float b)
{
	return a > b ? b : a;
}

inline float max(float a, float b)
{
	return a > b ? a : b;
}