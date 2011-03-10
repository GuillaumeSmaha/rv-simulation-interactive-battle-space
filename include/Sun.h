#ifndef _SUN_H_
#define _SUN_H_

#include <Ogre.h>
#include "ClassRoot.h"
#include "GestSceneManager.h"

using namespace Ogre;

class Sun : public ClassRoot
{
public:
	Sun(Vector3 LightPosition, SceneManager* SceneMgr);
	virtual ~Sun();
	void createSun();
	void update(const Ogre::FrameEvent &evt);
	void setLightPosition(Vector3 pos);
	void setHaloColour(ColourValue color);
	void setBurstColour(ColourValue color);
	
	SceneNode * getNode() 
	{
		return mNode;
	}


protected:
	SceneManager* mSceneMgr;
	ColourValue   mColour;
	SceneNode*    mNode;
	BillboardSet* mHaloSet;
	BillboardSet* mBurstSet;
	Vector3       mLightPosition;
};

#endif