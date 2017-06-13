#include "Boss.h"

Boss::Boss (scene::ISceneNode *node,video::ITexture *textures[], Stagehand *stagehand)
{

	//m_position=core::vector3df(0,0,-15750);
	m_position=core::vector3df (0,0,-6750);
	//m_position=core::vector3df(0,0,-160);
	//m_velocity=core::vector3df(0,0,1);
	m_velocity=core::vector3df(0,0,0.4);
	m_clock=15600;
	//m_clock=60;
	m_state=dormant;
	m_value1=0;
	m_pnode=node;
	m_health=0;
	m_id=other;
	for (int i=0;i<7;i++)
	{
	m_textures[i]=textures[i];
	}
	//m_pnode->setMaterialFlag(video::EMF_LIGHTING,false);
	m_pstagehand=stagehand;
	m_eyes=false;
	m_size=72;
	m_value2=0;
	m_cooldown=0;
	m_bool=false;
}


void Boss::update()
{
	if (m_clock>0)
	{
	m_clock--;
	}
	if (m_state==dormant)
	{
	m_position+=m_velocity;

	m_pnode->setPosition(m_position);
	if (m_clock==600)
	{
		m_velocity=core::vector3df(0,0,1);
	}
	if (m_clock==0)
	{
	m_state=awaken;
	m_velocity=core::vector3df (0,0,0);
	m_clock=460;
	}
	}
	if (m_state==awaken)
	{
	if (m_clock>100)
	{
		m_value1+=0.5;

		m_pnode->setRotation(core::vector3df(0,m_value1,0));
	}
	if (m_clock<=100)
	{

	m_health=100-(m_clock);
	}
	if (m_clock==100)
	{
		m_pstagehand->setmessage(L"?????");
		m_pstagehand->setbossbar(true);
		m_lefty=(Claw*)m_pstagehand->createclaw(core::vector3df(60,-30,-105),true);
		m_righty=(Claw*)m_pstagehand->createclaw(core::vector3df(-60,-30,-105),false);
	}
	if (m_clock==0)
	{
	m_state=base;
	m_clock=30;
	m_health=100;
	}

	}
	if (m_state==base)
	{
	if (m_clock==0)
	{
	m_state=eyes_opening;
	m_pnode->setMaterialTexture(0,m_textures[1]);
	m_clock=40;
	m_eyes=true;
	}

	}
	if (m_state==eyes_opening)
	{
	if (m_clock==0)
	{
	m_state=eyes_open;

	m_pnode->setMaterialTexture(0,m_textures[2]);
	//change texture here when textures implemented
	}

	}
	if (m_state==claw_attack)
	{

	if (m_clock<1)
		{
						if (!m_bool)
						{
							m_righty->clawattack();
						}
						else
						{
							m_lefty->clawattack();
						}	
			m_state=base;
						m_clock=90;
		}
	
	}

	if (m_state==eyes_open)
	{


	if (m_clock==0)
	{
			Actor *target=m_pstagehand->getplayer();
		if (target!=NULL)
			{
				core::vector3df eye1= core::vector3df(21,24,-100);
				core::vector3df firingsolution=(target->getPosition()+m_pstagehand->randomvector()*(rand()%5))- eye1;
				firingsolution+= m_pstagehand->randomvector()* (rand()%20);
				firingsolution= firingsolution.normalize() *1.5;
				m_pstagehand->createfireball(eye1,firingsolution);	
				core::vector3df eye2= core::vector3df(-21,24,-100);
				 firingsolution=(target->getPosition()+m_pstagehand->randomvector()*(rand()%5))- eye2;
				firingsolution+= m_pstagehand->randomvector()* (rand()%20);
				firingsolution= firingsolution.normalize() *1.8;
				m_pstagehand->createfireball(eye2,firingsolution);	
				m_value2++;
				m_clock=10;
				int numberofshots=8;
				if (m_health<50)
				{
					numberofshots=12;
				}
				if (m_value2==numberofshots)
					{
						m_state=base;
						m_pnode->setMaterialTexture(0,m_textures[0]);
						m_value2=0;
						m_clock=180;
						//change textures here when textures implemented.
						m_eyes=false;

						bool righty=rand()%2;
						if (righty)
						{
							m_righty->clawattack();
						}
						else
						{
							m_lefty->clawattack();
						}
						if (m_health<50)
						{
							m_bool=righty;
							m_state=claw_attack;
							m_clock=44;
						}
	
					}
			}
		}
	}

	
	Actor *collider=m_pstagehand->Collisioncheck(this);
	if (collider!=NULL)
	{
		if (collider->getID()==projectile)
		{
			bool hit=false;
			//position check
			core::vector3df position=collider->getPosition();
			if (position.X>15 && position.X<31 && position.Y >21 && position.Y <29 && m_eyes)
				{
					if (m_state!=dormant && m_state!=awaken)
					{
						m_health-=collider->getHealth();
						hit=true;
					}
				}
			if (position.X>-31 && position.X<-15 && position.Y >19 && position.Y <27 && m_eyes)
				{
					if (m_state!=dormant && m_state!=awaken)
					{
						m_health-=collider->getHealth();
						hit=true;
					}
				}			
			if (hit)
			{
			m_pstagehand->createexplosion(collider->getPosition());
			}
			else
			{
				m_pstagehand->createexplosion(collider->getPosition(),3);
			}
			m_pstagehand->Remove(collider);
			if (m_health<1 && m_state!=dormant && m_state!=awaken)
				{
					m_pstagehand->setgamewin();
					m_state=dying;
					m_clock=10;
					m_pnode->setMaterialTexture(0,m_textures[3]);
				}
		}
	
	
	}
	
	if (m_state==dying)
	{
	if (m_clock==0)
	{
	m_clock=10;
	core::vector2df position=m_pstagehand->randomposition();
	core::vector3df pos3d;
	pos3d.X=position.X;
	pos3d.Y=position.Y;
	pos3d.Z=m_position.Z+70;
	m_pstagehand->createexplosion(pos3d);
	}

	}
}