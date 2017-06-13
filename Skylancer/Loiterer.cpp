#include "Loiterer.h"

Loiterer::Loiterer (Stagehand *pstagehand, scene::ISceneNode *node,core::vector3df position, int aggression)
{
m_pnode=node;
m_pstagehand=pstagehand;
m_position=position;
m_velocity=core::vector3df (0,0,1);
m_lifespan=1200;
m_aggression=aggression;
m_pnode->setPosition(position);
m_guncooldown=0;
m_size=5;
m_health=4;
m_shotsfired=0;
m_timetodestination=150+(rand()%60);
m_spin=0;
m_alive=true;
m_destination= core::vector3df(0,0,0);
m_id=enemy;
m_spin_increment=0;
}

void Loiterer::update()
{
	m_position+= m_velocity;

	m_pnode->setPosition(m_position);

if (m_guncooldown>0)
{
m_guncooldown--;
}

m_lifespan--;

if (m_lifespan>0)
{
//this code is for sitting still and firing, put all that logic inside this if statement
if (m_timetodestination==0)
	{	
		m_spin=0;
		m_spin_increment=0;
m_pnode->setRotation(core::vector3df(0,0,0));
		m_velocity=core::vector3df(0,0,0);



	if (m_shotsfired==m_aggression )
		{
			m_shotsfired=0;
		//pick a new position, set is  as m_destination. determine time to destination as distance between locations and set that.
			core::vector2df newposition=m_pstagehand->randomposition();
			core::vector3df newposition3d=core::vector3df(newposition.X,newposition.Y,m_position.Z+5);
			float distance=newposition3d.getDistanceFrom(m_position);

			m_timetodestination=210-(m_aggression*15);
			m_velocity=(newposition3d.operator -(m_position)).normalize().operator * (distance/m_timetodestination);
				m_spin_increment=360/m_timetodestination;
		}
	//shoot the player	some here
		else if (m_guncooldown==0)
		{
		Actor *target=m_pstagehand->getplayer();
		if (target!=NULL)
		{
			core::vector3df firingsolution=(target->getPosition()+m_pstagehand->randomvector()*(rand()%5))- m_position;
			firingsolution+= m_pstagehand->randomvector()* (rand()%10);
			firingsolution= firingsolution.normalize() *1.5;

			m_guncooldown=20;
			m_shotsfired++;
			m_pstagehand->createfireball(m_position,firingsolution);
			if (m_shotsfired==m_aggression)
			{
			m_timetodestination=60;
			}
		}

		}
	}	

//this is for moving between one position and another.
if (m_timetodestination>0)
	{
		m_timetodestination--;
		m_spin+=m_spin_increment;
		m_pnode->setRotation(core::vector3df(0,0,m_spin));
	}
}
if (m_lifespan<0)
	{
		if (m_velocity.Z<2)
		{
			m_velocity+= core::vector3df(0,0,0.1);
		}

	}

if (m_lifespan<-100)
	{
		m_alive=false;

	}


Actor* collider=m_pstagehand->Collisioncheck(this);

if (collider!=NULL)
{
if (collider->getID()==enemy)
{

	core::vector3df nudge=m_position-collider->getPosition();
	nudge.normalize();
	nudge= nudge*0.1;
	m_position+= (nudge);

}
if (collider->getID()==projectile)
{
	m_health-=collider->getHealth();
	m_pstagehand->createexplosion(collider->getPosition());
	m_pstagehand->Remove(collider);
}
}

if (m_health<1)
{
	m_alive=false;
}


if (m_alive==false)
	{	
		m_pstagehand->createchunk(m_position,m_velocity,true,true);
		m_pstagehand->createchunk(m_position,m_velocity,true,true);
		m_pstagehand->createchunk(m_position,m_velocity,true,true);
		m_pstagehand->Remove(this);
	}
}