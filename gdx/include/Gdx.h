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

#include "Application.h"
#include "Graphics.h"
#include "Audio.h"
#include "Input.h"
#include "Files.h"

/** <p>
* Environment class holding references to the {@link Application}, {@link Graphics}, {@link Audio}, {@link Files} and
* {@link Input} instances. The references are held in public  fields. Do not mess with this! This essentially allows you
*  access to all sub systems. It is your responsiblity to keep things thread safe. Don't use Graphics in a thread that is
* not the rendering thread or things will go crazy. Really.
* </p>
* 
* <p>
* There's also references to {@link GLCommon}, {@link GL10}, {@link GL11}, {@link GL20} and {@link GLU}. The same rules as above
* apply. Don't mess with this or things will break!
* </p>
* 
* <p>
* This is kind of messy but better than throwing around Graphics and similar instances. I'm aware of the design faux pas.
* </p>
* 
* */

enum GLversion
{
    GL_VERSION_0,
    GL_VERSION_10,
    GL_VERSION_11,
    GL_VERSION_20
};

class GdxClass 
{
public:
	//TODO: store pointer and make accesor returning reference 
	Application* app;
	Graphics* graphics;
	Audio* audio;
	Input* input;
	Files* files;
	Threading* threading;

    GLversion glVersion;

	public:
        static GdxClass& getInstance()
        {
            static GdxClass    instance;
            return instance;
        }
		bool isGL20Available();
		bool isGL11Available();
        bool isGLInitialised();
        GLversion getGLVersion();
		~GdxClass();
    private:
        GdxClass();
		
        //GdxClass(const GdxClass&);
        //void operator=(const GdxClass&);
};

extern GdxClass Gdx;
