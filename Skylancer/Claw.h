#include <irrlicht.h>
#include "Actor.h"
#include "Stagehand.h"
using namespace irr;

#ifndef CLAW
#define CLAW

enum clawstatus {awakening,cbase, readying,striking,returning};
class Claw : public Actor
{

protected:

Stagehand *m_pstagehand;
core::vector3df m_positionmemory;
core::vector3df m_rotation;
clawstatus m_state;
bool m_isrighty;
float m_clock;


public:

	Claw (scene::IMeshSceneNode *node, core::vector3df position, Stagehand *stagehand, bool righty);

	void update();

	void clawattack();



};

#endif