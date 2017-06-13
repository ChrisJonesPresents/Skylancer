#include "Actor.h"
#include "Stagehand.h"


#ifndef TORPEDO
#define TORPEDO

class Torpedo : public Actor
{
protected:

	Stagehand *m_stagehand;
	int m_lifespan;
	bool m_bturbo;
public:

	Torpedo (Stagehand *stagehand, core::vector3df position, core::vector3df rotation, scene::ISceneNode *node, bool turbo);


	void update();


};


#endif