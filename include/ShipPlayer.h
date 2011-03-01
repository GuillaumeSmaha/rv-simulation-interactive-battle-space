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
#include "GestSound.h"

/*!
* \class ShipPlayer
* \brief Classe gérant les vaiseaux du joueur
*   Comporte un attribut Ogre::entity qui correspond à un unique mesh déplacable
*   Comporte également une fonction getNode qui permet de récupèrer le SceneNode de l'objet et donc de le positionner dans le graphe de scene (c'est via celui que l'on récupere la position orientation de l'objet.
*/
class ShipPlayer : public ShipAbstract
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

		/*!
		*  \brief Indique si la touche d'accélération est appuyée
		*/
        bool accelerationPressed;
		/*!
		*  \brief Indique si la touche de freinage est appuyée
		*/
        bool brakePressed;
		/*!
		*  \brief Indique si la touche gauche est appuyée
		*/
        bool leftPressed;
		/*!
		*  \brief Indique si la touche droite est appuyée
		*/
        bool rightPressed;
		/*!
		*  \brief Indique si la touche haut est appuyée
		*/
        bool upPressed;
		/*!
		*  \brief Indique si la touche bas est appuyée
		*/
        bool downPressed;
        /*!
         * \brief Controleur de vaiseau
        */
        PlayerControls * playerControl; 


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
		 * \brief Change de caméra par la suivante
		*/
		void switchNextCamera(void);
		/*!
		 * \brief Change de caméra par la précédente
		*/
		void switchPrevCamera(void);


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

    private:
        /*!
         * \brief permet de réagir aux évènement sur le clavier en utilisant PlayerControls
         */
        void update_differente_acceleration(void);
        /*!
         * \brief Permet de réagir aux évènement sur le clavier en utilisant PlayerControls
         * \param key Touche du clavier
         */
        void keyPressed(PlayerControls::Controls key);
        /*!
         * \brief Permet de réagir aux évènement sur le clavier en utilisant PlayerControls
         * \param key Touche du clavier
         */
        void keyReleased(PlayerControls::Controls key);
		/*!
         * \brief Permet de réagir aux évènement sur la souris en utilisant PlayerControls
         * \param mouseVec Mouvement de la souris
         */
        void mouseMoved(Ogre::Vector3 mouseVec);

};

#endif // __SHIP_PLAYER_H__
