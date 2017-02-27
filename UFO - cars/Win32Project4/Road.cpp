#include "stdafx.h"
#include "Road.h"
#include "Car.h"
#include <iostream>

using namespace Gdiplus;

Road::Road(CrossRoad *from, CrossRoad *to){
	this->from = from;
	this->to = to;
	from->addRoad(this);
	to->addRoad(this);
	
}

void Road::draw(Graphics &grp){
	Pen      pen(Color(255, 255, 255, 255),3);
	grp.DrawLine(&pen, from->getX()+10, from->getY()+10, to->getX()+10, to->getY()+10);
}


CrossRoad* Road::getFrom(){
	return from;
}

CrossRoad* Road::getTo(){
	return to;
}
void Road::addCar(Car* car){
	cars.push_back(car);
}
void Road::go(){
	//double Power = -1 * ((cars.getSize() / NNom) - 1);
	//int v = VeNom* pow(2, Power);
	int v = 2;
	switch (cars.getSize())
	{
	case 1: v = 60; break;
	case 2: v = 20; break;
	case 3: v = 15; break;
	case 4: v = 10; break;
	case 5: v = 5; break;
	}
	
	for (int i = 0; i < cars.getSize(); i++){
		cars[i]->go(v);
	}
}


void Road::deleteCar(Car* car){
	cars.remove(car);
}



Vector<Car*>* Road::getAllCars(){
	return &cars;
}