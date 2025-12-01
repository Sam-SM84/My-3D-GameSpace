#pragma once

#ifndef CUBE_H
#define CUBE_H

#include "Color.h"
#include "Object.h"
#include <GL/glut.h>
#include <functional>

class Cube : public Object
{
public:

    Cube(double xp, double yp, double zp, double size, Color c);
    void make();
};

#endif

