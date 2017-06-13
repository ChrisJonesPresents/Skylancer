#include <irrlicht.h>
#include <irrklang.h>
#include "Game.h"
#include "eventreceiver.cpp"




using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace irrklang;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#pragma comment(lib, "irrKlang.lib")
#endif

#define desired_fps 60
#define frame_increment 1000/desired_fps







int main ()
{

	u32 time=0;
	WNEventReceiver *eventreceiver=new WNEventReceiver();
	//initialization code

	video::E_DRIVER_TYPE driverType=video::EDT_DIRECT3D9;
        if (driverType==video::EDT_COUNT)
                return 1;

        // create device

        IrrlichtDevice *device = createDevice(driverType,
                core::dimension2d<u32>(800, 600), 16, false, false, false, eventreceiver);
		irrklang::ISoundEngine *sdevice= irrklang::createIrrKlangDevice();

		scene::ISceneManager *scene_mgr=device->getSceneManager();
  //      scene_mgr->addCameraSceneNode(0, core::vector3df(0,10,00), core::vector3df(0,0,0));

        if (device == 0)
                return 1; // could not create selected driver.

        device->setWindowCaption(L"Skylancer Desperation");

        video::IVideoDriver* driver = device->getVideoDriver();
		gui::IGUIFont *font = device->getGUIEnvironment()->getFont("Font/Font.xml");
		//gui::IGUIFont *font = device->getGUIEnvironment()->getBuiltInFont();
		
Game * p_game=new Game(driver, sdevice,scene_mgr,eventreceiver,font);


irr::core::vector2d<int> corner(16,16);

        while(device->run() && driver)
        {
                if (device->isWindowActive())
                {
					time = device->getTimer()->getRealTime();
						//put logic function calls here

					p_game->Update();
						
                        driver->beginScene(true, true, video::SColor(255,0,0,0));
						//put drawing function calls here



						//scene_mgr->drawAll();
						//scene_mgr->getGUIEnvironment()->drawAll();
						p_game->draw();
                       driver->endScene();

						while (device->getTimer()->getRealTime()<frame_increment+time)
						{

						}

                }
				else
                                device->yield();



        }
		delete p_game;
		delete eventreceiver;
        device->drop();

return 0;
}