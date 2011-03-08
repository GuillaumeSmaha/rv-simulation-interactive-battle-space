/*!
*  \file  Fenetre.h
*  \brief Ce fichier contient la déclaration de la classe Fenetre. Elle utilise cegui pour offrir des fenetre standard. Utiliser par le Menus et Annonce
*/
#ifndef __FENETRE_H__
#define __FENETRE_H__



#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "PlayerControls.h"
/*!
* \class Fenetre
* \brief Elle utilise cegui pour offrir des fenetre standard. Utiliser par le Menus et Annonce
*/

class Fenetre
{
    protected:

        /*!
        * \brief fenetre principale de l'application
        */
        CEGUI::Window * mainWdw;


        /*!
		* \brief Permet de créer une fentre de menus générique
		*/
        CEGUI::Window * create_std_window(std::string name, float posX, float posY ,float largeur, float hauteur, int nbEl ,CEGUI::Window ** contenu);

        /*!
		* \brief Permet de supprimer une fenetre (appeler par create_std_window, ne devrait pas être utilisé ailleurs).
		*/
        virtual bool destroyWindow(const CEGUI::EventArgs & evt) =0;

		/*!
		* \brief Réagis aux actions de player, en particulier pour gérer l'ouverture/fermeture du menus
		*/

        void actionFromPlayer(PlayerControls::Controls key);
         /*!
        * \brief Dispatché quand mis en pause ou reprise
        */
        Signal<bool> signalPaused;

};
#endif 
