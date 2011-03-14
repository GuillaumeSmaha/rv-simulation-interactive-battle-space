/*!
*  \file  ShipPlayer.h
*  \brief Ce fichier contient la déclaration de la classe ShipPlayer. C'est la classe qui gère les vaisseaux du joueur
*/
#ifndef __SHIP_PLAYER_H__
#define __SHIP_PLAYER_H__

#include <sstream>
#include <Ogre.h>
#include "MeshLoader.h"
#include "CameraAbstract.h"
#include "CameraLibre.h"
#include "CameraFixeTarget.h"
#include "ViewportLoader.h"
#include "PlayerControls.h"
#include "GestSceneManager.h"
#include "GestSound.h"
#include "ShipAbstract.h"
#include "Compteur.h"
#include "ListenerTime.h"
#include "Message.h"

#define limit 50000

/*!
* \class ShipPlayer
* \brief Classe gérant les vaiseaux du joueur
*   Comporte un attribut Ogre::entity qui correspond à un unique mesh déplacable
*   Comporte également une fonction getNode qui permet de récupèrer le SceneNode de l'objet et donc de le positionner dans le graphe de scene (c'est via celui que l'on récupere la position orientation de l'objet.
*/
class ShipPlayer : public ShipAbstract
{
	private:
        int shootDelay;
	       /*!
		 * \brief Point de destination (utilisé pour calculé la distance entre le vaisseau et sa destination)
		*/
        Ogre::Vector3 destination;
        /*!
		 * \brief Vitesse du vaisseau
		*/
        Ogre::Real speed;
        /*!
		 * \brief Nombre de frames pour la rotation
		*/
        Ogre::Real mRotFrames;
        /*!
		 * \brief Orientation courante (avant le début de la rotation)
		*/
        Ogre::Quaternion mOrientSrc;
        /*!
		 * \brief Orientation future (après la rotation)
		*/
        Ogre::Quaternion mOrientDest;
        /*!
		 * \brief Avancement de la rotation
		*/
        Ogre::Real mRotProgress;
        /*!
		 * \brief "Pas" pour la rotation
		*/
        Ogre::Real mRotFactor;
        /*!
		 * \brief Vaisseau en rotation ?
		*/
        bool mRotating;
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
		 * \brief Noeud pour l'emetteur de vitesse lumière
		 */
		Ogre::SceneNode * nodeLightSpeed;
		/*!
		*  \brief Type de la caméra utilisé
		*/
		CameraAbstract::CameraType typeCamera;
		/*!
		*  \brief Pointeur sur la caméra utilisée
		*/
		CameraAbstract * gestCamera;
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
		 * \brief Indique si la touche vitesse lumière est appuyée
		 */
		//bool lightSpeedPressed;
        /*!
         * \brief Controleur de vaiseau
        */
        PlayerControls * playerControl;
        /*!
         * \brief panneau comprend le compteur de vitesse et de vie associé au vaisseau
        */
        Compteur * compteur;

        /*!
         * \brief Particules indiquant l'ennemi
         */
        Ogre::ParticleEmitter * emitter;
        /*!
         * \brief Particules indiquant la station
         */
        Ogre::ParticleEmitter * emitterFriend;
        /*!
		*  \brief Pilote automatique
		*/
        bool isAutoPiloted;

		/*!
		 * \brief Système de particules vitesse lumière
		 */
		Ogre::ParticleSystem * lightSpeedSystem;

	public:
		/*!
		 * \brief Construction
		*/
		ShipPlayer(PlayerControls * pControl, ListenerTime * listenerTime);
		/*!
		 * \brief Destructeur
		*/
		~ShipPlayer(void);

		/*!
		 * \brief Update la position en fonction de la position actuelle, de la vitesse et de l'acceleration
		 * Méthode virtuelle pure
		*/
		void updatePosition(void);

        /*
         * \brief regarde si le vaisseau est trop loin du champs de bataille et lui fait perdre de la vie si c'est le cas
         *
        */
        void check_out_of_battle(void);

		/*!
		 * \brief Active la premiere caméra
		 * \param type Type de caméra
		*/
		void initCamera(CameraAbstract::CameraType type);

		/*!
		 * \brief Change de caméra
		 * \param type Type de caméra
		*/
		void changeCamera(CameraAbstract::CameraType type);

		/*!
		 * \brief Change de caméra par la suivante
		*/
		void switchNextCamera(void);
		/*!
		 * \brief Change de caméra par la précédente
		*/
		void switchPrevCamera(void);

        /*!
		 * \brief Définit les particules des réacteurs et indiquant la direction
		*/
		void defineParticules(void);
		/*!
		 * \brief Oriente les particules vers le vaisseau ennemi et la station
		*/
        void updateParticules(void);

		/*!
		 * \brief Définit le système de vitesse lumière
		 */
		void defineLightSpeedSystem(void);
		/*!
		 * \brief Active la vitesse lumière
		 */
		void activateLightSpeed();
		/*!
		 * \brief envoi un laser
		*/
		void shootLaser(void);

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
		/*!
		 * \brief [Getter] Récupère le gestionnaire de caméra
		 * \return Gestionnaire de caméra
		*/
		CameraAbstract * getGestCamera(void)
		{
			return this->gestCamera;
		}
		/*!
		 * \brief Switch le pilote automatique
		 */
		 void switchAutopilote()
		 {
		     switchAutopilote(!this->isAutoPiloted);

		 }
		 void switchAutopilote(bool autopiloteActivated)
		 {
            this->isAutoPiloted = autopiloteActivated;
            if(this->isAutoPiloted)
            {
				Message* message = Message::getSingleton();
				message->afficher_message((CEGUI::utf8*)"AutoPilot",(CEGUI::utf8 *)"Pilote Automatique Activé !");
                this->speed = 60;
                this->mRotFrames = 120;
                this->destination = Ogre::Vector3(130,0,6000);
                mRotating = true;
                mRotFactor = 1;
                mRotProgress = 1;
			}
			else
			{
				Message* message = Message::getSingleton();
				message->afficher_message((CEGUI::utf8*)"AutoPilot",(CEGUI::utf8 *)"Pilote Automatique Désactivé !");
			}
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
		
		/*!
		 * \brief Calcule le facteur de rotation en fonction de la vitesse
		 * \param method Methode de calcul sélectionnée :
		 * 		method = 1 : Logarithme
		 * 		method = 2 : x^3
		 * \return Le facteur calculé
		*/
		Ogre::Real getFactorRotation(int method = 1);


	public:
		//Getter/Setter
		
		/*!
		 * \brief Déplacement l'objet dans le référentiel de l'objet
		 * \param x Déplacement de l'objet en x
		 * \param y Déplacement de l'objet en y
		 * \param z Déplacement de l'objet en z
		*/
		void moveRelative(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z);
		/*!
		 * \brief Déplacement l'objet dans le référentiel de l'objet
		 * \param vec Déplacement de l'objet selon le vecteur v
		*/
		void moveRelative(const Ogre::Vector3 &vec);
        /*!
         * \brief Rotation autour de l'axe direction de l'objet, permet donc de tourner
         * \param w un angle en radian
        */
		void rotateRollRelative(const Ogre::Radian w);

		/*!
         * \brief Rotation autour de la normale à la direction de l'objet, permet donc de tourner
         * \param w un angle en radian
        */
		void rotateYawRelative(const Ogre::Radian w);

        /*!
         * \brief Permet d'incliner le vaiseau vers le haut (angle positif) ou vers le bas (angle négatif)
         * /param w l'angle d'inclinaison
        */
        void goUp(const Ogre::Radian w);
		/*!
		 * \brief [Getter] Récupère l'orientation de l'objet
		 * \return Orientation de l'objet
		*/
        Ogre::Quaternion getOrientation(void);
		/*!
		 * \brief [Setter] Définit l'orientation de l'objet
		 * \param q Orientation de l'objet
		*/
		void setOrientation(const Ogre::Quaternion &q);
		/*!
		 * \brief [Setter] Définit l'orientation de l'objet
		 * \param x Orientation de l'objet sur l'axe x
		 * \param y Orientation de l'objet sur l'axe y
		 * \param z Orientation de l'objet sur l'axe z
		 * \param a Orientation
		*/
        void setOrientation(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z, const Ogre::Real a);

		/*!
		 * \brief [Getter] Récupère la position de l'objet
		 * \return Position de l'objet
		*/
        Ogre::Vector3 getPosition(void);
		/*!
		 * \brief [Setter] Définit la position de l'objet
		 * \param v Position de l'objet
		*/
        void setPosition(const Ogre::Vector3 &v);
		/*!
		 * \brief [Setter] Définit la position de l'objet
		 * \param x Position de l'objet en x
		 * \param y Position de l'objet en y
		 * \param z Position de l'objet en z
		*/
		void setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z);

};

#endif // __SHIP_PLAYER_H__
