#include "Pit.h"
#include "ScreenManager.h"
#include "Level.h"
#include <stdio.h>

#define DEBUG 1

Pit::Pit(void)
{
	sm = ScreenManager::getInstance();
	type = O_INVALID;
	bodyshape=0;
	body=0;
	pX=0;
	pY=0;
	hsizeX=-1;
	hsizeY=-1;
}

Pit::Pit(float hsizex,float hsizey,float x, float y){
	type = O_PIT;

	pX=x;
	pY=y;
	hsizeX=hsizex;
	hsizeY=hsizey;

	sm = ScreenManager::getInstance();

	/**********codigo Box2D***************/
	//define a posição
	bodydef.position.Set(x,y);

	//cria a forma
	bodyshape=new b2PolygonShape();
	((b2PolygonShape*)bodyshape)->SetAsBox(hsizeX,hsizeY);

	//cria o corpo usando as definições
	body=NULL;
	b2World * world = ((Level*)sm->getCurrentScreen())->getWorld();
	body = world->CreateBody(&bodydef);

	b2FixtureDef fd;
	fd.isSensor=true;
	fd.shape = bodyshape;

	body->CreateFixture(&fd);

	//usa o userdata para guardar um ponteiro no objecto body do Box2D (usado nas colis�es)
	body->SetUserData(this);
	/**************************************/


}

Pit::~Pit(void)
{
	if(bodyshape)
		delete bodyshape;
	bodyshape=0;

	if(body)
		body->GetWorld()->DestroyBody(body);
	body=0;
}

///desenha o bloco
void Pit::draw(){

#ifdef DEBUG
	CL_Rectf ground(CL_Sizef(hsizeX*2,hsizeY*2));

	//centrar o rectangulo
	ground.translate(-ground.get_center().x,-ground.get_center().y);
	CL_Colorf color(0.639f,0.216f,0.135f);
	sm->drawBox(ground.left+pX,ground.bottom+pY,ground.right+pX,ground.top+pY,color);
#endif

}

///vai buscar os dados da simulação box2d e actualiza as corrdenadas
void Pit::handleevents(){

	/*
	pX=body->GetPosition().x;
	pY=body->GetPosition().y;
	angle = body->GetAngle();

	//por enquanto so para teste (colises clanlib)
	float screenratio=sm->getScreenRatio();

	float scalex = screenratio*hsizeX /((float)coutline.get_width());
	float scaley = screenratio*hsizeY /((float)coutline.get_height());
	coutline.set_scale(scalex*2,scaley*2);
	*/
}