#include "Asteroid.h"
#include <stdlib.h>


Asteroid::Asteroid ( Stagehand* stagehand, core::vector3df position, scene::ISceneNode *node, bool megaroid, bool crystal, bool immortal)
{
m_lifespan=360;
m_pstagehand=stagehand;
m_pnode=node;
m_size=5.5;
if (megaroid)
	m_size=8.5;
m_alive=true;
m_health=3;
m_velocity=core::vector3df(0,0,1);
m_velocity.X=-0.05+((rand()% 100)*0.001);
m_velocity.Y=-0.05+((rand()% 100)*0.001);
m_position=position;
m_id=enemy;
m_crystal=crystal;
m_immortal=immortal;


}
	
void Asteroid::update()
{
m_lifespan--;
m_position.operator += (m_velocity);
m_pnode->setPosition(m_position);



if (m_size!=-1)
{
Actor* collider=m_pstagehand->Collisioncheck(this);

if (collider!=NULL)
{
if (collider->getID()==enemy && !m_crystal)
{

	core::vector3df nudge=m_position-collider->getPosition();
	nudge.normalize();
	nudge=nudge*0.1;
//	nudge.operator * (2);
	m_velocity= nudge;
	m_velocity.Z=1;
	//m_position.operator +=(nudge);

}
if (collider->getID()==projectile || collider->getID()==enemy_projectile)
{
	if (!m_immortal)
	{
	m_health-=collider->getHealth();
	m_pstagehand->createexplosion(collider->getPosition());
	}
	else
	{
		m_pstagehand->createexplosion(collider->getPosition(),3);
	}
	m_pstagehand->Remove(collider);
}
}
}

if (m_lifespan<0)
{
m_alive=false;

}
if (m_health<1)
{
	if (m_crystal)
	{
		m_pstagehand->createcrystal(m_position);
	}
	m_pstagehand->createchunk(m_position,m_velocity,false);
	m_pstagehand->createchunk(m_position,m_velocity,false);
	m_pstagehand->createchunk(m_position,m_velocity,false);
	m_alive=false;
}





if (!m_alive)
{
	m_pstagehand->Remove(this);
}

}