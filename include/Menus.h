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
#include "PlayerControls.h"
#include "Application.h"
//#include <CEGUIOgreRenderer.h>

//déclaration avancé pour permettre la compilation
class Application;

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
        
        /*!
        * \brief pointeur sur l'application globale pour intéragir avec celle ci
        */
        Application * app;
        
        /*!
        * \brief fenetre principale de l'application
        */
        CEGUI::Window * mainWdw;
       
        bool menu_open;
	public:
		/*!
		* \brief constructeur
		*/
		Menus(ListenerMouse * mouseListener, ListenerKeyboard * keyControl, PlayerControls * pControl, Application * app);
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
		* \brief Réagis aux actions de player, en particulier pour gérer l'ouverture/fermeture du menus
		*/
		
        void actionFromPlayer(PlayerControls::Controls key);
        
        /*!
         * \brief
         */
        void afficher_menus();
        void cacher_menus();
        
        /*!
         * \brief affiche un bouton permettant de quitter
         */
        void creer_btn_exit(void);
        void afficher_btn_exit(void);
        void cacher_btn_exit(void);

		/*!
		* \brief Permet d'afficher un curseur de souris
		*/
		void creer_souris(void);
		void afficher_souris(void);
		void cacher_souris(void);

        bool clicExit(const CEGUI::EventArgs & evt);

};

#endif //__MENUS_H__
