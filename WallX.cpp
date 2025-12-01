#include "WallX.h"

WallX::WallX(double sx, double ex, double sz, double h, Color c)
{
    this->startingX = sx;
    this->endingX = ex;
    this->startingZ = sz;
    this->height = h;
    this->color = c;
}

void WallX::make()
{
    for (int i = 0; i < this->endingX - this->startingX; i++)
    {
        for (int j = 0; j < this->height; j++)
        {
            glPushMatrix();
            glTranslatef(this->startingX + i, j, this->startingZ);
            glColor3f(this->color.r, this->color.g, this->color.b);
            glutSolidCube(1);
            glPopMatrix();
        }
    }
}