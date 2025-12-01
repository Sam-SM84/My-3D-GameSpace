#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "Color.h"
#include "Object.h"
#include <GL/glut.h>
#include <functional>
class Sphere : public Object
{
public:

    Sphere(double xp, double yp, double zp, double size, Color c);
    void make();
};

#endif

