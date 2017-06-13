#include "Player.h"


using namespace std; 

Player::Player (irr::scene::IMeshSceneNode *node,WNEventReceiver *eventreceiver, scene::IParticleSystemSceneNode *flare, Stagehand *stagehand,scene::ISceneNode *shieldnode, bool godmode)
{
m_pnode=node;
m_eventreceiver=eventreceiver;
m_position=m_pnode->getPosition();
m_velocity=irr::core::vector3df(0,0,0);
m_movementspeed=0.45;
m_rotation=core::vector3df(0,0,0);
m_rotated=false;
m_flare=flare;
m_pstagehand=stagehand;
m_size=2;
m_health=2;
m_id=player;
m_enablecontrols=true;
scale=core::vector3df(1,1,1);
m_evolutionlevel=1;
m_evolutionpoints=m_evolutionlevel*4;
m_guncooldown=60;
m_shield=shieldnode;
m_shieldpower=0;
m_specialmove=0;
m_godmode=godmode;
m_bdoabarrelroll=false;
for (int i=0;i<6;i++)
{
m_movement[i]=false;
}
}

Player::~Player()
{




}

void Player::update()
{	//input logic

	if (m_evolutionlevel>=4)
	{
	if (m_shieldpower<1)
		{
			m_shieldpower+=0.002;
			if (m_shieldpower>0.999)
			{
				m_shield->setVisible(true);
			}
		}
	}
	if (m_specialmove>0)
	{
	m_specialmove--;
	m_position.operator += (m_velocity);
	m_pnode->setPosition(m_position);
	if (m_movement[4])
	{
	m_rotation.Z+=360/20;
	}
	if (m_movement[5])
	{
	m_rotation.Z-=360/20;
	}
	m_pnode->setRotation(m_rotation);
	if (m_specialmove==0)
	{
		m_velocity=core::vector3df(0,0,0);
		m_movement[4]=false;
		m_movement[5]=false;
		m_rotation=core::vector3df(0,0,0);
		m_pnode->setRotation(m_rotation);
		m_specialmove=-60;
	}
	}

	if (m_specialmove<0)
	{
		m_specialmove++;
	}

	if (m_enablecontrols && m_specialmove<1)
	{	
		if (m_guncooldown)
		{
			m_guncooldown--;
		}
		if (m_eventreceiver->IsKeyDown (KEY_KEY_Z) && m_guncooldown==0)
		{
			/*
		if (m_evolutionlevel>=3)
		{
		m_guncooldown=20;
		m_pstagehand->createlaser(m_position,m_rotation);
		}
		*/
		if (m_evolutionlevel>=3)
		{
		m_guncooldown=35;
		m_pstagehand->createtorpedo(m_position,m_rotation,true);

		}

		if (m_evolutionlevel<3)
		{
		m_guncooldown=27;
		m_pstagehand->createtorpedo(m_position,m_rotation,false);
		}
		}
		
		if (m_eventreceiver->IsKeyDown (KEY_KEY_X) && m_godmode)
		{
		m_evolutionpoints--;
		goto CHECK;
		}
		
		if (m_eventreceiver->IsKeyDown (KEY_DOWN))
		{
			m_movement[2]=true;
		}
		else
			m_movement[2]=false;
		if (m_eventreceiver->IsKeyDown (KEY_UP))
		{
			m_movement[0]=true;
		}
			else
				m_movement[0]=false;
		if (m_eventreceiver->IsKeyDown (KEY_LEFT))
		{
			m_movement[3]=true;
		}
			else
				m_movement[3]=false;
		if (m_eventreceiver->IsKeyDown (KEY_RIGHT) )
		{
			m_movement[1]=true;
		}
			else
				m_movement[1]=false;
		/*
		if (m_eventreceiver->IsKeyDown(KEY_KEY_A) && !m_eventreceiver->IsKeyDown(KEY_KEY_D) && m_bdoabarrelroll && m_specialmove==0)
		{
		if (m_position.X+20<40*cos(asin(m_position.Y/40)))
			{
				m_movement[5]=true;
				m_velocity.X+=1;
				m_specialmove=20;
			}
		}
		//	else
		//		m_movement[5]=false;

		if ( m_eventreceiver->IsKeyDown(KEY_KEY_D)&& !m_eventreceiver->IsKeyDown(KEY_KEY_A) && m_bdoabarrelroll && m_specialmove==0)
		{
		if (m_position.X-20>-40*cos(asin(m_position.Y/40)))

			{
				m_movement[4]=true;
				m_velocity.X-=1;
				m_specialmove=20;
			}
		}
		//	else
		//		m_movement[4]=false;
		*/
	
	if (!m_movement[1] && !m_movement[3])
	{
		if (m_rotation.Y>0)
		{
			m_rotation.Y-=0.2;

		}
		if (m_rotation.Y<0)
		{
			m_rotation.Y+=0.2;
		}

		
	}
	if (!m_movement[0] && !m_movement[2])
	{
		if (m_rotation.X>0)
		{
			m_rotation.X-=0.2;
		}
		if (m_rotation.X<0)
		{
			m_rotation.X+=0.2;
		}


	}
		if (m_rotated)
		m_pnode->setRotation(m_rotation);
	if (m_rotation.X==0 && m_rotation.Y==0)
	{
		m_rotated=false;
	}
	if (m_movement[0])
	{
		if (m_position.Y<40*cos(asin(m_position.X/40)))
		{
			m_rotated=true;
			m_position.Y+=m_movementspeed;
			if (m_rotation.X<m_movementspeed*2)
				m_rotation.X+=0.4;
		}
		else
		{
		if (m_position.X<0)
			{
			m_rotated=true;
			m_position.X+=m_movementspeed;
			}
		if (m_position.X>0)
			{
			m_rotated=true;
			m_position.X-=m_movementspeed;
			}
		}
	}
	if (m_movement[2] )
	{
		if (m_position.Y>-40*cos(asin(m_position.X/40)))
		{
			m_rotated=true;
			m_position.Y-=m_movementspeed;
			if (m_rotation.X>m_movementspeed*-2)
				m_rotation.X-=0.4;
		}
		else
		{
		if (m_position.X<0)
			{
			m_rotated=true;
			m_position.X+=m_movementspeed;
			}
		if (m_position.X>0)
			{
			m_rotated=true;
			m_position.X-=m_movementspeed;
			}
		}
	}
	if (m_movement[1] )
	{
		if (m_position.X>-40*cos(asin(m_position.Y/40)))
		{
			m_rotated=true;
			m_position.X-=m_movementspeed;
			if (m_rotation.Y<m_movementspeed*2)
				m_rotation.Y+=0.4;
		}
		else
		{
		if (m_position.Y<0)
			{
			m_rotated=true;
			m_position.Y+=m_movementspeed;
			}
		if (m_position.Y>0)
			{
			m_rotated=true;
			m_position.Y-=m_movementspeed;
			}
		}
	}
	if (m_movement[3] )
	{
		if (m_position.X<40*cos(asin(m_position.Y/40)))
		{
			m_rotated=true;
			m_position.X+=m_movementspeed;
			if (m_rotation.Y>m_movementspeed*-2)
				m_rotation.Y-=0.4;
		}
		else
		{
		if (m_position.Y<0)
			{
			m_rotated=true;
			m_position.Y+=m_movementspeed;
			}
		if (m_position.Y>0)
			{
			m_rotated=true;
			m_position.Y-=m_movementspeed;
			}
		}

	}
	if (m_movement[0]||m_movement[1]||m_movement[2]||m_movement[3])
	{
		m_pnode->setPosition(m_position);
	}

	Actor* collider=m_pstagehand->Collisioncheck(this);
	if (collider!=NULL)
	{
		if (collider->getID()==enemy)
		{
			if (m_shieldpower<1 && !m_godmode)
			{
				m_health-=2;
			}

			if (m_shieldpower>0.999 && !m_godmode)
			{
				m_health-=1;
				m_shield->setVisible(false);
				m_shieldpower=0;
			}

			if (m_health>0)
			{
				collider->setHealth(0);
			}

		

		}
		if (collider->getID()==enemy_projectile && !m_godmode)
		{
			m_pstagehand->createexplosion(collider->getPosition(),1);
			if (m_shieldpower<1)
			{
				m_health-=collider->getHealth();
			}

			if (m_shieldpower>0.999)
			{
				m_health-=collider->getHealth()-1;
				m_shieldpower=0;
				m_shield->setVisible(false);
			}

			m_pstagehand->Remove(collider);

			
		}
		if (collider->getID()==powerup)
		{
			m_evolutionpoints--;
			m_pstagehand->createexplosion(collider->getPosition(),2);
			m_pstagehand->Remove(collider);
CHECK:
			if (m_evolutionpoints==0)
			{
			m_evolutionlevel++;
			m_evolutionpoints=m_evolutionlevel*4;
			m_pstagehand->Setplayermesh(m_evolutionlevel-1);

			if (m_evolutionlevel==2)
				{
				m_movementspeed+=0.25;
				//m_bdoabarrelroll=true;
				m_pstagehand->setmessage(L"Energized engines!");
				}
			if (m_evolutionlevel==4)
			{
				m_shieldpower=1;
				m_pstagehand->setmessage(L"Regenerative forcefield!");
				m_shield->setVisible(true);
			}
			if (m_evolutionlevel==3)
			{
				m_pstagehand->setmessage(L"Turbo missiles!");

			}
			}

		}
			if (m_health==1)
			{
				m_pstagehand->burnplayer();

			}

			if (m_health<1)
			{
			m_pstagehand->setgameover();
			m_enablecontrols=false;
			m_pstagehand->createexplosion(m_position);
			}
	}


}
}

void Player::shrink()
{

		scale.X-=0.02;
		scale.Y-=0.02;
		scale.Z-=0.02;
		m_pnode->setScale(scale);
	



}