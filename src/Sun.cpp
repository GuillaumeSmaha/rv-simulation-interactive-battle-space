#include "Sun.h"

Sun::Sun(Vector3 LightPosition, SceneManager* SceneMgr)
{
	mSceneMgr      = SceneMgr;
	this->createSun();
	this->setLightPosition(LightPosition);
}

Sun::~Sun()
{
	mNode->detachObject(mHaloSet);
	mNode->detachObject(mBurstSet);
	mSceneMgr->destroyBillboardSet(mHaloSet);
	mSceneMgr->destroyBillboardSet(mBurstSet);
	/// TODO destroy mNode
} 

void Sun::createSun()
{
	Real LF_scale = 200000;

	// -----------------------------------------------------
	// We create 2 sets of billboards for the Sun
	// -----------------------------------------------------
	mHaloSet = mSceneMgr->createBillboardSet("halo");
	mHaloSet->setMaterialName("lensflare/halo");
	mHaloSet->setCullIndividually(true);
	mHaloSet->setQueryFlags(0);

	mBurstSet= mSceneMgr->createBillboardSet("burst");
	mBurstSet->setMaterialName("lensflare/burst");
	mBurstSet->setCullIndividually(true);
	mBurstSet->setQueryFlags(0);	

	// The node is located at the light source.
	mNode  = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	mNode->attachObject(mBurstSet);
	mNode->attachObject(mHaloSet);

	// -------------------------------
	// Creation of the Halo billboards
	// -------------------------------
	//Billboard* LF_Halo1 = mHaloSet->createBillboard(0,0,0);
	//LF_Halo1->setDimensions(LF_scale*0.5,LF_scale*0.5);
	//Billboard* LF_Halo2 = mHaloSet->createBillboard(0,0,0);
	//LF_Halo2->setDimensions(LF_scale,LF_scale);
	//Billboard* LF_Halo3 = mHaloSet->createBillboard(0,0,0);
	//LF_Halo3->setDimensions(LF_scale*0.025,LF_scale*0.025);


	// -------------------------------
	// Creation of the "Burst" billboards
	// -------------------------------
	Billboard* LF_Burst1 = mBurstSet->createBillboard(0,0,0);
	LF_Burst1->setDimensions(LF_scale*0.125,LF_scale*0.125);
	Billboard* LF_Burst2 = mBurstSet->createBillboard(0,0,0);
	LF_Burst2->setDimensions(LF_scale*0.5,LF_scale*0.5);
	Billboard* LF_Burst3 = mBurstSet->createBillboard(0,0,0);
	LF_Burst3->setDimensions(LF_scale*0.25,LF_scale*0.25);

} 

void Sun::update(const Ogre::FrameEvent &evt)
{
	int nbCams = GestSceneManager::getCamCount();

	for (int i = 0; i < nbCams; i++)
	{
		Camera *currentCam = GestSceneManager::getCamera(i)->getCamera();

		// If the Light is out of the Camera field Of View, the Sun is hidden.
		if (!currentCam->isVisible(mLightPosition)) 
		{
			mHaloSet->setVisible(false);
			mBurstSet->setVisible(false);
			return;
		}
		else
		{
			mHaloSet->setVisible(true);
			mBurstSet->setVisible(true);
		}

		Real LightDistance  = mLightPosition.distance(currentCam->getPosition());
		Vector3 CameraVect  = currentCam->getDirection(); // normalized vector (length 1)

		CameraVect = currentCam->getPosition() + (LightDistance * CameraVect);


		// The Sun effect takes place along this vector.
		Vector3 LFvect = (CameraVect - mLightPosition);
		//LFvect += Vector3(-64,-64,0);  // sprite dimension (to be adjusted, but not necessary)

		// The different sprites are placed along this line.
		//mHaloSet->getBillboard(0)->setPosition( LFvect*0.500);
		//mHaloSet->getBillboard(1)->setPosition( LFvect*0.125);
		//mHaloSet->getBillboard(2)->setPosition(-LFvect*0.250);

		mBurstSet->getBillboard(0)->setPosition( LFvect*0.333);
		mBurstSet->getBillboard(1)->setPosition(-LFvect*0.500);
		mBurstSet->getBillboard(2)->setPosition(-LFvect*0.180);
	}
}

/* ------------------------------------------------------------------------- */
/// This function updates the light source position. 
/** This function can be used if the light source is moving.*/
/* ------------------------------------------------------------------------- */
void Sun::setLightPosition(Vector3 pos)
{
	mLightPosition = pos;
	mNode->setPosition(mLightPosition); 
}


/* ------------------------------------------------------------------------- */
/// This function changes the colour of the burst. 
/* ------------------------------------------------------------------------- */
void Sun::setBurstColour(ColourValue color)
{
	mBurstSet->getBillboard(0)->setColour(color);
	mBurstSet->getBillboard(1)->setColour(color*0.8);
	mBurstSet->getBillboard(2)->setColour(color*0.6);
} 

/* ------------------------------------------------------------------------- */
/// This function changes the colour of the halos. 
/* ------------------------------------------------------------------------- */
void Sun::setHaloColour(ColourValue color)
{ 
	//mHaloSet->getBillboard(0)->setColour(color*0.8);
	//mHaloSet->getBillboard(1)->setColour(color*0.6);
	//mHaloSet->getBillboard(2)->setColour(color);
}
