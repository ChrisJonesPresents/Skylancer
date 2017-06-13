#include "Game.h"




Game::Game(video::IVideoDriver *driver, ISoundEngine *sound, scene::ISceneManager *scenemgr,WNEventReceiver* eventreceiver, gui::IGUIFont *font)
{
m_sound=sound;
m_state=s_menu;
//m_pcamera= scenemgr->addCameraSceneNode(0, core::vector3df(0,12.5,00), core::vector3df(0,0,0));
//m_pcamera->bindTargetAndRotation(true);
//m_pcamera->setUpVector(core::vector3df(0,0,1));

m_sound->play2D("Sound/2k3.mp3",true);
m_peventreceiver=eventreceiver;
m_imastertimer=0;
m_smgr=scenemgr;
m_driver=driver;
m_font=font;
m_icinematic=0;
m_smgr->setAmbientLight(video::SColor(180,180,180,180));
m_pactor_array= new Actor*[128];
	m_imagebatch=new video::ITexture *[6];
tick=0;
m_button=false;
m_tick2=0;
for (int i=0;i<128;i++)
{
m_pactor_array[i]=NULL;

}
m_backdrop=m_driver->getTexture("Resources/panorama.tga");
m_front=m_driver->getTexture("Resources/frontpage.tga");
m_backdropoffset=1200;
m_crystals[0]=m_driver->getTexture("Resources/emptycrystal.tga");
m_crystals[1]=m_driver->getTexture("Resources/fullcrystal.tga");
m_pictures[0]=m_driver->getTexture("Resources/pictureresource.tga");
m_pictures[1]=m_driver->getTexture("Resources/picturecollect.tga");
m_pictures[2]=m_driver->getTexture("Resources/picturebar.tga");
m_pictures[3]=m_driver->getTexture("Resources/pictureevolve.tga");
m_shieldsequence.push_back(m_driver->getTexture("Resources/shield0.tga"));
m_shieldsequence.push_back(m_driver->getTexture("Resources/shield1.tga"));
m_shieldsequence.push_back(m_driver->getTexture("Resources/shield2.tga"));
m_shieldsequence.push_back(m_driver->getTexture("Resources/shield3.tga"));
m_stagehand= new Stagehand_ex (m_pactor_array,m_driver,m_sound,m_smgr,&m_state,&m_icinematic);
m_reticule=m_driver->getTexture("Resources/reticule.tga");
	m_imagebatch[0]= m_driver->getTexture("Resources/briefing0.tga");

	m_imagebatch[1]= m_driver->getTexture("Resources/briefing1.tga");

	m_imagebatch[2]= m_driver->getTexture("Resources/briefing2.tga");
	m_imagebatch[3]= m_driver->getTexture("Resources/briefingpic0.tga");

	m_imagebatch[4]= m_driver->getTexture("Resources/briefingpic1.tga");

	m_imagebatch[5]= m_driver->getTexture("Resources/briefingpic2.tga");	
}

Game::~Game()
{
	m_sound->stopAllSounds();
m_sound->drop();

for (int i=0;i<128;i++)
{
if (m_pactor_array[i]!=NULL)
{
delete m_pactor_array[i];
}

}
delete[] m_pactor_array;
delete[] m_imagebatch;
}

void Game::Watchbriefing()
{

if (m_tick2<30)
{
if (tick<=10)
{
	m_driver->draw2DImage(m_imagebatch[0],core::vector2d <s32>(0,0));
}
else
{
	m_driver->draw2DImage(m_imagebatch[1],core::vector2d <s32>(0,0));
}
}
else
{
	m_driver->draw2DImage(m_imagebatch[2],core::vector2d <s32>(0,0));
}

if (m_tick2<15)
{
	m_driver->draw2DImage(m_imagebatch[3],core::vector2d<s32>(395,60));
		m_font->draw(L"Trouble.",core::rect<s32>(200,400,600,500),video::SColor(255,255,255,255),true);
}
if (m_tick2>=15 && m_tick2<31)
{
	m_driver->draw2DImage(m_imagebatch[4],core::vector2d<s32>(395,60));
		m_font->draw(L"Source?",core::rect<s32>(200,400,600,500),video::SColor(255,255,255,255),true);
}
if (m_tick2>=31 && m_tick2<45)
{
	m_driver->draw2DImage(m_imagebatch[5],core::vector2d<s32>(395,60));
		m_font->draw(L"Investigate!",core::rect<s32>(200,400,600,500),video::SColor(255,255,255,255),true);
}

}

void Game::Update()
{
	if (m_button && !m_peventreceiver->IsKeyDown(KEY_KEY_Z) && !m_peventreceiver->IsKeyDown(KEY_KEY_P))
	{
		m_button=false;
	}

if (m_state==s_briefing)
{
	tick++;
	if (tick>20)
	{
		tick=0;
		m_tick2++;
	}
	if (m_peventreceiver->IsKeyDown(KEY_KEY_Z) && !m_button)
	{
		tick=0;
	m_tick2=0;

	m_sound->stopAllSounds();
	startgame();
	}
	if (m_tick2==15 && tick==1)
	{
		m_sound->play2D("Sound/blah.wav");
	}
	if (m_tick2==30 && tick==1 )
	{	

		m_sound->play2D("Sound/blahsingle.wav");
	}

	if (m_tick2>37)
	{
		m_sound->stopAllSounds();
	startgame();
	m_tick2=0;
	tick=0;
	}



}

if (m_state==s_menu)
{
	if (m_peventreceiver->IsKeyDown(KEY_KEY_Z) && !m_button)
	{
	m_sound->stopAllSounds();
		m_sound->play2D("Sound/blah.wav");
	m_state=s_briefing;
	m_button=true;
	tick=0;

	}
	if (tick<255)
	{
	tick++;
	}

}
if (m_state==s_pause)
{
	m_tick2++;
	if (m_tick2>3200)
	{
	m_tick2=0;
	}
core::vector3df pos= m_pcamera->getPosition();
pos.rotateXZBy(-0.703125);

m_pcamera->setPosition(pos);

m_backdropoffset=1200+(6.25*m_tick2);
if (m_backdropoffset>3200)
{
m_backdropoffset=m_backdropoffset-3200;
}
	if (m_peventreceiver->IsKeyDown(KEY_KEY_P) && !m_button)
	{
		m_tick2=0;
	m_state=s_play;
	m_button=true;
m_pcamera->setPosition(core::vector3df(0,2,12));
m_pcamera->setTarget(core::vector3df(0,0,-300));

	}



}
if (m_icinematic>0)
{
if (m_icinematic==128)
{
	
	m_pcamera->setTarget(m_pactor_array[0]->getPosition());
	core::vector3df manip=m_pcamera->getTarget();
	manip.Y+=1.5;
	m_pcamera->setTarget(manip);
}
//m_pcamera->setPosition(core::vector3df(0,2,12));
core::vector3df pos= m_pcamera->getPosition();
pos.rotateXZBy(-2.8125);

m_pcamera->setPosition(pos);

m_icinematic--;
m_stagehand->cinematic(m_icinematic*2);
m_backdropoffset=1200+(25*m_icinematic);
if (m_backdropoffset>3200)
{
m_backdropoffset=m_backdropoffset-3200;
}
if (m_icinematic==0)
{

m_pcamera->setPosition(core::vector3df(0,2,12));
m_pcamera->setTarget(core::vector3df(0,0,-300));
}

}
if (m_state==s_win||m_state==s_play)
{

	if (m_peventreceiver->IsKeyDown(KEY_KEY_P) && !m_button)
	{
	m_button=true;
	m_state=s_pause;
	m_pcamera->setTarget(m_pactor_array[0]->getPosition());
	core::vector3df manip=m_pcamera->getTarget();
	manip.Y+=1.5;
	m_pcamera->setTarget(manip);
	}

if (m_icinematic==0)
	{
m_backdropoffset=1200- (m_player->getPosition().X*1);

tick++;


if (tick>60)
{
	
	tick=0;
		m_imastertimer++;
		int aggression=m_imastertimer/30;
		if (aggression>6)
		{
			aggression=6;
		}
		if (m_imastertimer<=245)
		{
	m_icrystaltimer++;
		if (m_imastertimer>5  )
		{
			m_stagehand->Dev_randomasteroids(aggression);
		}


	if (m_icrystaltimer>7 )
	{
		core::vector2df position=m_stagehand->randomposition();
		position=position*0.5;
		m_stagehand->createasteroid(core::vector3df(position.X,position.Y,-300),false,true);
		m_icrystaltimer=0;
	}
		}
if (m_imastertimer==245)
{
//	m_light2->setVisible(false);
	m_stagehand->Remove(m_pactor_array[1]);
	m_stagehand->Remove(m_pactor_array[2]);
	m_stagehand->Remove(m_pactor_array[3]);
}
	if (m_imastertimer>60 && m_imastertimer<220)
	{
		int special=rand()%12;
		if (special==9)
		{

			core::vector2df position=m_stagehand->randomposition();
			m_stagehand->createloiterer(core::vector3df (position.X,position.Y,-300),aggression-1);
		}

	}

	if (m_imastertimer==260)
	{
		m_sound->play2D("Sound/evil.wav");
	}
}
	

//m_stagehand->createlivingasteroid(core::vector3df(0,0,-300));

	for (int i=0;i<128;i++)
		{
			if (m_pactor_array[i]!=NULL)
			{
				m_pactor_array[i]->update();
			}

		}

}
}

	if (m_state==s_lose)
	{
	m_tick2++;
	m_player->shrink();
	if (m_tick2>60)
	{
	m_state=s_menu;
	cleargameworld();

	m_tick2=0;
	}
	}
	if (m_state==s_win)
	{
	m_tick2++;
	if (m_tick2>120)
	{
	m_state=s_menu;
	cleargameworld();
	
	m_tick2=0;
	}
	}
}

void Game::startgame()
{
m_state=s_play;
m_imastertimer=0;
m_icrystaltimer=0;
m_light=m_smgr->addLightSceneNode(0,core::vector3df(100,25,25),video::SColorf(0.7,0.7,0.6),500);

	m_sound->play2D("Sound/music.mp3",true,false,true);




tick=0;
//generate player
irr::scene::IMesh *mesh= m_smgr->getMesh("Mesh/SWORDSMAN.obj");
//irr::scene::IMesh *mesh= m_smgr->getMesh("Mesh/SWORDSMAN2.obj");
irr::scene::IMeshSceneNode *meshnode = m_smgr->addMeshSceneNode(mesh);
//meshnode->setMaterialFlag(video::EMF_LIGHTING, true);
meshnode->getMaterial(0).setTexture( 0, m_driver->getTexture("Mesh/swordsmantexture.tga") );
//meshnode->getMaterial(0).setTexture( 0, m_driver->getTexture("Mesh/swordsman2texture.tga") );
video::ITexture *damagetexture=m_driver->getTexture("Mesh/damage.tga");
//meshnode->getMaterial(1).setTexture(1,m_driver->getTexture("mesh/swordsmanglow1.tga"));
meshnode->getMaterial(0).setFlag(video::EMF_LIGHTING,true);
//video::E_MATERIAL_TYPE mtype= meshnode->getMaterial(0).MaterialType;
//meshnode->getMaterial(1).setFlag(video::EMF_LIGHTING,false);
//meshnode->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
meshnode->setScale(core::vector3df(0.75,0.75,0.75));
meshnode->getMaterial(0).Shininess=20;
meshnode->getMaterial(0).SpecularColor= video::SColor(0,200,200,255);
//meshnode->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
//	m_smgr->getMeshManipulator()->setVertexColorAlpha(meshnode->getMesh(),-255);
//add engine flare
scene::IParticleSystemSceneNode *flare= m_smgr->addParticleSystemSceneNode(true,meshnode,-1,core::vector3df(0,0,4));
//generate flare particle emitter and attach it
//scene::IParticleEmitter *em= flare->createPointEmitter(core::vector3df(0,0,3),5,10,video::SColor(0,200,200,255),video::SColor(0,255,255,255),2000,4000,10);
//scene::IParticleEmitter *em= flare->createSphereEmitter(core::vector3df(0,0,1),0.5,core::vector3df(0,0,3));
        scene::IParticleEmitter* em = flare->createBoxEmitter(
                core::aabbox3d<f32>(-2,-2,-4,2,2,4), 

                core::vector3df(0.0f,0.00f,0.03f),4000 
               ,4000,                            
                video::SColor(0,122,122,155),      
                video::SColor(0,222,222,255),       
                50,50,3,                         
                core::dimension2df(0.7f,0.7f),         
                core::dimension2df(1.5f,1.5f));        

flare->setEmitter(em);
em->drop();

//generate particle fadeout system
        scene::IParticleAffector* paf = flare->createFadeOutParticleAffector();

        flare->addAffector(paf); // same goes for the affector
        paf->drop();
		//configure things properly
        flare->setScale(core::vector3df(0.1,0.1,0.1));
        flare->setMaterialFlag(video::EMF_LIGHTING, false);
        flare->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        flare->setMaterialTexture(0, m_driver->getTexture("Resources/spark.bmp"));
        flare->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

//add shield bubble
		scene::IBillboardSceneNode *snode=m_smgr->addBillboardSceneNode(meshnode,core::dimension2d<f32>(5,5));
		snode->setMaterialTexture(0,m_driver->getTexture("Resources/shield0.tga"));
		snode->setMaterialFlag(video::EMF_LIGHTING,false);
		snode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	scene::ISceneNodeAnimator *anim= m_smgr->createTextureAnimator(m_shieldsequence,50,true);
	snode->addAnimator(anim);
			snode->setVisible(false);

//add player logic
			bool god=false;
			if (m_peventreceiver->IsKeyDown(KEY_KEY_G) && m_peventreceiver->IsKeyDown(KEY_KEY_M) && m_peventreceiver->IsKeyDown(KEY_KEY_T))
			{
			god=true;
			}

m_pactor_array[0]= new Player(meshnode,m_peventreceiver,flare,m_stagehand,snode,god);

//add camera
m_pcamera= m_smgr->addCameraSceneNode(m_pactor_array[0]->Getnode(), core::vector3df(0,2,12), core::vector3df(0,0,-300));
m_pcamera->setFarValue(16000);
m_pcamera->setUpVector(core::vector3df(0,1,0));

m_player=(Player*)m_pactor_array[0];

scene::ISceneNode *node=m_smgr->addBillboardSceneNode(meshnode,core::dimension2d<f32>(5,5),core::vector3df(0,-1,-50));
node->setMaterialTexture(0,m_driver->getTexture("Resources/reticule.tga"));
        node->setMaterialFlag(video::EMF_LIGHTING, false);
       node->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

scene::ISceneNode *node2=m_smgr->addBillboardSceneNode(meshnode,core::dimension2d<f32>(5,5),core::vector3df(0,-1,-100));
node2->setMaterialTexture(0,m_driver->getTexture("Resources/reticuletwo.tga"));
        node2->setMaterialFlag(video::EMF_LIGHTING, false);
       node2->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        node2->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

		
//generate world


//generate the ring
mesh = m_smgr->getMesh("Mesh/Ring.obj");
meshnode= m_smgr->addMeshSceneNode(mesh);


meshnode->getMaterial(0).EmissiveColor=video::SColor(200,50,50,255);
meshnode->getMaterial(0).DiffuseColor=video::SColor(200,50,50,255);
meshnode->setPosition(core::vector3df(0,0,-100));
meshnode->setScale(core::vector3df(9,9,9));
meshnode->setRotation(core::vector3df(90,0,180));
meshnode->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);
meshnode->setMaterialFlag(video::EMF_FRONT_FACE_CULLING,false);
meshnode->setMaterialFlag(video::EMF_LIGHTING, false);
m_pactor_array[1]= new Ring(meshnode);

meshnode= m_smgr->addMeshSceneNode(mesh);

meshnode->getMaterial(0).EmissiveColor=video::SColor(200,50,50,255);
meshnode->getMaterial(0).DiffuseColor=video::SColor(200,50,50,255);
meshnode->setPosition(core::vector3df(0,0,-600));
meshnode->setScale(core::vector3df(9,9,9));
meshnode->setRotation(core::vector3df(90,0,180));
meshnode->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);
meshnode->setMaterialFlag(video::EMF_FRONT_FACE_CULLING,false);
meshnode->setMaterialFlag(video::EMF_LIGHTING, false);
m_pactor_array[2]= new Ring(meshnode);

meshnode= m_smgr->addMeshSceneNode(mesh);

meshnode->getMaterial(0).EmissiveColor=video::SColor(200,50,50,255);
meshnode->getMaterial(0).DiffuseColor=video::SColor(200,50,50,255);
meshnode->setPosition(core::vector3df(0,0,-1100));
meshnode->setScale(core::vector3df(9,9,9));
meshnode->setRotation(core::vector3df(90,0,180));
meshnode->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);
meshnode->setMaterialFlag(video::EMF_FRONT_FACE_CULLING,false);
meshnode->setMaterialFlag(video::EMF_LIGHTING, false);
m_pactor_array[3]= new Ring(meshnode);

//generate everything else
scene::IMesh *bmesh= m_smgr->getMesh("Mesh/sphere.obj");
scene::IMeshSceneNode *bmeshnode= m_smgr->addMeshSceneNode(bmesh);
bmeshnode->setMaterialTexture(0,m_driver->getTexture("Mesh/planetb.tga"));
bmeshnode->getMaterial(0).EmissiveColor=video::SColor(25,25,25,25);
//bmeshnode->setPosition(core::vector3df(0,0,-120));
bmeshnode->setScale(core::vector3df(70,70,70));
//bmeshnode->setRotation(core::vector3df(0,180,0));
bmeshnode->getMaterial(0).Shininess=20;

video::ITexture *list[7];
list[0]=m_driver->getTexture("Mesh/planetb.tga");
list[1]=m_driver->getTexture("Mesh/planetw.tga");
list[2]=m_driver->getTexture("Mesh/planetr.tga");
list[3]=m_driver->getTexture("Mesh/planetd.tga");

m_pactor_array[4]= new Boss(bmeshnode,list,m_stagehand);
//m_stagehand->creatasteroid(core::vector2df (0,0),false);
//m_stagehand->createloiterer(core::vector3df(0,0,-300));
m_light2=m_smgr->addLightSceneNode(bmeshnode,core::vector3df(100,70,-70),video::SColorf(0.7,0.7,0.6),500);

}

void Game::draw()
{
	if (m_state!=s_menu && m_state!=s_briefing)
	{
//		m_driver->draw2DImage(m_backdrop,core::vector2d<s32>(0,0));
		int tint=m_imastertimer;
		if (tint>255)
		{
		tint=255;
		}
		m_driver->draw2DImage(m_backdrop,core::vector2d<s32>(0,0),core::rect<s32>(m_backdropoffset,0,m_backdropoffset+800,600),NULL,video::SColor(255,255,255-tint,255-tint));
		m_smgr->drawAll();
		//m_driver->draw2DImage(m_reticule,core::vector2d<s32>(384,284));
		//		char buffer[3];
		//	Player *ptr=(Player*)m_pactor_array[0];
		//	itoa(ptr->Getepoints(),&buffer[0],10);	
			//m_font->draw(buffer,core::rect<s32>(10,500,100,600),video::SColor(255,255,255,255),true);
				int filled=m_player->Getlevel()*4-m_player->Getepoints();
				for (int i=0;i<m_player->Getlevel()*4;i++)
				{
				if (i<filled)
				{
					m_driver->draw2DImage(m_crystals[1],core::vector2d<s32>(16+(32*i),550), core::rect<s32>(0,0,32,32),NULL,video::SColor(255,255,255,255),true);

				}
				else
				{
					m_driver->draw2DImage(m_crystals[0],core::vector2d<s32>(16+(32*i),550), core::rect<s32>(0,0,32,32),NULL,video::SColor(255,255,255,255),true);
				}


				}

			if (m_imastertimer>0 && m_imastertimer<4)
			{
				m_driver->draw2DImage(m_pictures[0],core::vector2d<s32>(360,25));
				m_font->draw(L"Destroy!",core::rect<s32>(360,105,440,145),video::SColor(255,255,255,255),true);
			}
			if (m_imastertimer>3 && m_imastertimer<7)
			{
				m_driver->draw2DImage(m_pictures[1],core::vector2d<s32>(360,25));
				m_font->draw(L"Collect!",core::rect<s32>(360,105,440,145),video::SColor(255,255,255,255),true);
			}
			if (m_imastertimer>6 && m_imastertimer<10)
			{
				m_driver->draw2DImage(m_pictures[2],core::vector2d<s32>(360,25));
				m_font->draw(L"Fill!",core::rect<s32>(360,105,440,145),video::SColor(255,255,255,255),true);
			}
			if (m_imastertimer>9 && m_imastertimer<13)
			{
				m_driver->draw2DImage(m_pictures[3],core::vector2d<s32>(360,25));
				m_font->draw(L"Evolve!",core::rect<s32>(360,105,440,145),video::SColor(255,255,255,255),true);
			}

			m_stagehand->Draw(m_font);

		if (m_state==s_lose)
		{

		m_font->draw(L"Game Over",core::rect<s32>(200,200,600,300),video::SColor(255,255,255,255),true);
		}
		if (m_state==s_win)
		{

		m_font->draw(L"Congratulations, you have won.",core::rect<s32>(200,200,600,300),video::SColor(255,255,255,255),true);
		}
		if (m_state==s_pause)
		{
		m_font->draw(L"Game is paused.",core::rect<s32>(200,200,600,300),video::SColor(255,255,255,255),true);

		}
	}
	if (m_state==s_menu)
	{
		m_driver->draw2DImage(m_front,core::vector2d<s32>(0,0),core::rect<s32>(0,0,800,600),NULL,video::SColor(255,tick,tick,tick));
		if (tick>200)
		{
			m_font->draw(L"Press Z to begin",core::rect<s32>(200,300,600,400),video::SColor(255,255,255,255),true);
		}
	}
	if (m_state==s_briefing)
	{
	Watchbriefing();


	}

}

void Game::cleargameworld()
{
	m_sound->stopAllSounds();
	m_sound->play2D("Sound/2k3.mp3",true);
for (int i=0;i<128;i++)
{
	if (m_pactor_array[i]!=NULL)
	{
	//we have an issue in the code, comment out line below to see
	m_pactor_array[i]->Getnode()->setVisible(false);
	//m_pactor_array[i]->Getnode()->drop();
	m_smgr->getRootSceneNode()->removeChild(m_pactor_array[i]->Getnode());

	delete m_pactor_array[i];
	m_pactor_array[i]=NULL;

	}
	
}

	m_smgr->getRootSceneNode()->removeAll();


}