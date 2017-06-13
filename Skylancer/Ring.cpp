#include "Ring.h"







Ring::Ring(irr::scene::IMeshSceneNode *node)
{
m_pnode=node;
m_position=m_pnode->getPosition();
m_velocity=irr::core::vector3df(0,0,2);
m_size=-1;

}

void Ring::update()
{

	m_position.operator += (m_velocity);
m_pnode->setPosition(m_position);

if (m_position.Z>0)
{
 m_position.Z=-1500;
}


}
