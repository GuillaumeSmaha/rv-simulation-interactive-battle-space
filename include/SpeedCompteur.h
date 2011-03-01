/*!
*  \file  SpeedCompteur.h
*  \brief Ce fichier contient la déclaration de la classe SpeedCompteur. Permet d'afficher pour un joueur un compteur de vitesse
*/
#ifndef __SPEED_COMPTEUR_H__
#define __SPEED_COMPTEUR_H__

#include <Ogre.h>
#include "ObjectRoot.h"
#include "ShipAbstract.h"
#include "ListenerTime.h"

/*!
* \class SpeedCompteur
* \brief Classe Permet d'afficher pour un joueur un compteur de vitesse
*/
class SpeedCompteur : public ObjectRoot
{

public:
    SpeedCompteur(ShipAbstract * ship, ListenerTime * listenerTime);
    ~SpeedCompteur();


private:
    /*!
     * \brief le vaiseau auquel est lié le compteur
    */
    ShipAbstract * ship;
    /*!
     * \brief La fonction appelé régulièrement pour mettre à jour la vitesse
    */
    void miseAJour(void *);
};

#endif //__SPEED_COMPTEUR_H__
