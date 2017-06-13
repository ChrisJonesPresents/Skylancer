#ifdef _MSC_VER
// We'll also define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
//#include "driverChoice.h"

using namespace irr;

#ifndef EVENTRECEIVER
#define EVENTRECEIVER

class WNEventReceiver : public IEventReceiver
{
public:
        // This is the one method that we have to implement
        virtual bool OnEvent(const SEvent& event)
        {

                if (event.EventType == EET_GUI_EVENT )
                {
					if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED || event.GUIEvent.EventType == gui::EGET_CHECKBOX_CHANGED || event.GUIEvent.EventType== gui::EGET_MENU_ITEM_SELECTED)
						GUI=event.GUIEvent.Caller->getID();
					
					if (event.GUIEvent.EventType == 6)
					{
						GUI=event.GUIEvent.Caller->getID();
						GUI_2=((gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();

					}






				return false;
				}

                // Remember whether each key is down or up
                if (event.EventType == irr::EET_KEY_INPUT_EVENT)
				{
                        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
				
                return false;
				}
				else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
				{	
					if (event.MouseInput.Event == EMIE_MOUSE_MOVED)
					{
						mouseposition.X=event.MouseInput.X;
						mouseposition.Y=event.MouseInput.Y;	

					}
					if (event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
					{
						b_1=true;
				
					}
					if (event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
					{
						b_1=false;
					}
					if (event.MouseInput.Event == EMIE_RMOUSE_PRESSED_DOWN)
					{
						b_2=true;
				
					}
					if (event.MouseInput.Event == EMIE_RMOUSE_LEFT_UP)
					{
						b_2=false;
					}
					return false;
				}
				return false;
        };
		
        // This is used to check whether a key is being held down
        virtual bool IsKeyDown(EKEY_CODE keyCode) const
        {
                return KeyIsDown[keyCode];
        };
        
		void mousestate(bool *a1,bool *a2, core::vector2d <s32> *position)
		{
		*a1=b_1;
		*a2=b_2;
		*position=mouseposition;
		};

		s32 getGUI()
		{
		return GUI;

		};
		s32 getGUI2()
		{
		return GUI_2;

		};
        WNEventReceiver()
        {
                for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
                        KeyIsDown[i] = false;
			
				mouseposition.X=0;
				mouseposition.Y=0;
				b_1=false;
				b_2=false;
				GUI=0;
				GUI_2=0;
        };
		
		void WNClear()
		{

		GUI=0;
		};

private:
        // We use this array to store the current state of each key
        bool KeyIsDown[KEY_KEY_CODES_COUNT];
		core::vector2d <s32> mouseposition;
		bool b_1, b_2;
		s32 GUI;
		s32 GUI_2;
};

#endif