#include "Claw.h"




Claw::Claw (scene::IMeshSceneNode *node, core::vector3df position, Stagehand *stagehand, bool righty)
{
	m_position=position;
	m_pnode=node;
	m_pstagehand=stagehand;
	m_isrighty=righty;
	if (righty)
	{
	m_rotation=core::vector3df (0,180,-45);
	}
	if (!righty)
	{
	m_rotation=core::vector3df (0,180,45);
	}
	m_pnode->setRotation(m_rotation);
	m_clock=99;
	m_state=awakening;
	m_size=8;
	m_id=enemy;
	m_isrighty=righty;
	m_health=3;
}

void Claw::update()
{

if (m_clock>0)
{
m_clock--;
}

if (m_state==awakening)
{
	m_pnode->setScale(core::vector3df(5-(m_clock/20),5-(m_clock/20),5-(m_clock/20)));
	if (m_clock<1)
	{
	m_state=cbase;
	}

}
if (m_state==striking)
{

m_position += m_velocity;
m_pnode->setPosition(m_position);

if (m_health==0)
{
m_size=-1;
}

if (m_clock<1)
{
m_state=returning;
core::vector3df targ;
if (m_isrighty)
{
m_velocity=core::vector3df(60,-30,-105)-m_position;
targ=core::vector3df(55,-25,-105);
}
else
{
m_velocity=core::vector3df(-60,-30,-105)-m_position;
targ=core::vector3df(-55,-25,-105);
}
m_velocity=m_velocity.normalize();
m_clock=m_position.getDistanceFrom(targ);
}

}
if (m_state==returning)
{
m_position+=m_velocity;
m_pnode->setPosition(m_position);

if (m_health==0)
{
m_size=-1;
}

if (m_clock<0)
{
m_state=cbase;
	if (!m_isrighty)
	{
		m_rotation.Z=45;
	}
	if (m_isrighty)
	{
		m_rotation.Z=-45;
	}
	m_pnode->setRotation(m_rotation);

	m_health=3;
	m_size=8;
}
}
if (m_state==readying)
{


	if (m_clock<1)
	{
		float distance=m_pstagehand->getplayer()->getPosition().getDistanceFrom(m_position);
		float timetotarget=distance/4;
		core::vector3df estimate=m_pstagehand->getplayer()->getPosition()-m_positionmemory;
		estimate=estimate*(timetotarget/30);
		estimate=estimate+m_pstagehand->getplayer()->getPosition();
		core::vector3df firingsolution=estimate-m_position;
		firingsolution=firingsolution.normalize()*4;
		m_velocity=firingsolution;
		m_clock=timetotarget;
		m_state=striking;
	}


}
		Actor *collider=m_pstagehand->Collisioncheck(this);
	if (collider!=NULL)
	{
		if (collider->getID()==projectile)
		{		
			m_pstagehand->createexplosion(collider->getPosition());
			m_pstagehand->Remove(collider);

		}
	}




}


void Claw::clawattack()
{	if (m_state==cbase)
{
	m_state=readying;

	m_positionmemory=m_pstagehand->getplayer()->getPosition();

	m_clock=30;
	if (m_isrighty)
	{
		m_rotation.Z=-90;
	}
	if (!m_isrighty)
	{
		m_rotation.Z=90;
	}
	m_pnode->setRotation(m_rotation);
}
}