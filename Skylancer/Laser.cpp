#include "Laser.h"	



Laser::Laser (core::vector3df position, core::vector3df rotation, scene::ISceneNode *node, Stagehand *pstagehand)
{

m_pnode=node;
m_pstagehand=pstagehand;
m_position=position;
float buf=rotation.X;
rotation.X=rotation.Y;
rotation.Y=buf;
m_pnode->setRotation(rotation);
m_velocity=core::vector3df (0,0,-4);
m_position.Y-=1;
m_velocity.rotationToDirection(rotation);
m_velocity.rotateYZBy(rotation.Y);

m_size=3;
m_id=projectile;
m_health=2;
m_alive=true;
m_lifespan=180;


}

void Laser::update()
{
m_position += m_velocity;
m_pnode->setPosition(m_position);


m_lifespan--;

if (m_lifespan<1)
{
m_alive=false;
}
if (m_alive==false)
{
	m_pstagehand->Remove(this);
}

}