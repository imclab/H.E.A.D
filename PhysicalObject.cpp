#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(void)
{
}

PhysicalObject::~PhysicalObject(void)
{
}

void PhysicalObject::handleevents(){
}

void PhysicalObject::draw(){
}

EObjectType  PhysicalObject::getType(){
	return type;
}

void PhysicalObject::setPosition(float x , float y){
	pX=x;
	pY=y;
}