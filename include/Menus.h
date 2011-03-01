/*!
*  \file  Menus.h
*  \brief Ce fichier contient la déclaration de la classe Menus. Elle utilise cegui pour gérer un menus du jeux
*/
#ifndef __MENUS_H__
#define __MENUS_H__

#include <Ogre.h>
#include <string>
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "config.h"
#include "ListenerMouse.h"
#include "ListenerKeyboard.h"
#include "PlayerControls.h"
#include "Application.h"
#include "Signal.h"
#include "Utils.h"
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

        ListenerMouse * mouseControl;
        ListenerKeyboard * keyControl;
        PlayerControls * pControl;

        /*!
        * \brief fenetre principale de l'application
        */
        CEGUI::Window * mainWdw;

        bool menu_open;
	public:
         /*!
        * \brief Dispatché quand mis en pause ou reprise
        */
        Signal<bool> signalPaused;
		/*!
		* \brief constructeur
		*/
		Menus(ListenerMouse * mouseListener, ListenerKeyboard * keyControl, PlayerControls * pControl, Application * app);
		/*!
		* \brief destructeur
		*/
		~Menus();

    private:
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
         * \brief Lance l'affichage des différents éléments du menus lors de l'activation de celui ci
         */
        void afficher_menus();

        /*!
         * \brief Retire le menus lorsque l'on le quitte.
         */
        void cacher_menus();

        /*!
         * \brief Crée le menus principal
         */
        void creer_main_window(void);

        /*!
         * \brief Affiche le menus principal
         */
        void afficher_main_window(void);

        /*!
         * \brief Cache le menus principal
         */
        void cacher_main_window(void);

		/*!
		* \brief Permet d'afficher un curseur de souris
		*/
		void creer_souris(void);

        /*!
         * \brief Affiche la souris
         */
		void afficher_souris(void);

        /*!
         * \brief cache la souris
        */
		void cacher_souris(void);

		/*!
		* \brief Action appelé lors de l'appui sur le bouton exit
		*/
        bool clicExit(const CEGUI::EventArgs & evt);

        /*!
		* \brief Action appelé lors de l'appui sur le bouton restart
		*/
        bool clicRestart(const CEGUI::EventArgs & evt);
       
         /*!
		* \brief Action appelé lors de l'appui sur le bouton about
		*/
        bool clicAbout(const CEGUI::EventArgs & evt);

        /*!
		* \brief Action appelé lors de l'appui sur le bouton scenario
		*/
        bool clicScenario(const CEGUI::EventArgs & evt);

        /*!
		* \brief Permet de créer une fentre de menus générique
		*/
        CEGUI::Window * create_std_window(std::string name, float posX, float posY ,float largeur, float hauteur, int nbEl ,CEGUI::Window ** contenu);

        /*!
		* \brief Permet de supprimer une fenetre (appeler par create_std_window, ne devrait pas être utilisé ailleurs).
		*/
        bool destroyWindow(const CEGUI::EventArgs & evt);

        /*!
		* \brief Permet de supprimer les intéractions du jeux en cours (actions des touches, défilement...)
		*/
        void suspendre_jeux();
        
        /*!
		* \brief Permet de reprendre le jeux en cours
		*/
        void redemarrer_jeux();


};

#endif //__MENUS_H__
