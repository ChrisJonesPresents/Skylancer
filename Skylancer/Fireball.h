#include "Actor.h"
#include "Stagehand.h"
#include <irrlicht.h>

using namespace irr;

#ifndef FIREBALL
#define FIREBALL

class Fireball : public Actor

{
 
protected:
	int m_lifespan;
	Stagehand *m_pstagehand;

public:



	Fireball (scene::ISceneNode *node, core::vector3df position, core::vector3df velocity, Stagehand* p_stagehand);

	void update();




};

#endif