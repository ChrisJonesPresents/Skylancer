#include "Chunk.h"


Chunk::Chunk (core::vector3df position,core::vector3df velocity, scene::ISceneNode *node,Stagehand *stagehand)
{
m_pnode=node;
m_pstagehand=stagehand;
m_velocity=velocity;
m_position=position;
m_health=60;
m_size=1;
m_id=other;
m_alive=true;

m_velocity+=m_pstagehand->randomvector()*0.5;


}

void Chunk::update()
{

	m_position.operator += (m_velocity);

	m_pnode->setPosition(m_position);
	m_health--;


	if (m_health<0)
	{

	m_alive=false;
	}

if (!m_alive)
{
	m_pstagehand->Remove(this);
}
}