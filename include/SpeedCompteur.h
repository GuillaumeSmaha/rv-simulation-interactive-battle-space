/*!
*  \file  SpeedCompteur.h
*  \brief Ce fichier contient la déclaration de la classe SpeedCompteur. Permet d'afficher pour un joueur un compteur de vitesse
*/
#ifndef __SPEED_COMPTEUR_H__
#define __SPEED_COMPTEUR_H__

#include <Ogre.h>
#include "Utils.h"
#include "ObjectRoot.h"
#include "ShipAbstract.h"
#include "ListenerTime.h"

/*!
* \class SpeedCompteur
* \brief Classe Permet d'afficher pour un joueur un compteur de vitesse
*/
class SpeedCompteur : public ObjectRoot
{



private:
    /*!
     * \brief Le vaiseau auquel est lié le compteur
    */
    ShipAbstract * ship;
    /*!
     * \brief Nom de l'objet de la jauge
    */
    Ogre::String panelJaugeName;
    
    
public:
    /*!
     * \brief Constructeur
     * \param ship Le vaisseau contenant la vitesse de celui-ci
     * \param listenerTime Pointeur sur le controleur de frame régulé
    */
    SpeedCompteur(ShipAbstract * ship, ListenerTime * listenerTime);
    /*!
     * \brief Destructeur
    */
    ~SpeedCompteur();


private:
    /*!
     * \brief La fonction appelé régulièrement pour mettre à jour la vitesse
    */
    void miseAJour(void *);
};

#endif //__SPEED_COMPTEUR_H__
