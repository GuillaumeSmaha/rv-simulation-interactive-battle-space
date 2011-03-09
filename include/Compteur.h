/*!
*  \file  Compteur.h
*  \brief Ce fichier contient la déclaration de la classe Compteur. Classe abstraite permettant de gérer un compteur associé à un vaiseau
*/
#ifndef __COMPTEUR_H__
#define __COMPTEUR_H__

#include <Ogre.h>
#include "Utils.h"
#include "ClassRoot.h"
#include "ShipAbstract.h"
#include "ListenerTime.h"


/*!
* \class Compteur
*/
class Compteur : public ClassRoot, public Ogre::RenderTargetListener
{
    protected:	
        /*!
		 * \brief Le vaiseau auquel est lié le compteur
		*/
		ShipAbstract * ship;
		/*!
		 * \brief Nom de l'objet de la jauge
		*/
		Ogre::String panelJaugeNameSpeed;
		Ogre::String panelJaugeNameLife;
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
		Compteur(ShipAbstract * ship, ListenerTime * listenerTime);
        Compteur();
		/*!
		 * \brief Destructeur
		*/
		~Compteur();

		/*!
		 * \brief Définit le viewport où afficher le compteur
		 * \param viewport Pointeur sur le viewport
		*/
		void setViewport(Ogre::Viewport * viewport);

    protected:	
		/*!
		 * \brief La fonction appelé régulièrement pour mettre à jour la vitesse
		*/
		void miseAJour(void *);

        void miseAJourLifeCompteur(void);
        void miseAJourSpeedCompteur(void);

		/*!
		 * \brief appelé juste avant la mise à jour des textures,
		 * permet de mettre à jour l'overlay et de la cacher aux autres viewport et le recachant juste aprés
		 * \param evt Evenement de rendu
		*/
		virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
};

#endif //__COMPTEUR_H__
