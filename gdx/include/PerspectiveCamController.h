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

#include "GdxDefines.h"
#include "InputAdapter.h"
#include "PerspectiveCamera.h"
#include "Vector2.h"

class GdxDllImportExport PerspectiveCamController : public InputAdapter 
{
public:
  enum TransformMode 
  {
		Rotate, 
    Translate, 
    Zoom, 
    None
	};

  PerspectiveCamera cam;
  Vector3 lookAt;
	TransformMode mode;
	bool translated;

  Vector2 tCurr;
	Vector2 last;
	Vector2 delta;
	Vector2 currWindow;
	Vector2 lastWindow;
	Vector3 curr3;
	Vector3 delta3;
	Plane lookAtPlane;
	Matrix4 rotMatrix;
	Vector3 xAxis;
	Vector3 yAxis;
	Vector3 point;

public:
	PerspectiveCamController( const PerspectiveCamera& cam);
  
	virtual bool touchDown (int x, int y, int pointer, int button);
  
  virtual bool touchUp (int x, int y, int pointer, int button);

  virtual bool touchDragged (int x, int y, int pointer);
  
	virtual bool scrolled (int amount);
  
};