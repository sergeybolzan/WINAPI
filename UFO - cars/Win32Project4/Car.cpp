#include "stdafx.h"
#include "Car.h"
#include <iostream>
using namespace Gdiplus;

Car::Car(Road* road, Color c){
	this->road = road;
	this->from = road->getFrom();
	this->to = road->getTo();
	x = from->getX();
	y = from->getY();
	this->c = c;
	road->addCar(this);
}

void Car::draw(Graphics &grp){
	Point Pt[3];
	Pt[0].X = x + 10;
	Pt[0].Y = y;
	Pt[1].X = x + 20;
	Pt[1].Y = y + 20;
	Pt[2].X = x;
	Pt[2].Y = y + 20;
	Pen  pen(c, 6);
	grp.DrawPolygon(&pen, Pt, 3);
}
void Car::setDirection(Road* road, CrossRoad* from, CrossRoad* to){
	this->road = road;
	road->addCar(this);
	this->from = from;
	this->to = to;
}
void Car::go(int speed){
	int tempSpeed = speed;
	if (abs(x - to->getX()) % tempSpeed != 0 && abs(x - to->getX()) < tempSpeed){
		tempSpeed = abs(x - to->getX());
	}
	if (abs(y - to->getY()) % tempSpeed != 0 && abs(y - to->getY()) < tempSpeed){
		tempSpeed = abs(y - to->getY());
	}
	if (y < to->getY()){
		y += tempSpeed;
	}
	else if (y > to->getY()){
		y -= tempSpeed;
	}

	if (x < to->getX()){
		x += tempSpeed;
	}
	else if (x > to->getX()){
 		x -= tempSpeed;
	}
	tempSpeed = speed;
	if (x == to->getX() && y == to->getY()){
		//Если машина приехал в конец дороги
		//1)Удалиться из первой дороги
		//2)И задать новую
		Vector<Road*> roads = to->getAllRoads();
		CrossRoad *nextCrossRoad;
		Road* next;
		do{
			next = roads[rand() % roads.getSize()];
			//Случайная дорога
			//У дороги есть два конца
			CrossRoad *cr1 = next->getFrom();
			CrossRoad *cr2 = next->getTo();
			if (to == cr1)
				nextCrossRoad = cr2;
			else
				nextCrossRoad = cr1;
		} while (nextCrossRoad == from && roads.getSize() > 1);
		from = to;
		to = nextCrossRoad;
		road->deleteCar(this);
		road = next;
		road->addCar(this);

	}
	
	//как только доехала до конечного перекрестка
	//пусть едет обратно
	//меняете у машинки to<->from
	//пусть едет обратно
}


int Car::getX(){
	return x;
}


int Car::getY(){
	return y;
}


