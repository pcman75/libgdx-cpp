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

class NumberUtils
{
public:
	static int floatToIntBits(float value);
	static int floatToRawIntBits(float value);
	static int floatToIntColor(float value);
	static float intToFloatColor(int value);
	static float intBitsToFloat (int value);
	static uint64_t doubleToLongBits (double value);
	static double longBitsToDouble (uint64_t tvalue);

private:
	static union lutype
	{
		double df; // assuming 64-bit
		uint64_t li;
	} lu;
	static union utype
	{
		float f;  // assuming 32-bit IEEE 754 single-precision
		int i;    // assuming 32-bit 2's complement int
	} u;
};
