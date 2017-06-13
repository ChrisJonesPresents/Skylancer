#include "Actor.h"
#include "Stagehand.h"
#include <irrlicht.h>

using namespace irr;

#ifndef CRYSTAL
#define CRYSTAL

class Crystal : public Actor
{

protected:
Stagehand *m_pstagehand;
int m_lifespan;


public:

	Crystal (scene::IMeshSceneNode *node, core::vector3df position, Stagehand *p_stagehand);

void	update();

};

#endif 