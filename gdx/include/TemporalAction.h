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
#include "Action.h"
class Actor;

/** A {@link TemporalAction} controls an {@link Action} by repeating, delaying etc. the effect of an {@link Action}.
 * 
 * @author Moritz Post <moritzpost@gmail.com> */
class GdxDllImportExport TemporalAction : public Action 
{
protected:
	Action* action;
	Actor* target;

public:
  TemporalAction();
  virtual ~TemporalAction();

	/** Gets the {@link Action} that is controlled by this {@link TemporalAction}.
	 * 
	 * @return the {@link Action} under control */
	Action* getAction();
};
