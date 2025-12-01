#include "Cube.h"

Cube::Cube(double xp, double yp, double zp, double size, Color c) : Object(xp, yp, zp, size, c) {};

void Cube::make()
{
    glPushMatrix();
    glTranslatef(this->xp, this->yp, this->zp);
    glColor3f(this->color.r, this->color.g, this->color.b);
    glutSolidCube(this->size);
    glPopMatrix();
}