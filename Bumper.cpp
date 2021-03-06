#include "Bumper.h"
#include "ScreenManager.h"
#include "Level.h"


Bumper::Bumper(void)
{
	sm = ScreenManager::getInstance();
	type = O_INVALID;
	bodyshape=0;
	body=0;
	pX=0;
	pY=0;
}

Bumper::Bumper(float x, float y){
	type = O_BUMPER;

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
	
	vect[0]=b2Vec2(0.0f,0.0f);	
	vect[1]=b2Vec2(2.0f,0.0f);	
	vect[2]=b2Vec2(2.0f,5.0f);	
	vect[3]=b2Vec2(0.0f,5.0f);		

	b2PolygonShape shape;

	shape.Set(vect,4);

	b2FixtureDef fd;
	fd.density = 1.0f;
	fd.friction = 0.3f;
	fd.restitution = 1.5f;
	fd.shape=&shape;

	body->CreateFixture(&fd);

	//usa o userdata para guardar um ponteiro no objecto body do Box2D (usado nas colis�es)
	body->SetUserData(this);
	/**************************************/


	/***********codigo CLanlib***************/
	//criar a sprite
	sprite = sm->getSprite("bumper");
	sprite->set_linear_filter(true);

}

Bumper::~Bumper(void)
{
	if(bodyshape)
		delete bodyshape;
	bodyshape=0;

	if(body)
		body->GetWorld()->DestroyBody(body);
	body=0;
	
	if(sprite)
		delete sprite;
	sprite=0;

}


void Bumper::handleevents()
{

	pX=body->GetPosition().x;
	pY=body->GetPosition().y;


	float screenratio=sm->getScreenRatio();


	//dados do poligono
	
	//2 largura no ficheiro c4d
	//5 altura no ficheiro c4d
	
	float scalex = screenratio*2.0f /((float)sprite->get_width());
	float scaley = screenratio*5.0f /((float)sprite->get_height());

	sprite->set_scale(scalex,scaley);
}

void Bumper::draw()
{
	sm->drawSprite(sprite,pX,pY);
}
