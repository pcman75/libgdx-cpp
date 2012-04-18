//
//  main.m
//  superjumper
//
//  Created by Cosmin Manoliu on 4/5/12.
//  Copyright (c) 2012 Home. All rights reserved.
//
#include "stdafx.h"

#include "GlfwApplication.h"
#include "SuperJumper.h"

int main(int argc, char *argv[])
{
    SuperJumper superJumper;
    GlfwApplication(superJumper, "Super Jumper", 320, 480, true);
}
