#pragma once

#include <ClanLib/display.h>
#include <Box2D/Box2D.h>

enum EObjectType
{
	O_BLOCK,
	O_BALL,
	O_PIT,
	O_RAMP,
	O_INVALID
};

class PhysicalObject
{
public:
	PhysicalObject(void);
	virtual ~PhysicalObject(void);
protected:
	EObjectType type;
	CL_Sprite sprite;
	CL_CollisionOutline coutline;
	b2Body * body;
	b2BodyDef bodydef;
	b2Shape * bodyshape;
	b2FixtureDef fixturedef;
public:
	virtual void draw();
	virtual void handleevents();
	EObjectType getType();
};