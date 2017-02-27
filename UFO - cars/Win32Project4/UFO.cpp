#include "stdafx.h"
#include "UFO.h"
UFO::UFO(int x, int y){
	this->x = x;
	this->y = y; }
int UFO::getX(){ return x; }
int UFO::getY(){ return y; }
void UFO::setX(int x){ this->x = x; }
void UFO::setY(int y){ this->y = y; }
void UFO::draw(Graphics &gpr){
	Pen pen(Color(255, (x+y)% 256, x % 256, y % 256), 10);
	gpr.DrawEllipse(&pen, x-15, y - 15, 30, 30);
}