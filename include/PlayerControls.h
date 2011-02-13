#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H
#include "Signal.h"
//#include "ListenerMouse.h"
#include "ObjectRoot.h"
#include "ListenerKeyboard.h"
#include <OISInputManager.h>
#include <OISKeyboard.h>
class ListenerKeyboard;
//class ListenerMouse;
/*!
* \class PlayerControls
* \brief Class Permettant de gérer le contrôle de manière "haut niveau" du joueur au d'utiliser directement les évènements de base de Ogre
* Permettra par la suite de facilemet modifier les contrôles pour chaque joueur (enregistrés dans un fichier par exemple)
* Par la suite il faudra donc écouter les évènements (signaux) de PlayerControls et non plus directement de mouse et keyboard
*/
class PlayerControls: public ObjectRoot
{
    public:
        /*!
         * \brief Constructor
         * \param mouse MouseListener
         * \param keyboard KeyboardListener
         */
        PlayerControls(/*ListenerMouse* mouse,*/ ListenerKeyboard* keyboard);
        /*!
         * \brief Destructor
         */
        virtual ~PlayerControls();
		/// Définit les différents types de contrôles
		enum Controls
		{
			SHOOT1 = 0,
			SHOOT2 = 1,
			ACCELERATION = 2,
			BRAKE = 3,
			LEFT = 4,
			RIGHT = 5,
			QUIT = 6
		};
		/*!
		 * \brief Emet un dispatche lorsqu'une touche est préssée  Signal(PlayerControls::Controls key)
		 */
        Signal<PlayerControls::Controls> signalKeyPressed;
        /*!
		 * \brief Emet un dispatche lorsqu'une touche est relâchée  Signal(PlayerControls::Controls key)
		 */
        Signal<PlayerControls::Controls> signalKeyReleased;
        //Surement un truc genre signalMove (pour la souris/joystick)
    protected:
    private:
         /*!
		 * \brief Reçoit un dispatche lorsqu'une touche est pressée et le transmet à signalKeyPressed;
		 * \param evt Event OIS
		 */
        void keyboardPressed(const OIS::KeyEvent &evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche est relâchée et le transmet à signalKeyReleaed;
		 * \param evt Event OIS
		 */
        void keyboardReleased(const OIS::KeyEvent &evt);
        /*!
		 * \brief Convertit un évènement OIS::KeyEvent en PlayerControls::Controls pour se défaire du couplage aux touches physiques
		 * \param evt Event OIS
		 * \return PlayerControls::Controls key correspondante
		 */
		 //TODO:définir le comportement si aucune touche ne correspond
        PlayerControls::Controls OISEventToControlKey(const OIS::KeyEvent &evt);

};

#endif // PLAYERCONTROLS_H
