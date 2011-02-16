/*!
*  \file  Menus.h
*  \brief Ce fichier contient la déclaration de la classe Menus. Elle utilise cegui pour gérer un menus du jeux
*/
#ifndef __MENUS_H__
#define __MENUS_H__

#include <Ogre.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
//#include <CEGUIOgreRenderer.h>

/*!
* \class Menus
* \brief Classe gérant les menus du jeux 
*/
class Menus
{
	private:
		/*!
		* \brief le renderer de cegui pour ogre
		*/
		CEGUI::OgreRenderer * menusRenderer;
		CEGUI::System * menusSystem;

	public:
		/*!
		* \brief constructeur
		*/
		Menus();
		/*!
		* \brief destructeur
		*/
		~Menus();

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
