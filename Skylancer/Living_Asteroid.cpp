#include "Living_Asteroid.h"


Living_Asteroid::Living_Asteroid(Stagehand* stagehand, core::vector3df position, scene::ISceneNode *node, Actor *ptarget,float aggression)
{

//	Asteroid::Asteroid(stagehand,position,node,false,false);
	m_pnode=node;
	m_velocity=core::vector3df(0,0,1+((rand()%5)/10));
	m_ptarget=ptarget;
	m_position=position;
	m_lifespan=250;
	m_health=3;
	m_size=5;
	m_alive=true;
	m_pstagehand=stagehand;
	m_id=enemy;
	m_stun=0;
	m_pnode->setRotation(core::vector3df(90,0,0));
	m_aggression=aggression;
}
	

void Living_Asteroid::update()
{
	if (m_stun>0)
	{
	m_stun--;
	}
	if (m_ptarget!=NULL && m_stun==0 && m_lifespan>25)
	{
		if (m_position.X>m_ptarget->getPosition().X+1)
			m_velocity.X=m_aggression*-1;
		if (m_position.X<m_ptarget->getPosition().X-1)
			m_velocity.X=m_aggression;
		if (m_position.Y>m_ptarget->getPosition().Y+1)
			m_velocity.Y=m_aggression*-1;
		if (m_position.Y<m_ptarget->getPosition().Y-1)
			m_velocity.Y=m_aggression;		

		if (m_position.X<m_ptarget->getPosition().X+1 && m_position.X>m_ptarget->getPosition().X-1)
			m_velocity.X=0;
		if (m_position.Y<m_ptarget->getPosition().Y+1 && m_position.Y>m_ptarget->getPosition().Y-1)
			m_velocity.Y=0;		

	}
	m_lifespan--;
	m_position.operator += (m_velocity);

	m_pnode->setPosition(m_position);



Actor* collider=m_pstagehand->Collisioncheck(this);

if (collider!=NULL)
{
if (collider->getID()==enemy)
{

	core::vector3df nudge=m_position-collider->getPosition();
	nudge.normalize();
	nudge.operator * (0.01);
	m_velocity= nudge;
	m_velocity.Z=1.5;
	m_stun=20;
}
if (collider->getID()==projectile)
{
	m_health-=collider->getHealth();
	m_pstagehand->createexplosion(collider->getPosition());
	m_pstagehand->Remove(collider);
}
}


if (m_lifespan<0)
{
m_alive=false;

}
if (m_health<1)
{
		m_pstagehand->createchunk(m_position,m_velocity,true);
		m_pstagehand->createchunk(m_position,m_velocity,true);
		m_pstagehand->createchunk(m_position,m_velocity,true);
	m_alive=false;
}





if (!m_alive)
{
	m_pstagehand->Remove(this);
}

}
