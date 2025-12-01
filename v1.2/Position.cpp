#include "Position.h"

Position::Position(double x1, double x2, double y1, double y2, double z1, double z2)
{
	this->Xmin = x1;
	this->Xmax = x2;
	this->Ymin = y1;
	this->Ymax = y2;
	this->Zmin = z1;
	this->Zmax = x2;
}
