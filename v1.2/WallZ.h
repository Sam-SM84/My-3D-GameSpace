#pragma once

#ifndef WALLZ_H
#define WALLZ_H

#include "Color.h"
#include <GL/glut.h>
#include<functional>

class WallZ 
{
public:
    double startingZ, endingZ, startingX, height;
    Color color;
    WallZ(double sz, double ez, double sx, double h, Color c);
    void make();
    std::function<void()>moveObject;
};

#endif

#pragma once
