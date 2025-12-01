#include "Color.h"
#include "Position.h"
#include "Object.h"
#include<GL/glut.h>


Object::Object(double xp, double yp, double zp, double size, Color c)
{
      this->xp = xp;
      this->yp = yp;
      this->zp = zp;
      this->size = size;
      this->color = c;
}

Position Object::getDim()
{
    double xn = this->xp - (this->size / 2.0);
    double xm = this->xp + (this->size / 2.0);
    double yn = this->yp - (this->size / 2.0);
    double ym = this->yp + (this->size / 2.0);
    double zn = this->zp - (this->size / 2.0);
    double zm = this->zp + (this->size / 2.0);
    return Position(xn, xm, yn, ym, zn, zm);

}

void Object::makeWireCube()
{
    glPushMatrix();
    glTranslatef(this->xp, this->yp, this->zp);
    glutWireCube(this->size + 1);
    glColor3f(0, 0, 0);
    glLineWidth(10);
    glPopMatrix();
}

