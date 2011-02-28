/*!
*  \file  PlayerControls.h
*  \brief Ce fichier contient la déclaration de la classe PlayerControls. 
*/
#ifndef __PLAYER_CONTROLS_H__
#define __PLAYER_CONTROLS_H__

#include <vector>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include "Signal.h"
#include "ListenerMouse.h"
#include "ObjectRoot.h"
#include "ListenerKeyboard.h"

class ListenerKeyboard;
class ListenerMouse;

/*!
* \class PlayerControls
* \brief Class Permettant de gérer le contrôle de manière "haut niveau" du joueur au d'utiliser directement les évènements de base de Ogre
* Permettra par la suite de facilemet modifier les contrôles pour chaque joueur (enregistrés dans un fichier par exemple)
* Par la suite il faudra donc écouter les évènements (signaux) de PlayerControls et non plus directement de mouse et keyboard
*/
class PlayerControls: public ObjectRoot
{
    public:
		/// Définit les différents types de contrôles
		enum Controls
		{
			NONE = 0,
			SHOOT1 = 1,
			SHOOT2 = 2,
			ACCELERATION = 3,
			BRAKE = 4,
			LEFT = 5,
			RIGHT = 6,
            UP = 7,
            DOWN = 8,
            OPEN_MENU= 9,
			QUIT = 10,
            SWITCH_NEXT_CAMERA = 11,
            SWITCH_PREV_CAMERA = 12
		};
		
         /*!
		 * \brief Nombre maximum de touche clavier dans OIS
		 */
		static int maxOISKeyControl;
         /*!
		 * \brief Nombre maximum de touche souris dans OIS
		 */
		static int maxOISMouseControl;

        ListenerKeyboard * keyboard;
        ListenerMouse * mouse;


	private:
         /*!
		 * \brief Lie une touche à un contrôle (déplacement, tir). 
         * par exemple listKeyControl[25]=SHOOT1 position la touche repéré par le code 25 sur l'action SHOOT1
		 */
        std::vector<PlayerControls::Controls> listKeyControl;
         /*!
		 * \brief Lie un bouton de souris à un contrôle.
		 */
        std::vector<PlayerControls::Controls> listMouseControl;
        
	public:
		/*!
		 * \brief Emet un dispatche lorsqu'une touche est préssée  Signal(PlayerControls::Controls key)
		 */
        Signal<PlayerControls::Controls> signalKeyPressed;
        /*!
		 * \brief Emet un dispatche lorsqu'une touche est relâchée  Signal(PlayerControls::Controls key)
		 */
        Signal<PlayerControls::Controls> signalKeyReleased;
         /*!
		 * \brief Emet un dispatche lorsque la souris est bougée  Signal(Ogre::Vector3)
		 */
        Signal<Ogre::Vector3> signalMouseMoved;
	
        /*!
         * \brief Permet d'arréter de réagir aux listeners 
         * Utile lorsque le menu est activé.
        */
        void suspendre_ecoute();
        /*!
         * \brief Permet de rependre l'écoute des listeneurs
         * Appelé aprés que le menu ai été fermé.
        */
        void reprendre_ecoute();

    public:
        /*!
         * \brief Constructor
         * \param mouse MouseListener
         * \param keyboard KeyboardListener
         */
        PlayerControls(ListenerMouse * mouse, ListenerKeyboard * keyboard);
        /*!
         * \brief Destructor
         */
        virtual ~PlayerControls();
        
        /*!
         * \brief Met à zéro les controllers de touche clavier et souris
         */
        void resetControls(void);        
        /*!
         * \brief Définit une touche du clavier pour une action donnée
         * \param keyControl Action à effectuer
         * \param key Touche correspondante
         */
        void setKeyControl(const PlayerControls::Controls keyControl, const OIS::KeyCode key);
        /*!
         * \brief Définit une touche de la souris pour une action donnée
         * \param keyControl Action à effectuer
         * \param mouseId Touche correspondante
         */
        void setMouseControl(const PlayerControls::Controls keyControl, const OIS::MouseButtonID mouseId);
        
    private:
         /*!
		 * \brief Reçoit un dispatche lorsqu'une touche du clavier est pressée et le transmet à signalKeyPressed
		 * \param evt Event OIS
		 */
        void keyboardPressed(const OIS::KeyEvent &evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche du clavier est relâchée et le transmet à signalKeyReleased
		 * \param evt Event OIS
		 */
        void keyboardReleased(const OIS::KeyEvent &evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'un la souris est bougée et le transmet à signalMouseMoved
		 * \param vect Vector3(X, Y, Z)
		 */
        void mouseMoved(Ogre::Vector3 vect);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche de la souris est pressée et le transmet à signalKeyPressed
		 * \param evt Event OIS
		 */
        void mousePressed(OIS::MouseButtonID evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche de la souris est relâchée et le transmet à signalKeyReleased
		 * \param evt Event OIS
		 */
        void mouseReleased(OIS::MouseButtonID evt);
        /*!
		 * \brief Convertit un évènement OIS::KeyEvent en PlayerControls::Controls pour se défaire du couplage aux touches physiques
		 * \param evt Event OIS
		 * \return PlayerControls::Controls key correspondante
		 */
        PlayerControls::Controls OISEventToControlKey(const OIS::KeyEvent &evt);
        /*!
		 * \brief Convertit un id IS::MouseButtonID en PlayerControls::Controls pour se défaire du couplage aux touches physiques
		 * \param evt Mouse button ID (OIS)
		 * \return PlayerControls::Controls key correspondante
		 */
        PlayerControls::Controls OISEventToControlKey(const OIS::MouseButtonID evt);

};

#endif // __PLAYER_CONTROLS_H__
