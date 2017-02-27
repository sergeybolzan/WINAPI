#pragma once
#include "DrawObject.h"


class UFO : public DrawObject{
	int x;
	int y;
public:
	UFO(int x,int y);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	void draw(Graphics &grp);
};