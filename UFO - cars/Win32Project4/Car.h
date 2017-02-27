#pragma once
#include "DrawObject.h"
#include "CrossRoad.h"
#include "Road.h"
class DrawObject;
class CrossRoad;
class Road;

class Car : public DrawObject{
	Road *road;
	CrossRoad *from;
	CrossRoad *to;
	int x;
	int y;
	Color c;
public:
	Car(Road* road, Color c);
	void draw(Graphics &grp);
	void go(int speed);
	void setDirection(Road* road,CrossRoad* from, CrossRoad* to);
	int getX();
	int getY();
};