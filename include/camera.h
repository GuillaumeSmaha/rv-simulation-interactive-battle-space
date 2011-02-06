#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <OgreCamera.h>
#include <OgreSceneManager.h>

/*!
 **  \file  camera.h
 **  \brief Ce fichier contient la déclaration de la classe Camera. C'est la classe une classe abstraite qui permet d'utiliser différents types de caméras.
 **/

/**
    \class Camera
    \brief Classe abstraite entre le programme principale et la caméra effectivement utilisé. Elle ne peut donc pas être instancié directement

**/

class Camera {
public:

    virtual int init_camera() = 0;
    Ogre::Camera * get_camera(){
        return camera;
    }
protected:
    Ogre::Camera * camera;
    //la caméra ne peut travailler sans disposer du scene manager
    Ogre::SceneManager * sceneMgr;


};

#endif // __CAMERA_H__ 
