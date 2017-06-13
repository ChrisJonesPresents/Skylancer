#include <irrlicht.h>
#include "Actor.h"
#include "Stagehand.h"


using namespace irr;
#ifndef LASER
#define LASER

class Laser : public Actor
{

protected:

	int m_lifespan;
	
	Stagehand *m_pstagehand;



public:

	Laser (core::vector3df position, core::vector3df rotation, scene::ISceneNode *node, Stagehand *pstagehand);

	void update();



};


#endif