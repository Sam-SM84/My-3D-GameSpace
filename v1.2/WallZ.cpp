#include "WallZ.h"

WallZ::WallZ(double sz, double ez, double sx, double h, Color c)
{
    this->startingZ = sz;
    this->endingZ = ez;
    this->startingX = sx;
    this->height = h;
    this->color = c;
}

void WallZ::make()
{
    for (int i = 0; i < this->endingZ - this->startingZ; i++)
    {
        for (int j = 0; j < this->height; j++)
        {
            glPushMatrix();
            glTranslatef(this->startingX, j, this->startingZ + i);
            glColor3f(this->color.r, this->color.g, this->color.b);
            glutSolidCube(1);
            glPopMatrix();
        }
    }
}