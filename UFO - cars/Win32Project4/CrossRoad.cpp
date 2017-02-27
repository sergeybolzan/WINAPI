#include "stdafx.h"
#include "CrossRoad.h"
using namespace Gdiplus;


CrossRoad::CrossRoad(int x, int y){
	this->x = x;
	this->y = y;
}

void CrossRoad::draw(Graphics &grp){
	Pen  pen(Color(255, 255, 255, 255),5);
	grp.DrawEllipse(&pen, x, y, 20, 20);
}


int CrossRoad::getX(){
	return x;
}

int CrossRoad::getY(){
	return y;
}


void CrossRoad::addRoad(Road* road){
	roads.push_back(road);
}


Vector<Road*> CrossRoad::getAllRoads(){
	return roads;
}