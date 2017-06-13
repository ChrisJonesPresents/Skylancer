#include "Explosion.h"



Explosion::Explosion(Stagehand* stagehand, scene::ISceneNode *node,core::vector3df position)
{

m_pnode=node;
m_position=position;
m_stagehand=stagehand;
m_lifespan=25;
m_size=-1;
m_pnode->setPosition(position);
}

void Explosion::update()
	{

	m_lifespan--;

	if (m_lifespan<1)
	{
		m_stagehand->Remove(this);
	}

	}
