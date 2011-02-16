/*!
*  \file  Menus.h
*  \brief Ce fichier contient la déclaration de la classe Menus. Elle utilise cegui pour gérer un menus du jeux
*/
#ifndef __MENUS_H__
#define __MENUS_H__

#include <Ogre.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "ListenerMouse.h"
#include "ListenerKeyboard.h"
//#include <CEGUIOgreRenderer.h>

/*!
* \class Menus
* \brief Classe gérant les menus du jeux 
*/
class Menus: public ObjectRoot
{
	private:
		/*!
		* \brief le renderer de cegui pour ogre
		*/
		CEGUI::OgreRenderer * menusRenderer;

	public:
		/*!
		* \brief constructeur
		*/
		Menus(ListenerMouse * mouseListener, ListenerKeyboard * keyControl);
		/*!
		* \brief destructeur
		*/
		~Menus();

        /*!
         * \brief Permet de récupérer appuis sur touche dans cegui
        */
        void keyPressed(const OIS::KeyEvent &evt);
        
        /*!
         * \brief Permet de récupérer les relachements d'une touche dans cegui
        */
        void keyReleased(const OIS::KeyEvent &evt);


        /*!
         * \brief Permet de récupérer les relachement de touche dans cegui
        */
        void keyReleased(OIS::MouseButtonID evt);

        /*!
         * \brief Permet de récupérer les clics de souris dans cegui
        */
        void mousePressed(OIS::MouseButtonID evt);

        /*!
         * \brief Permet de récupérer les relachements de la souris dans cegui
        */
        void mouseReleased(OIS::MouseButtonID evt);

        /*!
         * \brief Permet de récupérer les déplacements de la souris
        */
        void mouseMoved(Ogre::Vector3 vect);

        /*!
         * \brief Permet de convertir les clics de souris pour cegui (utilisé par mousePressed).
        */
        CEGUI::MouseButton convertButton(OIS::MouseButtonID evt);

		/*!
		* \brief pour tester: affiche un bouton quit
		*/
		void affiche_btn_exit(void);

		/*!
		* \brief Permet d'afficher un curseur de souris
		*/
		void afficher_souris(void);

};

#endif //__MENUS_H__
