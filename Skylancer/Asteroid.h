#include "Actor.h"
#include "Stagehand.h"
using namespace irr;

#ifndef ASTEROID
#define ASTEROID

class Asteroid : public Actor
{

protected:
	Stagehand *m_pstagehand;
	int m_lifespan;
	bool m_crystal;
	bool m_immortal;
public:

	Asteroid(){};

	Asteroid(Stagehand* stagehand, core::vector3df position, scene::ISceneNode *node, bool megaroid=false, bool crystal=false, bool immortal=false);
	
	void update();






};

#endif