#include "Planet.h"

using namespace Ogre;

int Planet::planetNumber = 0;

Planet::Planet(void) : type(MeshLoader::PLANET), hasAtmosphere(false), mInnerRadius(1000)
{
	//this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET);
    //this->getNode()->setPosition(150, 100, -100);

	//updateCalculations();

	this->planetNode = MeshLoader::getSingleton()->getNode(MeshLoader::PLANET);

	createSpheres("Planet" + planetNumber++);

	this->setMaterialGroundFromSpace("Earth");

}

Planet::Planet(Ogre::Real radius, bool hasAtmo)	: hasAtmosphere(hasAtmo), mInnerRadius(radius)
{
	if (this->hasAtmosphere)
	{
		mKr = 0.000043f;
		mKm = 0.00668;
		mESun = 40.0f;
		mG = -0.990f;
		mExposure = 2.0f;
		mWaveLengths = Vector3(0.650f,0.570f,0.475f);
		mScaleDepth = 0.25f;

		updateCalculations();
	}

	this->planetNode = MeshLoader::getSingleton()->getNode(MeshLoader::PLANET);
	
	Ogre::String planetMaterialName = "planet1";
	if (this->hasAtmosphere)
	{
		createSpheres("Planet" + planetNumber, "Atmo" + planetNumber);
		planetMaterialName += "_Atmo";

		this->setMaterialSkyFromSpace("SkyFromSpace");
	}
	else
	{
		createSpheres("Planet" + planetNumber);
	}
	planetNumber++;

	//Utils::log(planetMaterialName);
	this->setMaterialGroundFromSpace(planetMaterialName);
}

Planet::Planet(Ogre::Real radius, Ogre::int16 _type, bool hasAtmo)	: type(_type), hasAtmosphere(hasAtmo), mInnerRadius(radius)
{
	if (this->hasAtmosphere)
	{
		mKr = 0.000043f;
		mKm = 0.00668;
		mESun = 40.0f;
		mG = -0.990f;
		mExposure = 2.0f;
		mWaveLengths = Vector3(0.650f,0.570f,0.475f);
		mScaleDepth = 0.25f;

		updateCalculations();
	}

	switch(type)
	{
		case 1 : this->planetNode = MeshLoader::getSingleton()->getNode(MeshLoader::PLANET); break;
		case 2 : this->planetNode = MeshLoader::getSingleton()->getNode(MeshLoader::PLANET2); break;
		case 3 : this->planetNode = MeshLoader::getSingleton()->getNode(MeshLoader::PLANET3); break;
		case 4 : this->planetNode = MeshLoader::getSingleton()->getNode(MeshLoader::PLANET4); break;
		case 5 : this->planetNode = MeshLoader::getSingleton()->getNode(MeshLoader::PLANET5); break;
		case 6 : this->planetNode = MeshLoader::getSingleton()->getNode(MeshLoader::PLANET6); break;
		case 7 : this->planetNode = MeshLoader::getSingleton()->getNode(MeshLoader::PLANET7); break;
		case 8 : this->planetNode = MeshLoader::getSingleton()->getNode(MeshLoader::PLANET8); break;
	}

	Ogre::String planetMaterialName = "planet" + Ogre::StringConverter::toString(type);
	if (this->hasAtmosphere)
	{
		createSpheres("Planet" + planetNumber, "Atmo" + planetNumber);
		planetMaterialName += "_Atmo";

		this->setMaterialSkyFromSpace("SkyFromSpace");
	}
	else
	{
		createSpheres("Planet" + planetNumber);
	}
	planetNumber++;

	this->setMaterialGroundFromSpace(planetMaterialName);
}

Planet::~Planet(void)
{
	planetNode->detachAllObjects();

	SceneManager* scnMgr = GestSceneManager::getSingleton()->getSceneManager();

	scnMgr->destroyEntity(innerSphere);

	if (this->hasAtmosphere)
	{
		scnMgr->destroyEntity(outerSphere);
	}

	scnMgr->destroySceneNode(planetNode->getName());
}

void Planet::update()
{
	// Mise � jour de la position de la plan�te
	updatePosition();

	// Mise � jour n�cessaire seulement si une atmosph�re est pr�sente
	if (this->hasAtmosphere == false)
	{
		return;
	}

	GestSceneManager* scnMgr = GestSceneManager::getSingleton();

	// On met � jour l'affichage de la plan�te pour toutes les cam�ras
	for (int i = 0; i < scnMgr->getCamCount(); i++)
	{
		Camera* currentCamera = scnMgr->getCamera(i)->getCamera();

		Ogre::Real cameraHeight = (planetNode->getPosition() - currentCamera->getPosition()).length();
		Ogre::Real cameraHeightSqr = cameraHeight * cameraHeight;

		GpuProgramParametersSharedPtr pParams;
		Ogre::Pass* pPass;

		if (cameraHeight >= mOuterRadius)
		{
			//mInnerSphere->setMaterialName("Moon");
			
			// GroundFromSpace
			pPass = mGroundFromSpace->getTechnique(0)->getPass(1);
			pParams = pPass->getVertexProgramParameters();
			
			pParams->setNamedConstant("fvInvWavelengths", mInvWaveLengthsPow4);
			pParams->setNamedConstant("fCameraHeightSqr", cameraHeightSqr);
			pParams->setNamedConstant("fInnerRadius", mInnerRadius);
			pParams->setNamedConstant("fOuterRadius", mOuterRadius);
			pParams->setNamedConstant("fOuterRadiusSqr", mOuterRadiusSqr);
			pParams->setNamedConstant("fKr4PI", mKr4PI);
			pParams->setNamedConstant("fKm4PI", mKm4PI);
			pParams->setNamedConstant("fKrESun", mKrESun);
			pParams->setNamedConstant("fKmESun", mKmESun);
			pParams->setNamedConstant("fScale", mScale);
			pParams->setNamedConstant("fScaleOverScaleDepth", mScaleOverScaleDepth);

			pParams = pPass->getFragmentProgramParameters();
			pParams->setNamedConstant("fExposure", mExposure);
			
			// SkyFromSpace
			pPass = mSkyFromSpace->getTechnique(0)->getPass(0);
			pParams = pPass->getVertexProgramParameters();

			pParams->setNamedConstant("fvInvWavelengths",mInvWaveLengthsPow4);
			pParams->setNamedConstant("fCameraHeightSqr",cameraHeightSqr);
			pParams->setNamedConstant("fInnerRadius",mInnerRadius);
			pParams->setNamedConstant("fOuterRadius",mOuterRadius);
			pParams->setNamedConstant("fOuterRadiusSqr",mOuterRadiusSqr);
			pParams->setNamedConstant("fKr4PI",mKr4PI);
			pParams->setNamedConstant("fKm4PI",mKm4PI);
			pParams->setNamedConstant("fKrESun",mKrESun);
			pParams->setNamedConstant("fKmESun",mKmESun);
			pParams->setNamedConstant("fScale",mScale);
			pParams->setNamedConstant("fScaleOverScaleDepth",mScaleOverScaleDepth);

			pParams = pPass->getFragmentProgramParameters();
			pParams->setNamedConstant("fExposure",mExposure);
		}
	}
}

void Planet::updatePosition(void)
{
}


//Getter/Setter


void Planet::setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z)
{
    this->getNode()->setPosition(x, y, z);
}

void Planet::setScale(Ogre::Real x, Ogre::Real y, Ogre::Real z)
{
	this->getNode()->setScale(x, y, z);
}


//Private method


void Planet::createSpheres(const Ogre::String& innerName, const Ogre::String& outerName)
{
	SceneManager* scnMgr = GestSceneManager::getSingleton()->getSceneManager();

	MeshLoader::getSingleton()->createSphere(innerName, mInnerRadius, 128, 128);
	innerSphere = scnMgr->createEntity(innerName + "_Ent", innerName);
	planetNode->attachObject(innerSphere);

	
	if (hasAtmosphere)
	{
		MeshLoader::getSingleton()->createSphere(outerName, mOuterRadius, 128, 128);
		outerSphere = scnMgr->createEntity(outerName + "_Ent", outerName);
		planetNode->attachObject(outerSphere);
	}
}

void Planet::updateCalculations()
{
	mInvWaveLengthsPow4.x = 1.0f / Math::Pow(mWaveLengths.x,4.0f);
	mInvWaveLengthsPow4.y = 1.0f / Math::Pow(mWaveLengths.y,4.0f);
	mInvWaveLengthsPow4.z = 1.0f / Math::Pow(mWaveLengths.z,4.0f);

	// This must stay this way as some of the constants
	// as the depth scale function relies on this.
	mOuterRadius = mInnerRadius * 1.025;

	mInnerRadiusSqr = mInnerRadius * mInnerRadius;
	mOuterRadiusSqr = mOuterRadius * mOuterRadius;

	mKr4PI = mKr * 4.0f * PI;
	mKm4PI = mKm * 4.0f * PI;

	mKrESun = mKr * mESun;
	mKmESun = mKm * mESun;

	mScale = 1.0f / (mOuterRadius - mInnerRadius);
	mScaleOverScaleDepth = mScale / mScaleDepth;

	mG2 = mG * mG;
}
