//
//  Shader.fsh
//  gdx-tests-ios
//
//  Created by Cosmin Manoliu on 4/17/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
