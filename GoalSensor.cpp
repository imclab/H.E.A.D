/*
 * GoalSensor.cpp
 *
 *  Created on: Apr 29, 2010
 *      Author: bgouveia
 */

#include "GoalSensor.h"
#include "ScreenManager.h"
#include "Level.h"
#include <stdio.h>

//#define DEBUG

GoalSensor::GoalSensor() {
	sm = ScreenManager::getInstance();
	type = O_INVALID;
	bodyshape=0;
	body=0;
	pX=0;
	pY=0;
}

GoalSensor::GoalSensor(float x,float y){
	type = O_GOALSENSOR;

	pX=x;
	pY=y;

	sm = ScreenManager::getInstance();

	/**********codigo Box2D***************/
	//define a posição
	bodydef.position.Set(x,y);

	//cria o corpo usando as definições
	body=NULL;
	b2World * world = ((Level*)sm->getCurrentScreen())->getWorld();
	body = world->CreateBody(&bodydef);

	b2Vec2 vect[4];

	vect[3]=b2Vec2(-1.129f,1.369f);	
	vect[2]=b2Vec2(1.129f,	1.369f);	
	vect[0]=b2Vec2(-0.858f,	0.217f);	
	vect[1]=b2Vec2(0.858f,	0.217f);	

	b2PolygonShape shape;

	shape.Set(vect,4);
	
	b2FixtureDef fd;
	fd.isSensor=true;
	fd.shape = &shape;

	body->CreateFixture(&fd);

	
	//usa o userdata para guardar um ponteiro no objecto body do Box2D (usado nas colisões)
	body->SetUserData(this);
	/**************************************/


	/***********codigo CLanlib***************/
	//criar a sprite
	sprite = sm->getSprite("goalsensor");
	sprite->set_linear_filter(true);
}

GoalSensor::~GoalSensor() {
	if(bodyshape)
		delete bodyshape;
	bodyshape=0;

	if(body)
		body->GetWorld()->DestroyBody(body);
	body=0;
}

///desenha o bloco
void GoalSensor::draw(){
	
	#ifdef DEBUG
		sm->drawSprite(sprite,pX,pY);
	#endif
}

///vai buscar os dados da simulação box2d e actualiza as corrdenadas
void GoalSensor::handleevents(){

	//por enquanto so para teste (colisões clanlib)
	float screenratio=sm->getScreenRatio();

	pX=body->GetPosition().x;
	pY=body->GetPosition().y+0.217f;
	angle = body->GetAngle();

	float scalex = screenratio*2.258f /((float)sprite->get_width());
	float scaley = screenratio*1.152f /((float)sprite->get_height());

	sprite->set_angle(CL_Angle::from_radians(-angle));
	sprite->set_scale(scalex,scaley);

}
