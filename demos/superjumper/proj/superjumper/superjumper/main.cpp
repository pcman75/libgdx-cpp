//
//  main.m
//  superjumper
//
//  Created by Cosmin Manoliu on 4/5/12.
//  Copyright (c) 2012 Home. All rights reserved.
//
#include "stdafx.h"

#ifdef TARGET_IOS
#include "IOSApplication.h"
#else
#include "GlfwApplication.h"
#endif
#include "SuperJumper.h"

int main(int argc, char *argv[])
{
    SuperJumper superJumper;
#ifdef TARGET_IOS
    IOSApplication(superJumper, true, argc, argv);
#else
    GlfwApplication(superJumper, "Super Jumper", 320, 480, true);
#endif
}
