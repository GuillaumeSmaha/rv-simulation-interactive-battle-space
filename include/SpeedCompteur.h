/*!
*  \file  SpeedCompteur.h
*  \brief Ce fichier contient la déclaration de la classe SpeedCompteur. Permet d'afficher pour un joueur un compteur de vitesse
*/
#ifndef __SPEED_COMPTEUR_H__
#define __SPEED_COMPTEUR_H__

#include <Ogre.h>
#include "Utils.h"
#include "ClassRoot.h"
#include "ShipAbstract.h"
#include "ListenerTime.h"


/*!
* \class SpeedCompteur
* \brief Classe Permet d'afficher pour un joueur un compteur de vitesse
*/
class SpeedCompteur : public ClassRoot, public Ogre::RenderTargetListener
{
	private:
		/*!
		 * \brief Le vaiseau auquel est lié le compteur
		*/
		ShipAbstract * ship;
		/*!
		 * \brief Nom de l'objet de la jauge
		*/
		Ogre::String panelJaugeName;
		/*!
		 * \brief Un compteur est associé à un unique viewport
		*/
		Ogre::Viewport * viewport;
		/*!
		 * \brief l'overlay représente le panel de vitresse
		*/
		Ogre::Overlay* overlay;
		
	public:
		/*!
		 * \brief Constructeur
		 * \param ship Le vaisseau contenant la vitesse de celui-ci
		 * \param listenerTime Pointeur sur le controleur de frame régulé
		*/
		SpeedCompteur(ShipAbstract * ship, ListenerTime * listenerTime);
		/*!
		 * \brief Destructeur
		*/
		~SpeedCompteur();

		/*!
		 * \brief set le viewport
		*/
		void setViewport(Ogre::Viewport * viewport);

	private:
		/*!
		 * \brief La fonction appelé régulièrement pour mettre à jour la vitesse
		*/
		void miseAJour(void *);

		/*!
		 * \brief appelé juste avant la mise à jour des textures,
		 * permet de mettre à jour l'overlay et de la cacher aux autres viewport et le recachant juste aprés
		*/
		virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
};

#endif //__SPEED_COMPTEUR_H__
