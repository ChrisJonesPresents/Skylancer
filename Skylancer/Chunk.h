#include <irrlicht.h>
#include "Actor.h"
#include "Stagehand.h"
#ifndef CHUNK
#define CHUNK

class Chunk : public Actor
{
protected:
	Stagehand *m_pstagehand;

public:

	Chunk (core::vector3df position,core::vector3df velocity, scene::ISceneNode *node,Stagehand *stagehand);

	void update();











};
#endif