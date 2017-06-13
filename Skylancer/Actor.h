#include <irrlicht.h>
using namespace irr;


#ifndef ACTOR
#define ACTOR

enum identity {player,enemy,other,projectile,enemy_projectile,powerup};
class Actor
{

protected:
	irr::core::vector3df  m_position;
	irr::core::vector3df m_velocity;
	irr::scene::ISceneNode *m_pnode;
	float m_size;
	float m_health;
	identity m_id;
	bool m_alive;
public:

	Actor(){};
	~Actor(){};

	virtual void update(){};

	irr::scene::ISceneNode* Getnode(){return m_pnode;};

	core::vector3df getPosition(){return m_position;};
	float getSize(){return m_size;};
	float getHealth(){return m_health;};
	void setHealth(int hp){m_health=hp;};
	identity getID(){return m_id;};

};

#endif