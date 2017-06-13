#include <irrlicht.h>
#include "Actor.h"
#include "Stagehand.h"
using namespace irr;

#ifndef LIVING_ASTEROID
#define LIVING_ASTEROID

class Living_Asteroid : public Actor
{

protected:
	Stagehand *m_pstagehand;
	int m_lifespan;
	float m_aggression;
	int m_stun;
Actor *m_ptarget;

public:

		Living_Asteroid(Stagehand* stagehand, core::vector3df position, scene::ISceneNode *node,  Actor *ptarget=NULL,float aggression=0.1F);
	

		void update();



};

#endif