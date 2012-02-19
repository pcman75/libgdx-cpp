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


/**
 * List of GdxTest classes. To be used by the test launchers. If you write your
 * own test, add it in here!
 */
#pragma once

#include "GdxTest.h"
#include "GdxTestsDefines.h"

class GdxTestsDllImportExport GdxTests
{
private:
	static GdxTests self;
	GdxTests();
public:
	typedef std::map<std::string, GdxTest* (*)()> TestsMap;
	typedef std::map<std::string, GdxTest* (*)()>::iterator TestsMapIterator;

	static TestsMap tests;
	static GdxTest* newTest(const char* name);
};
