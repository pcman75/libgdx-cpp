//
//  Renderer.h
//  gdx
//
//  Created by Tamas Jano on 02/04/2012.
//  Copyright (c) 2012 Home. All rights reserved.
//

#ifndef gdx_Renderer_h
#define gdx_Renderer_h

class Renderer{
public:
    virtual void initialize(int width, int height) = 0;
    virtual void render() const = 0;
    virtual ~Renderer() {}
};

class Renderer* createGL2Renderer();

#endif
