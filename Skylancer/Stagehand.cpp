#include "Stagehand.h"







Stagehand::Stagehand (Actor **array_ptr, video::IVideoDriver *driver, scene::ISceneManager *smgr)
{
m_array_ptr=array_ptr;

m_smgr=smgr;
m_driver=driver;


}

Actor * Stagehand::Collisioncheck (Actor * caller)
{
//check sequentially against every object in the gameworld
for (int i=0;i<128;i++)
	{
		//ignore collisions with the self
	if (m_array_ptr[i]!=caller)
		{
			if (m_array_ptr[i]!=NULL)
			{
		//ignore collision disabled objects
			if (m_array_ptr[i]->getSize()!=-1)
			{
				//add the two collision radiuses together and compare them to the distance between the two points
				float maxcollision=m_array_ptr[i]->getSize()+caller->getSize();
				if (m_array_ptr[i]->getPosition().getDistanceFrom(caller->getPosition())<maxcollision)
				{

				return m_array_ptr[i];
				}

			}
			}
		
		}
	}

return NULL;

}

void Stagehand::Remove(Actor * target)
{

	if (target->Getnode()!=NULL)
	{

	m_smgr->getRootSceneNode()->removeChild(target->Getnode());


	}
	for (int i=0;i<128;i++)
	{
	if (target==m_array_ptr[i])
	{
		delete m_array_ptr[i];
		m_array_ptr[i]=NULL;
		break;
	}


	}


}



int Stagehand::findemptyspot()
{
for (int i=0;i<128;i++)
{
	if (m_array_ptr[i]==NULL)
	{
		return i;
	}

}
	return -1;
}

 void Stagehand::Draw(gui::IGUIFont *font)
{

if (m_messagelifespan>0)
{
m_messagelifespan--;
font->draw(m_message,core::rect<s32>(200,400,600,500),video::SColor(255,255,255,255),true);

}
if (m_bbossbar)
{
			char buffer[4];
			itoa(m_array_ptr[4]->getHealth(),&buffer[0],10);	
			font->draw(buffer,core::rect<s32>(700,32,800,100),video::SColor(255,255,255,255),true);

			m_driver->draw2DRectangle(video::SColor(255,255,0,0),core::rect<s32>(100,32,100+(m_array_ptr[4]->getHealth()*6),64));


}

}
 void Stagehand::setmessage (core::stringw message)
{
m_messagelifespan=128;
m_message=message;




}