/*!
*  \file  ShipPlayer.h
*  \brief Ce fichier contient la déclaration de la classe ShipPlayer. C'est la classe qui gère les vaisseaux du joueur
*/
#ifndef __SHIP_PLAYER_H__
#define __SHIP_PLAYER_H__

#include <sstream>
#include <Ogre.h>
#include "ShipAbstract.h"
#include "MeshLoader.h"
#include "CameraFixeAbstract.h"
#include "CameraFixe.h"
#include "CameraFixeTarget.h"
#include "ViewportLoader.h"
#include "PlayerControls.h"
#include "GestSceneManager.h"

/*!
* \class ShipPlayer
* \brief Classe gérant les vaiseaux du joueur
*   Comporte un attribut Ogre::entity qui correspond à un unique mesh déplacable
*   Comporte également une fonction getNode qui permet de récupèrer le SceneNode de l'objet et donc de le positionner dans le graphe de scene (c'est via celui que l'on récupere la position orientation de l'objet.
*/
class ShipPlayer : /*public ObjectRoot, */public ShipAbstract
{
	private:
       	/*!
         * \brief Noeud cible
        */
        Ogre::SceneNode * nodeCameraTarget;
       	/*!
         * \brief Noeud pour la caméra à la première personne
        */
        Ogre::SceneNode * nodeCameraFirstPerson;
       	/*!
         * \brief Noeud pour la caméra extérieure fixe
        */
        Ogre::SceneNode * nodeCameraExterieureFixe;
		/*!
		*  \brief Type de la caméra utilisé
		*/
		CameraFixeAbstract::CameraType typeCamera;
		/*!
		*  \brief Pointeur sur la caméra utilisée
		*/
		CameraFixeAbstract * gestCamera;
		/*!
		*  \brief Id du viewport
		*/
		int idViewport;
	public:
		/*!
		 * \brief Construction
		*/
		ShipPlayer(PlayerControls * pControl);
		/*!
		 * \brief Destructeur
		*/
		~ShipPlayer(void);

		/*!
		 * \brief Update la position en fonction de la position actuelle, de la vitesse et de l'acceleration
		 * Méthode virtuelle pure
		*/
		void updatePosition(void);

		/*!
		 * \brief Active la premiere caméra
		 * \param type Type de caméra
		*/
		void initCamera(CameraFixeAbstract::CameraType type);

		/*!
		 * \brief Change de caméra
		 * \param type Type de caméra
		*/
		void changeCamera(CameraFixeAbstract::CameraType type);

        /*!
         * \brief permet de réagir aux évènement sur le clavier en utilisant PlayerControls
         */
        void keyPressed(PlayerControls::Controls key);

		/*!
         * \brief permet de réagir aux évènement sur la souris en utilisant PlayerControls
         */
        void mouseMoved(Ogre::Vector3 mouseVec);

        //getter/setter


		/*!
		 * \brief [Getter] Récupère le noeud de la caméra à la première personne
		 * \return Noeud de la caméra
		*/
		Ogre::SceneNode * getNodeCameraTarget(void)
		{
			return this->nodeCameraTarget;
		}
		/*!
		 * \brief [Getter] Récupère le noeud de la caméra à la première personne
		 * \return Noeud de la caméra
		*/
		Ogre::SceneNode * getNodeCameraFirstPerson(void)
		{
			return this->nodeCameraFirstPerson;
		}
		/*!
		 * \brief [Getter] Récupère le noeud de la caméra extérieure fixe
		 * \return Noeud de la caméra
		*/
		Ogre::SceneNode * getNodeCameraExterieureFixe(void)
		{
			return this->nodeCameraExterieureFixe;
		}
};

#endif // __SHIP_PLAYER_H__
