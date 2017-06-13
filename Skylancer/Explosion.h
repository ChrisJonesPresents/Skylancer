#include "Actor.h"
#include <irrlicht.h>
#include "Stagehand.H"
using namespace irr;

#ifndef EXPLOSION
#define EXPLOSION

class Explosion : public Actor
{

protected:

	int m_lifespan;
	Stagehand* m_stagehand;

public:

	Explosion(Stagehand* stagehand, scene::ISceneNode *node,core::vector3df position);

	void update();



};

#endif