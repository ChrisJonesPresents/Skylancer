#include "Fireball.h"


Fireball::Fireball (scene::ISceneNode *node, core::vector3df position, core::vector3df velocity, Stagehand* p_stagehand)
{
m_pnode=node;
m_position=position;
m_velocity=velocity;
m_pstagehand=p_stagehand;
m_lifespan=180;
m_size=1;
m_health=1;
m_id=enemy_projectile;
m_alive=true;


}

void Fireball::update()
{

m_position.operator += (m_velocity);
m_pnode->setPosition(m_position);

m_lifespan--;

if (m_lifespan<1)
{
m_alive=false;
}


if (!m_alive)
{
m_pstagehand->Remove(this);
}

}