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
#include "Stage.h"
#include "Group.h"



class GroupTest : public GdxTest 
{
public:
  GDX_DEFINE_CREATOR(GroupTest);

	Stage* stage;

  GroupTest::GroupTest()
  {
    stage = NULL;
  }

  virtual GroupTest::~GroupTest()
  {
    if( NULL != stage)
    {
      delete stage;
      stage = NULL;
    }
  }

	virtual void create() 
  {
    stage = new Stage(0, 0, false);
		Gdx.input->setInputProcessor( stage);
		
		Group::enableDebugging("data/group-debug.png");

		Group* group1 = new Group("group1");
		group1->rotation = 30;
		group1->transform = true;
		group1->x = 50;
		group1->y = 50;
		group1->width = 150;
		group1->height = 150;
		stage->addActor(group1);

		Group* group2 = new Group("group2");
		group2->transform = false;
		group2->x = 50;
		group2->y = 50;
		group2->width = 50;
		group2->height = 50;
		group1->addActor(group2);

		Group* group3 = new Group("group3");
		group3->transform = true;
		group3->originX = 100;
		group3->rotation = 45;
		group3->x = 10;
		group3->y = 10;
		group3->width = 35;
		group3->height = 35;
		group2->addActor(group3);

		Group* group4 = new Group("group4");
		group4->transform = false;
		group4->x = 5;
		group4->y = 5;
		group4->width = 25;
		group4->height = 25;
		group3->addActor(group4);
	}

	void render () 
  {
    Gdx.graphics->getGL10()->glClearColor(0, 0, 0, 1);
		Gdx.graphics->getGL10()->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);
		stage->draw();
	}

	void resize (int width, int height) 
  {
    if( stage)
		  stage->setViewport(width, height, false);
	}

	bool needsGL20 () 
  {
		return false;
	}
};