#include <irrlicht.h>
#include "Actor.h"
#include "Stagehand.h"
#include "Claw.h"
using namespace irr;

#ifndef BOSS
#define BOSS

enum state {dormant,awaken,base,eyes_opening, eyes_closing,eyes_open, dying, claw_attack};

class Boss : public Actor
{

protected:

Stagehand *m_pstagehand;
video::ITexture * m_textures[7];
state m_state;
int m_clock;
float m_value1;
bool m_eyes;
int m_value2;
int m_cooldown;
Claw *m_lefty;
Claw *m_righty;
bool m_bool;
public:

	Boss (scene::ISceneNode *node,video::ITexture *textures[], Stagehand *stagehand);


	void update();

	


};

#endif