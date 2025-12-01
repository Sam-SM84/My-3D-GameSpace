#pragma once

#ifndef TEAPOT_H
#define TEAPOT_H

#include "Color.h"
#include "Object.h"
#include <GL/glut.h>
#include <functional>
class Teapot : public Object
{
public:

    Teapot(double xp, double yp, double zp, double size, Color c);
    void make();
};

#endif

