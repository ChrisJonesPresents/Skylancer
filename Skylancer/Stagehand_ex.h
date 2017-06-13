#include <irrklang.h>
#include "Stagehand.h"
#include "Asteroid.h"
#include "Torpedo.h"
#include "Explosion.h"
#include "Living_Asteroid.h"
#include "Chunk.h"
#include "Loiterer.h"
#include "Fireball.h"
#include "Crystal.h"
#include "Laser.h"
#include "Claw.h"

using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")

#ifndef STAGEHAND_EX
#define STAGEHAND_EX

enum e_STATE {s_menu,s_briefing,s_play,s_win,s_lose,s_pause};

class Stagehand_ex : public Stagehand
{




private:
	e_STATE *pstate;

	core::array<video::ITexture *> m_explosionsequence;
	core::array<video::ITexture *> m_fireballsequence;
	core::array<video::ITexture *> m_fireballsplosionsequence;
	core::array<video::ITexture *> m_pingsequence;
	scene::IMeshSceneNode *m_fadenode;
	unsigned int *m_pcinematic;
	ISoundEngine *m_sound;
public:

Stagehand_ex(Actor **array_ptr, video::IVideoDriver *driver, ISoundEngine *sound, scene::ISceneManager *smgr, e_STATE *state,unsigned int *cinematic);
void createasteroid(core::vector3df position, bool megaroid, bool crystal=false, bool immortal=false);
void createtorpedo(core::vector3df position,  core::vector3df rotation, bool turbo);
void createexplosion(core::vector3df position, int type=0);
 void createlivingasteroid(core::vector3df position, float aggression=0.1F);
void Dev_randomasteroids(float difficulty);
void createchunk(core::vector3df position, core::vector3df velocity,bool trail=false, bool metal=false);
void createloiterer(core::vector3df position, int aggression=1);
 void createfireball(core::vector3df position, core::vector3df velocity);
 void createcrystal (core::vector3df position);
void createlaser(core::vector3df position, core::vector3df rotation);
Actor * createclaw(core::vector3df position, bool righty);
 void Setplayermesh(int meshnumber);
core::vector2df randomposition();
void burnplayer();
void setgameover();
 void setbossbar(bool enabled);
void setgamewin();
core::vector3df randomvector();

void cinematic(int shift);

};

#endif