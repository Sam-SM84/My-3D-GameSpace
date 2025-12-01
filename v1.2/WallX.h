#pragma once

#ifndef WALLX_H
#define WALLX_H

#include "Color.h"
#include <GL/glut.h>
#include<functional>

class WallX
{
public:
    double startingX, startingZ, endingX, height;
    Color color;
    WallX(double sx, double ex, double sz, double h, Color c);
    void make();
    std::function<void()>moveObject;
};

#endif

