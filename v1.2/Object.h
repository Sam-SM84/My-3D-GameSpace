#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include "Color.h"
#include "Position.h"
#include <functional>

class Object {
public:
    double xp, yp, zp, size;
    Color color;

    Object(double xp, double yp, double zp, double size, Color c);
    Position getDim();
    void makeWireCube();
    std::function<void()>moveObject;
};

#endif
