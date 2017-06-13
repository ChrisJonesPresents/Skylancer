#include "Crystal.h"



Crystal::Crystal (scene::IMeshSceneNode *node, core::vector3df position, Stagehand *p_stagehand)
	{
	m_size=6;
	m_alive=true;
	m_id=powerup;
	m_pnode=node;
	m_position=position;
	m_pstagehand=p_stagehand;
	m_lifespan=300;
	m_velocity=core::vector3df(0,0,1);
	m_health=1;
	}

void Crystal::update()
	{

	m_lifespan--;

	m_position += m_velocity;
	m_pnode->setPosition(m_position);

	if (m_lifespan<1)
	{
	m_alive=false;
	}



	if (m_alive==false)
	{
	m_pstagehand->Remove(this);
	}

	}