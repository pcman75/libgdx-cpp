//
//  RendererTest.cpp
//  gdx
//
//  Created by Tamas Jano on 02/04/2012.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "GdxTest.h"
#include "Renderer.h"

class RendererTest : public GdxTest
{
    Renderer* renderer;
public:
    void create () 
	{
        renderer = createGL2Renderer();
    };
    
    void render()
    {
        renderer->render();
    }
};