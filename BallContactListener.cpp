#include "BallContactListener.h"
#include "PhysicalObject.h"
#include "ScreenManager.h"
#include "Ball.h"
#include <stdio.h>

//quando 2 objectos colidem pela primeira vez
void BallContactListener::BeginContact(b2Contact* contact){
	printf("touch\n");
	const b2Body* bodyA = contact->GetFixtureA()->GetBody();
    const b2Body* bodyB = contact->GetFixtureB()->GetBody();
	b2Vec2 posA = bodyA->GetPosition();
	b2Vec2 posB = bodyB->GetPosition();

	printf("PosA x:%f y:%f\n",posA.x,posA.y);
	printf("PosB x:%f y:%f\n",posB.x,posB.y);


	//vou obter o objecto a partir da userdata
	PhysicalObject * objA = (PhysicalObject *) bodyA->GetUserData();
	PhysicalObject * objB = (PhysicalObject *) bodyB->GetUserData();

	printf("obj A type: %d\n",objA->getType());
	printf("obj B type: %d\n",objB->getType());
	
	if (objA->getType() == O_BALL){
		((Ball *)objA)->playsound();
	}else{
		((Ball *)objB)->playsound();
	}

	// no caso  de ganhar
	if (objA->getType()==O_BALL && objB->getType()== O_GOALSENSOR || objA->getType()==O_GOALSENSOR && objB->getType()== O_BALL )
		ScreenManager::getInstance()->setScreenType(S_WIN);

	//no caso de tocar num pit
	if (objA->getType()==O_BALL && objB->getType()== O_PIT || objA->getType()==O_PIT && objB->getType()== O_BALL )
		ScreenManager::getInstance()->setScreenType(S_OVER);

}

/// Called when two fixtures cease to touch.
void BallContactListener::EndContact(b2Contact* contact){
	printf("...and go\n");
}

void BallContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void BallContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}
