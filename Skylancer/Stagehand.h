#include "Actor.h"
#include <irrlicht.h>

#ifndef STAGEHAND
#define STAGEHAND

class Stagehand
{

protected:
bool m_bbossbar;
Actor **m_array_ptr;
scene::ISceneManager *m_smgr;
video::IVideoDriver *m_driver;
core::stringw m_message;
int m_messagelifespan;
public:
	Stagehand (Actor **array_ptr, video::IVideoDriver *driver, scene::ISceneManager *smgr);
	Stagehand (){};
Actor * Collisioncheck (Actor * caller);

void Remove(Actor * target);

virtual void createasteroid(core::vector3df position, bool megaroid, bool crystal=false, bool immortal=false){};
virtual void createtorpedo(core::vector3df position, core::vector3df rotation, bool turbo){};
virtual void createexplosion(core::vector3df position,int type=0){};
virtual void Dev_randomasteroids(float difficulty){};
virtual void createlivingasteroid(core::vector3df position, float aggression=0.1F){};
virtual void createchunk(core::vector3df position, core::vector3df velocity,bool trail=false, bool metal=false){};
virtual void createloiterer(core::vector3df position, int aggression=1){};
virtual void createfireball(core::vector3df position, core::vector3df velocity){};
virtual void createcrystal (core::vector3df position){};
virtual void burnplayer(){};
virtual void createlaser(core::vector3df position, core::vector3df rotation){};
virtual Actor * createclaw(core::vector3df position, bool righty){return NULL;};
virtual void setbossbar(bool enabled){};
void Draw(gui::IGUIFont *font);
 void setmessage (core::stringw message);
int findemptyspot();

virtual void setgameover(){};
virtual void setgamewin(){};
virtual core::vector3df randomvector(){return core::vector3df(0,0,0);};
virtual core::vector2df randomposition(){return core::vector2df(0,0);};

virtual void Setplayermesh(int meshnumber){};
Actor* getplayer(){return m_array_ptr[0];};

};

#endif