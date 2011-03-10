#ifndef LISTENERJOYSTICK_H
#define LISTENERJOYSTICK_H

#include <OISInputManager.h>
#include <OISJoyStick.h>
#include "ObjectRoot.h"
#include "Signal.h"
#include "Ogre.h"
class ListenerJoystick : public ObjectRoot
{
    private:
		/*!
		 *  \brief Gestionnaire d'événements
		 */
        OIS::InputManager * inputManager;
		/*!
		 *  \brief Capteur d'événements de la souris
		 */
        OIS::JoyStick * joystick;

	public:
        /*!
		 * \brief Dispatche un signal lorsque la souris bouge Signal(Ogre::Vector3(X, Y, Z)))
		 */
        Signal<Ogre::Vector3> signalMouseMoved;
        /*!
		 * \brief Dispatche un signal lorsque une touche de la souris est enfoncée Signal(OIS::MouseButtonID)
		 */
        Signal<void*> signalMousePressed;
        /*!
		 * \brief Dispatche un signal lorsque une touche de la souris est relâchée Signal(OIS::MouseButtonID)
		 */
        Signal<void*> signalMouseReleased;
		/*!
		 * \brief Constructeur
		 */
		ListenerJoystick(OIS::InputManager * inputManager);
		/*!
		 * \brief Destructeur
		 */
		~ListenerJoystick();

		/*!
		 * \brief Recupère les événements
		 */
		void capture()
		{
			this->capture(NULL);
		}
		/*!
		 * \brief Recupère les événements
		 * \param paramCapture Parametre de capture
		 */
		void capture(void * paramCapture);

        bool povMoved(const OIS::JoyStickEvent &e, int pov);
        bool axisMoved(const OIS::JoyStickEvent &e, int axis );
        bool sliderMoved(const OIS::JoyStickEvent &e, int sliderID );
        bool buttonPressed(const OIS::JoyStickEvent &e, int button );
        bool buttonReleased(const OIS::JoyStickEvent &e, int button );
        //getter/setter

		/*!
		 * \brief [Getter] Récupère la valeur de mouse
		 * \return Le pointeur sur le capteur d'événements de la souris
		 */
		OIS::JoyStick * getJoystick()
		{
			return this->joystick;
		}
};

#endif // LISTENERJOYSTICK_H
