/*!
 **  \file  OrbitCamera.h
 **  \brief Contient la déclaration de la classe gérant une caméra oribatale
 **/
#ifndef __ORBITCAMERA_H__
#define __ORBITCAMERA_H__

#include <Ogre.h>
#include <OISMouse.h>

/*!
 * \class OrbitCamera
 * \brief Classe permetttant de gérer une caméra orbitale
 */
class OrbitCamera
{
private:
	Ogre::Camera *camera;
	Ogre::Viewport *viewport;
	Ogre::SceneNode *targetNode;
	Ogre::SceneManager *sceneMgr;

	bool orbiting;
	bool zooming;

public:
	OrbitCamera(Ogre::SceneManager *sceneMgr, Ogre::SceneNode *target);
	~OrbitCamera();
	void updateMovement(const OIS::MouseEvent &evt);
	
	Ogre::Camera *getCamera(void);
	bool getOrbiting(void);
	void setOrbiting(bool orbiting);
	bool getZooming(void);
	void setZooming(bool zooming);
	
};

#endif // __ORBITCAMERA_H__
