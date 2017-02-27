﻿//Специальный абстрактный класс
//который будет отвечать за отрисовку объектов

//Все объекты которые мы будем рисовать
//будем наследовать от этого класса
#pragma once
#include "Headers.h"
class DrawObject{
public:
	virtual void draw(Graphics &grp) = 0;
};


//все наследники ОБЯЗАНЫ иметь такой мето

