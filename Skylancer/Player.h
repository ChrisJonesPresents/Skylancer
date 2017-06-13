#include "Actor.h"
#include "Stagehand.h"
#include "eventreceiver.cpp"
#include <stdio.h>
#include <math.h>




#ifndef PLAYER
#define PLAYER

class Player : public Actor
{

private:
	unsigned int m_evolutionpoints;
	unsigned char m_evolutionlevel;
	unsigned int m_guncooldown;
	core::vector3df m_rotation;
	float m_movementspeed;
	WNEventReceiver *m_eventreceiver;
	bool m_movement[6];
	bool m_rotated;
	scene::IParticleSystemSceneNode *m_flare;
	Stagehand *m_pstagehand;
	bool m_enablecontrols;
	video::ITexture *m_damagetexture;
	scene::ISceneNode *m_shield;
	float m_shieldpower;
	int m_specialmove;
	bool m_bdoabarrelroll;
	bool m_godmode;
core::vector3df scale;
public:
	
	Player (irr::scene::IMeshSceneNode *node,WNEventReceiver *eventreceiver, scene::IParticleSystemSceneNode *flare, Stagehand *stagehand,scene::ISceneNode *shieldnode,bool godmode=false);

	~Player();

	void update();

	void shrink();

	int Getepoints(){return m_evolutionpoints;};
	int Getlevel(){return m_evolutionlevel;};
};

#endif