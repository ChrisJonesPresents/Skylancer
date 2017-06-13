#include "Torpedo.h"




Torpedo::Torpedo(Stagehand *stagehand, core::vector3df position, core::vector3df rotation, scene::ISceneNode *node, bool turbo)
{
m_pnode=node;
m_stagehand=stagehand;
m_bturbo=turbo;
m_position=position;
m_position.Y-=0.2;
m_pnode->setRotation(rotation);
float buf=rotation.X;
rotation.X=rotation.Y;
rotation.Y=buf;
m_size=1;
m_health=3;
m_id=projectile;
m_lifespan=180;
//m_velocity=core::vector3df(0,0,0);
m_velocity=core::vector3df(0,-0.1,0);
core::vector3df velocity= core::vector3df (0,0,-1);
velocity.rotationToDirection(rotation);
velocity.rotateYZBy(rotation.Y);
velocity.rotateXYBy(rotation.Z);
m_velocity.operator += (velocity);
m_velocity.Z=0;
}


void Torpedo::update()
{
m_position.operator += (m_velocity);
m_pnode->setPosition(m_position);

m_lifespan--;

if (m_lifespan>170 && m_bturbo)
{
m_velocity.Z-=0.4;
}

if (m_lifespan==170)
{
if (!m_bturbo)
{
m_velocity.Z=-1;
}
m_velocity.Y+=0.1;
}

if (m_lifespan<0)
{
m_stagehand->Remove(this);
}

}