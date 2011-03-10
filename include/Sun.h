#ifndef _SUN_H_
#define _SUN_H_

#include <Ogre.h>
#include "ClassRoot.h"

using namespace Ogre;

class Sun : public ClassRoot
{
public:
	Sun(Vector3 LightPosition, Camera* camera, SceneManager* SceneMgr);
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
	Camera*       mCamera;
	ColourValue   mColour;
	SceneNode*    mNode;
	BillboardSet* mHaloSet;
	BillboardSet* mBurstSet;
	Vector3       mLightPosition;
};

#endif