#include "Stagehand_ex.h"
#include <stdlib.h>
#include <time.h>

Stagehand_ex::Stagehand_ex(Actor **array_ptr, video::IVideoDriver *driver, ISoundEngine *sound,scene::ISceneManager *smgr, e_STATE *state, unsigned int *cinematic)
{
m_sound=sound;
m_array_ptr=array_ptr;
m_pcinematic=cinematic;
m_smgr=smgr;
m_driver=driver;
srand ( time(NULL) );
m_messagelifespan=0;
pstate=state;
m_bbossbar=false;
m_explosionsequence.push_back(m_driver->getTexture("Resources/exp0.tga"));
m_explosionsequence.push_back(m_driver->getTexture("Resources/exp1.tga"));
m_explosionsequence.push_back(m_driver->getTexture("Resources/exp2.tga"));
m_explosionsequence.push_back(m_driver->getTexture("Resources/exp3.tga"));
m_explosionsequence.push_back(m_driver->getTexture("Resources/exp4.tga"));
m_explosionsequence.push_back(m_driver->getTexture("Resources/exp5.tga"));

m_fireballsequence.push_back(m_driver->getTexture("Resources/Laser0.tga"));
m_fireballsequence.push_back(m_driver->getTexture("Resources/Laser1.tga"));
m_fireballsequence.push_back(m_driver->getTexture("Resources/Laser2.tga"));
m_fireballsequence.push_back(m_driver->getTexture("Resources/Laser3.tga"));
m_fireballsequence.push_back(m_driver->getTexture("Resources/Laser4.tga"));
m_fireballsequence.push_back(m_driver->getTexture("Resources/Laser5.tga"));
m_fireballsequence.push_back(m_driver->getTexture("Resources/Laser6.tga"));
m_fireballsequence.push_back(m_driver->getTexture("Resources/Laser7.tga"));

m_fireballsplosionsequence.push_back(m_driver->getTexture("Resources/fireball0.tga"));
m_fireballsplosionsequence.push_back(m_driver->getTexture("Resources/fireball1.tga"));
m_fireballsplosionsequence.push_back(m_driver->getTexture("Resources/fireball2.tga"));
m_fireballsplosionsequence.push_back(m_driver->getTexture("Resources/fireball3.tga"));
m_fireballsplosionsequence.push_back(m_driver->getTexture("Resources/fireball4.tga"));
m_fireballsplosionsequence.push_back(m_driver->getTexture("Resources/fireball5.tga"));
m_fireballsplosionsequence.push_back(m_driver->getTexture("Resources/fireball6.tga"));
m_fireballsplosionsequence.push_back(m_driver->getTexture("Resources/fireball7.tga"));

m_pingsequence.push_back(m_driver->getTexture("Resources/ping0.tga"));
m_pingsequence.push_back(m_driver->getTexture("Resources/ping1.tga"));
m_pingsequence.push_back(m_driver->getTexture("Resources/ping2.tga"));
m_pingsequence.push_back(m_driver->getTexture("Resources/ping3.tga"));
m_pingsequence.push_back(m_driver->getTexture("Resources/ping4.tga"));
m_pingsequence.push_back(m_driver->getTexture("Resources/ping5.tga"));
m_pingsequence.push_back(m_driver->getTexture("Resources/ping6.tga"));
m_pingsequence.push_back(m_driver->getTexture("Resources/ping7.tga"));
}

void Stagehand_ex::createasteroid(core::vector3df position, bool megaroid, bool crystal, bool immortal)
{


int point=findemptyspot();
if (point!=-1)
	{

		scene::IMesh *mesh;
		if (!crystal)
		{
		mesh=m_smgr->getMesh("Mesh/asteroid2.obj");
		}
		if (crystal)
		{
			mesh=m_smgr->getMesh("Mesh/asteroid3.obj");
		}
		scene::IMeshSceneNode *meshnode=m_smgr->addMeshSceneNode(mesh,0,-1,core::vector3df(0,0,-10));
		if (!crystal)
		{
		meshnode->setMaterialTexture(0, m_driver->getTexture("Mesh/asteroidtexture.tga"));
		}
		meshnode->setScale(core::vector3df(5,5,5));
		if (megaroid)
		{
		meshnode->setScale(core::vector3df(8,8,8));
		}
		if (crystal)
		{
			meshnode->setMaterialTexture(0,m_driver->getTexture("Mesh/asteroidcrystal2texture.tga"));
			meshnode->getMaterial(0).Shininess=20;
		/*scene::IBillboardSceneNode *node=m_smgr->addBillboardSceneNode(meshnode,core::dimension2d<f32> (15,15),core::vector3df(0,0,0));
		node->setMaterialTexture(0,m_driver->getTexture("Resources/spark.tga"));
		node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
		*/
		}
		if (immortal)
		{
			meshnode->setMaterialTexture(0,m_driver->getTexture("Mesh/asteroidinvulnerabletexture.tga"));
			meshnode->getMaterial(0).Shininess=20;
		}
		m_array_ptr[point]=new Asteroid(this,position,meshnode,megaroid,crystal,immortal);
		core::vector3df rotation=randomvector();
       scene::ISceneNodeAnimator* anim = m_smgr->createRotationAnimator (rotation);
			meshnode->addAnimator(anim);
		anim->drop();
			
	}
}
void Stagehand_ex::createtorpedo(core::vector3df position, core::vector3df rotation, bool turbo)
{
	
	int point= findemptyspot();
	if (point!=-1)
	{
		irrklang::ISound *snd=m_sound->play2D("Sound/missile.wav",false);
		scene::IMesh *mesh=m_smgr->getMesh("Mesh/torpedo.obj");
		scene::IMeshSceneNode *meshnode=m_smgr->addMeshSceneNode(mesh);
		meshnode->setMaterialTexture(0,m_driver->getTexture("Mesh/torpedotexture.tga"));
		meshnode->getMaterial(0).Shininess=20;
		meshnode->setScale(core::vector3df(0.8,0.8,0.8));
	meshnode->getMaterial(0).SpecularColor= video::SColor(0,200,200,255);
		m_array_ptr[point]=new Torpedo(this,position,rotation,meshnode,turbo);
		video::SColor color1= video::SColor (0,155,22,22);
		video::SColor color2= video::SColor (0,255,222,222);
		if (turbo)
		{
			color1= video::SColor (0,255,100,0);
			color2= video::SColor (0,255,0,0);
		}
scene::IParticleSystemSceneNode *flare= m_smgr->addParticleSystemSceneNode(true,meshnode,-1,core::vector3df(0,0,3.5));
        scene::IParticleEmitter* em = flare->createBoxEmitter(
                core::aabbox3d<f32>(-2,-2,-4,2,2,4), 

                core::vector3df(0.0f,0.00f,0.01f),1000 
               ,2000,                            
                color1,      
                color2,       
                300,300,1,                         
                core::dimension2df(1.0f,1.0f),         
                core::dimension2df(1.8f,1.8f));        

flare->setEmitter(em);
em->drop();

        scene::IParticleAffector* paf = flare->createFadeOutParticleAffector();

        flare->addAffector(paf); // same goes for the affector
        paf->drop();
        flare->setScale(core::vector3df(0.1,0.1,0.1));
        flare->setMaterialFlag(video::EMF_LIGHTING, false);
        flare->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        flare->setMaterialTexture(0, m_driver->getTexture("Resources/spark.bmp"));
        flare->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

	}
}

void Stagehand_ex::createexplosion(core::vector3df position, int type)
{

int point=findemptyspot();
if (point!=-1)
{
	scene::IBillboardSceneNode *node=m_smgr->addBillboardSceneNode(0,core::dimension2d<f32>(20,20));
	if (type==0)
	{
	node->setMaterialTexture(0,m_explosionsequence[0]);
	scene::ISceneNodeAnimator *anim= m_smgr->createTextureAnimator(m_explosionsequence,50,false);
	node->addAnimator(anim);
	m_sound->play2D("Sound/hit.wav",false);
	}	
	if (type==3)
	{
	node->setMaterialTexture(0,m_pingsequence[0]);
	scene::ISceneNodeAnimator *anim= m_smgr->createTextureAnimator(m_pingsequence,50,false);
	node->addAnimator(anim);
	m_sound->play2D("Sound/ineffective.wav",false);

	}
	if (type==1 || type==2)
	{
	node->setMaterialTexture(0,m_fireballsplosionsequence[0]);
	scene::ISceneNodeAnimator *anim= m_smgr->createTextureAnimator(m_fireballsplosionsequence,50,false);
	node->addAnimator(anim);
			node->setColor(video::SColor(0,255,50,50));
			if (type==2)
			{
				node->setColor(video::SColor(0,170,170,255));
				m_sound->play2D("Sound/crystalget.wav",false);
			}
	}
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL );

	m_array_ptr[point]= new Explosion(this,node,position);
}
}

void Stagehand_ex::Dev_randomasteroids(float difficulty)
 {

	int number=rand()%3+1;
	
	for (int i=0;i<number;i++)
	{
		core::vector2df position=randomposition();
		int living=0;
		if (difficulty)
		{
		int living=rand()%5;
		
		if (living==4)
		{
			if (difficulty>3)
			{
			difficulty=3;
			}
			float aggression=difficulty/20;
			createlivingasteroid(core::vector3df(position.X,position.Y,-300),aggression);

			}
		}
		
		
		int ran=rand()%4;
		int immortal=0;
		if (difficulty>1)
		{
		immortal=rand()%4;
		}
		createasteroid(core::vector3df(position.X,position.Y,-300),ran==3,false,immortal==3);
		

	}


 }

void Stagehand_ex::createlivingasteroid(core::vector3df position, float aggression)
 {

int point=findemptyspot();

if (point!=-1)
{
	scene::IMesh *mesh=m_smgr->getMesh("Mesh/asteroidlive.obj");
	scene::IMeshSceneNode *meshnode= m_smgr->addMeshSceneNode(mesh);

	meshnode->setMaterialTexture(0,m_driver->getTexture("Mesh/asteroidlivetexture.tga"));
		
		meshnode->getMaterial(0).Shininess=20;
		meshnode->setScale(core::vector3df(3,3,3));
	meshnode->getMaterial(0).SpecularColor= video::SColor(0,255,255,55);
	m_array_ptr[point]=new Living_Asteroid(this, position, meshnode,m_array_ptr[0],aggression);
	scene::ISceneNodeAnimator* anim = m_smgr->createRotationAnimator (core::vector3df(0,0,1));
			meshnode->addAnimator(anim);
		anim->drop();
}
 }

void Stagehand_ex::createchunk(core::vector3df position, core::vector3df velocity,bool trail,bool metal)
{
int point=findemptyspot();

if (point!=-1)
{		
	scene::IMesh *mesh;
		velocity=randomvector();
		if (!metal)
		mesh=m_smgr->getMesh("Mesh/asteroid2.obj");
		else
		mesh=m_smgr->getMesh("Mesh/debris.obj");
		scene::IMeshSceneNode *meshnode=m_smgr->addMeshSceneNode(mesh,0,-1,core::vector3df(0,0,-10));
		if (!metal)
		meshnode->setMaterialTexture(0, m_driver->getTexture("Mesh/asteroidtexture.tga"));
		else
		meshnode->setMaterialTexture(0, m_driver->getTexture("Mesh/debristexture.tga"));
		
		meshnode->setScale(core::vector3df(3,3,3));
		m_array_ptr[point]=new Chunk(position,velocity,meshnode, this);
		if (trail)
		{
			video::SColor color=video::SColor(0,155,22,22);
			video::SColor colormax=video::SColor(0,255,22,22);
		if (metal)
		{
			color=video::SColor(0,155,155,22);
			colormax=video::SColor(0,255,255,22);

		}
scene::IParticleSystemSceneNode *trail= m_smgr->addParticleSystemSceneNode(true,meshnode,-1,core::vector3df(0,0,0));
        scene::IParticleEmitter* em = trail->createBoxEmitter(
                core::aabbox3d<f32>(-2,-2,-2,2,2,2), 

                core::vector3df(0.0f,0.00f,0.0f),500 
               ,1000,                            
                color,      
				colormax,       
                300,300,1,                         
                core::dimension2df(0.6f,0.6f),         
                core::dimension2df(1.2f,1.2f));        

trail->setEmitter(em);
em->drop();

        scene::IParticleAffector* paf = trail->createFadeOutParticleAffector();

        trail->addAffector(paf); // same goes for the affector
        paf->drop();
        trail->setScale(core::vector3df(0.1,0.1,0.1));
        trail->setMaterialFlag(video::EMF_LIGHTING, false);
        trail->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        trail->setMaterialTexture(0, m_driver->getTexture("Resources/spark.bmp"));
        trail->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

	}
}


}
		




void Stagehand_ex::setgameover()
{
*pstate=s_lose;
//scene::ISceneNodeAnimator* anim = m_smgr->createRotationAnimator (core::vector3df(0.1,0,0.1));
//			m_array_ptr[0]->Getnode()->addAnimator(anim);
scene::IParticleSystemSceneNode *flare= m_smgr->addParticleSystemSceneNode(true,m_array_ptr[0]->Getnode(),-1,core::vector3df(0,0,0));

        scene::IParticleEmitter* em = flare->createBoxEmitter(
                core::aabbox3d<f32>(-2,-2,-2,2,2,2), 
 
                core::vector3df(0.0f,0.00f,0.02f),  
                300,400,                            
                video::SColor(0,122,122,155),      
                video::SColor(0,222,222,255),       
                100,400,90,                         
                core::dimension2df(0.6f,0.6f),         
                core::dimension2df(2.2f,2.2f));        

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
        flare->setMaterialTexture(0, m_driver->getTexture("Resources/fire.bmp"));
        flare->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
}

void Stagehand_ex::createloiterer(core::vector3df position, int aggression)
{

	int point=findemptyspot();
	if (point!=-1)
	{
		scene::IMesh *mesh= m_smgr->getMesh("Mesh/loiterer.obj");
		scene::IMeshSceneNode *meshnode=m_smgr->addMeshSceneNode(mesh);
		meshnode->setMaterialTexture(0,m_driver->getTexture("Mesh/loiterertexture.tga"));
		meshnode->getMaterial(0).Shininess=20;
		meshnode->setScale(core::vector3df(2,2,2));
	meshnode->getMaterial(0).SpecularColor= video::SColor(0,255,255,55);
		m_array_ptr[point]= new Loiterer (this, meshnode,position, aggression);
		


	}






}

core::vector3df Stagehand_ex::randomvector()
{

	core::vector3df vector;
	/*
		int random= rand() % 12;
		switch(random)
		{
		case 0:
			vector= core::vector3df(0,1,0);
		break;
		case 1:
			vector= core::vector3df(1,0,0);
		break;
		case 2:
			vector= core::vector3df(0,0,1);
		break;
		case 3:
			vector= core::vector3df(1,1,0);
		break;
		case 4:
			vector= core::vector3df(1,0,1);
		break;
		case 5:
			vector= core::vector3df(0,1,1);
		case 6:
			vector= core::vector3df(1,-1,0);
		break;
		case 7:
			vector= core::vector3df(-1,1,0);
		break;
		case 8:
			vector= core::vector3df(1,0,-1);
		break;
		case 9:
			vector= core::vector3df(-1,-1,-1);
		break;
		case 10:
			vector= core::vector3df(-1,-1,0);
		break;
		case 11:
			vector= core::vector3df(-1,0,-1);
		break;
		}
	*/
	vector.X=((rand() %20))-10;
	vector.Y=((rand() %20))-10;
	vector.Z=((rand() %20))-10;
	vector.normalize();
	return vector;


}

core::vector2df Stagehand_ex::randomposition()
{
DOVER:
		float height= ((rand()%40)*2);
		float X=((rand()%40)*2);
		X-=40;
		height-=40;
		float asine=asin(height/40);
		float cosine=cos(asine);
		if (X>40*cosine||X<-40*cosine)
		{
			goto DOVER;
		}
		float Y=height;


		return core::vector2df(X,Y);







}

void Stagehand_ex::createfireball(core::vector3df position, core::vector3df velocity)
{

int point=findemptyspot();
if (point!=-1)
{
	m_sound->play2D("Sound/laser2.wav",false);
	scene::IBillboardSceneNode *node=m_smgr->addBillboardSceneNode(0,core::dimension2d<f32>(5,5));
	node->setMaterialTexture(0,m_fireballsequence[0]);
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL );
			node->setColor(video::SColor(0,255,50,50));
	scene::ISceneNodeAnimator *anim= m_smgr->createTextureAnimator(m_fireballsequence,50,true);
	node->addAnimator(anim);
	m_array_ptr[point]= new Fireball(node,position,velocity,this);





}


}

void Stagehand_ex::burnplayer()
{


scene::IParticleSystemSceneNode *flare= m_smgr->addParticleSystemSceneNode(true,m_array_ptr[0]->Getnode(),-1,core::vector3df(0,0,1));
//generate flare particle emitter and attach it
//scene::IParticleEmitter *em= flare->createPointEmitter(core::vector3df(0,0,3),5,10,video::SColor(0,200,200,255),video::SColor(0,255,255,255),2000,4000,10);
//scene::IParticleEmitter *em= flare->createSphereEmitter(core::vector3df(0,0,1),0.5,core::vector3df(0,0,3));
        scene::IParticleEmitter* em = flare->createBoxEmitter(
                core::aabbox3d<f32>(-3,-3,-3,3,3,3), 

                core::vector3df(0.0f,0.00f,0.03f),0 
               ,15,   
			 video::SColor (0,255,100,0),
			 video::SColor (0,255,0,0),      
                300,300,3,                         
                core::dimension2df(0.2f,0.2f),         
                core::dimension2df(0.4f,0.4f));        

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

	



}

void Stagehand_ex::createcrystal (core::vector3df position)
{
int point=findemptyspot();

if (point!=-1)
{

	scene::IMesh *mesh=m_smgr->getMesh("Mesh/crystal.obj");
	scene::IMeshSceneNode *meshnode=m_smgr->addMeshSceneNode(mesh);
	meshnode->setMaterialTexture(0,m_driver->getTexture("Mesh/crystaltexture.tga"));
	meshnode->setMaterialFlag(video::EMF_LIGHTING,false);
	//meshnode->setScale(core::vector3df(2,2,2));
	m_array_ptr[point]=new Crystal(meshnode,position,this);
		core::vector3df rotation=randomvector();
       scene::ISceneNodeAnimator* anim = m_smgr->createRotationAnimator (rotation);
			meshnode->addAnimator(anim);
		anim->drop();
		scene::IBillboardSceneNode *node=m_smgr->addBillboardSceneNode(meshnode,core::dimension2d<f32> (3,3),core::vector3df(0,0,0));
		node->setMaterialTexture(0,m_driver->getTexture("Resources/spark.tga"));
		node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);


}


}

void Stagehand_ex::Setplayermesh(int meshnumber)
{

	scene::IMeshSceneNode *meshnode=(scene::IMeshSceneNode *)m_array_ptr[0]->Getnode();
	m_fadenode= m_smgr->addMeshSceneNode(meshnode->getMesh(),0,-1,meshnode->getPosition());

	m_fadenode->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
	m_fadenode->setMaterialTexture(0,meshnode->getMaterial(0).getTexture(0));
	m_fadenode->setScale(core::vector3df(0.80,0.80,0.80));
	*m_pcinematic=128;
	switch (meshnumber)
	{

	case 0:
	meshnode->setMesh(m_smgr->getMesh("Mesh/SWORDSMAN.obj"));
	meshnode->setMaterialTexture(0,m_driver->getTexture("Mesh/swordsmantexture.tga"));
	break;

	case 1:
	meshnode->setMesh(m_smgr->getMesh("Mesh/SWORDSMAN2.obj"));
	meshnode->setMaterialTexture(0,m_driver->getTexture("Mesh/swordsman2texture.tga"));
	break;

	case 2:
	meshnode->setMesh(m_smgr->getMesh("Mesh/SWORDSMAN3.obj"));
	meshnode->setMaterialTexture(0,m_driver->getTexture("Mesh/swordsman3texture.tga"));
	break;
	}
	//meshnode->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
}

void Stagehand_ex::createlaser(core::vector3df position, core::vector3df rotation)
{

int point=findemptyspot();

if (point!=-1)
{
	scene::IBillboardSceneNode *node=m_smgr->addBillboardSceneNode(0,core::dimension2d<f32>(3,3));
	node->setMaterialTexture(0,m_driver->getTexture("Resources/spark.tga"));
				node->setColor(video::SColor(0,255,222,0));
	
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL );
	/*

	scene::IMesh *mesh=m_smgr->getMesh("Mesh/laserbeam.obj");
	scene::IMeshSceneNode *meshnode=m_smgr->addMeshSceneNode(mesh);
	meshnode->setMaterialTexture(0,m_driver->getTexture("Resources/spark.tga"));
	meshnode->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);
	meshnode->setMaterialFlag(video::EMF_FRONT_FACE_CULLING,false);
	meshnode->setMaterialFlag(video::EMF_LIGHTING,false);
	meshnode->setScale(core::vector3df(2,2,2));
	meshnode->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
	*/
	m_array_ptr[point]=new Laser(position,rotation,node,this);


}

}

void Stagehand_ex::setbossbar(bool enabled)
{
m_bbossbar=enabled;
}

void Stagehand_ex::setgamewin()
{
*pstate=s_win;
}

Actor * Stagehand_ex::createclaw(core::vector3df position, bool righty)
{
	int point=findemptyspot();
	if (point!=-1)
	{
	scene::IMesh *mesh=m_smgr->getMesh("Mesh/claw.obj");
	scene::IMeshSceneNode *meshnode=m_smgr->addMeshSceneNode(mesh);
	meshnode->setPosition(position);
	meshnode->setMaterialTexture(0,m_driver->getTexture("Mesh/clawtexture.tga"));



	m_array_ptr[point]= new Claw(meshnode,position,this,righty);
	return m_array_ptr[point];

	}

return NULL;

}

void Stagehand_ex::cinematic(int shift)
{
	shift--;
	if (shift>2)
	{
	scene::IMeshSceneNode *meshnode=(scene::IMeshSceneNode *)m_array_ptr[0]->Getnode();
	//m_smgr->getMeshManipulator()->setVertexColorAlpha(meshnode->getMesh(),shift);
	m_smgr->getMeshManipulator()->setVertexColorAlpha(m_fadenode->getMesh(),shift);

	}
	else
	{

	m_smgr->getRootSceneNode()->removeChild(m_fadenode);
	scene::IMeshSceneNode *meshnode=(scene::IMeshSceneNode *)m_array_ptr[0]->Getnode();
	meshnode->setMaterialType(video::EMT_SOLID);
}

};