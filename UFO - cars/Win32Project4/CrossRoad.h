#pragma once
#include "DrawObject.h"
#include "Vector.h"
#include "Road.h"
class DrawObject;
class Road;

class CrossRoad :public DrawObject {
	int x;
	int y;
	Vector<Road*> roads;
public:
	CrossRoad(int x, int y);
	void draw(Graphics &grp);
	int getX();
	int getY();
	void addRoad(Road* road);  
	Vector<Road*> getAllRoads();
};