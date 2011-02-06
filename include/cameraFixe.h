#ifndef __CAMERAFIXE_H__
#define __CAMERAFIXE_H__

#include "camera.h"

/*!
 **  \file  camera.h
 **  \brief Ce fichier contient la déclaration de la classe Camera. C'est la classe gérant une caméra fixe
 **/

/**
    \class CameraFixe
    \brief Classe permetttant de gérer une caméra fixe

**/

class CameraFixe : public Camera {
public:
    CameraFixe(Ogre::Camera * camera, Ogre::SceneManager * sceneMgr);
    int init_camera();
};

#endif //__CAMERAFIXE_H__
