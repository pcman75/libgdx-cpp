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
#include "AnimationAction.h"
class Actor;

class GdxDllImportExport FadeOut : public AnimationAction 
{
protected: 
  float startAlpha;
	float deltaAlpha;

public:
	FadeOut(float duration);
  virtual ~FadeOut();

	virtual void setTarget( Actor* actor);
  
	virtual void act( float delta);
  
	virtual void finish();
  
	virtual Action* copy();
  
};
