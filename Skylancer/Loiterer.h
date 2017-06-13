#include <irrlicht.h>
#include "Actor.h"
#include "Stagehand.h"

using namespace irr;

#ifndef LOITERER
#define LOITERER

class Loiterer : public Actor
{

protected:

Stagehand *m_pstagehand;
core::vector3df m_destination;
int m_lifespan;
float m_timetodestination;
float m_spin, m_spin_increment;
int m_guncooldown;
int m_aggression;
int m_shotsfired;
public:

	Loiterer (Stagehand *pstagehand, scene::ISceneNode *node,core::vector3df position, int aggression=1);

void update();



};

#endif