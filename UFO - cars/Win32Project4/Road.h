#pragma once
#include "Vector.h"
#include "DrawObject.h"
#include "CrossRoad.h"
#include "Car.h"

class DrawObject;
class CrossRoad;
class Car;

class Road : public DrawObject{
	CrossRoad *from;
	CrossRoad *to;
	Vector<Car*> cars;
	int VeNom=20;
	double NNom = 2;
public:
	Road(CrossRoad *from, CrossRoad *to);
	void draw(Graphics &grp);
	CrossRoad* getFrom();
	CrossRoad* getTo();
	void addCar(Car* car);
	void deleteCar(Car* car);
	void go();
	Vector<Car*>* getAllCars();
};