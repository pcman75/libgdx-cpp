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

#pragma once
#include "GdxDefines.h"
#include "TemporalAction.h"

class GdxDllImportExport Repeat : public TemporalAction 
{
protected:
  int times;
	int finishedTimes;

public:
  Repeat(Action* action, int times);
  virtual ~Repeat();

	virtual void reset ();

	virtual void setTarget (Actor* actor);

	virtual void act (float delta);

	virtual bool isDone ();

	virtual void finish ();

  virtual Action* copy ();

	virtual Actor* getTarget ();

};