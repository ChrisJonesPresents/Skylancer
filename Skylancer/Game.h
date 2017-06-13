#include <irrlicht.h>
#include <irrklang.h>
#include "eventreceiver.cpp"
#include "Actor.h"
#include "Stagehand_ex.h"
#include "Player.h"
#include "Ring.h"
#include "Boss.h"

using namespace irr;
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")
#ifndef GAME
#define GAME

class Game
{

private:
ISoundEngine *m_sound;
ISound *m_gametheme;
bool m_buttonpressed;
WNEventReceiver *m_peventreceiver;
scene::ISceneManager *m_smgr;
video::IVideoDriver *m_driver;
scene::ILightSceneNode *m_light;
scene::ILightSceneNode *m_light2;
irr::scene::ICameraSceneNode *m_pcamera;
Actor **m_pactor_array;
bool m_button;
e_STATE m_state;
unsigned int m_icinematic;
 gui::IGUIFont* m_font;
 video::ITexture *m_backdrop;
 video::ITexture *m_front;
 video::ITexture *m_crystals[2];
 video::ITexture *m_pictures[4];
 Stagehand_ex *m_stagehand;
	int tick;
	bool m_bgameover;
unsigned int m_imastertimer;
unsigned int m_icrystaltimer;
unsigned int m_tick2;
int m_backdropoffset;
Player *m_player;
video::ITexture *m_reticule;
video::ITexture **m_imagebatch;
	core::array<video::ITexture *> m_shieldsequence;



public:

	Game(video::IVideoDriver *driver, ISoundEngine *sound, scene::ISceneManager *scenemgr,WNEventReceiver *eventreceiver, gui::IGUIFont *font);

	~Game();

void Update();




void Watchbriefing();

void startgame();

void draw();

void cleargameworld();

bool geteditmode(){return m_buttonpressed;};


};

#endif