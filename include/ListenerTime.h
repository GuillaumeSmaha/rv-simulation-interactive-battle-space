/*!
 *  \file  ListenerTime.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerTime. C'est le listener qui envoit des signaux à temps régulier
 */
#ifndef __LISTENER_TIME_H__
#define __LISTENER_TIME_H__

#include "ObjectRoot.h"
#include <Ogre.h>
#include "ListenerFrame.h"
/*!
 * \class ListenerTime
 * \brief Classe envoyant des signaux à temps régulier, utile pour gérer le vaiseaux.
 *
 * Ecoute le frameListener, à chaque frame, regarde le temps écoulé depuis son dernier signal et si le temps est supérieur à un seuil, lance un signal
 */
class ListenerTime : public ObjectRoot
{
	public:	
        /*!
         * \brief Signal pour le timer
         */
		Signal<void *> signalTimerElapsed;

    private:
        /*!
         * \brief Seuil auquel on dispatch un signal
         */
        unsigned long seuil;
        /*!
         * \brief Permet de vérifier que le timer tourne déja ou pas
         */
        bool started;
         /*!
         * \brief Le timer en lui même
         */
        Ogre::Timer * timer;
        /*!
         * \brief Indique si la pause est active
         */
         bool paused;


    public:
        /*!
         * \brief Constructeur
         * \param seuil Seuil pour faire la mise à jour de la frame
         * \param listenerFrame Pointeur sur le controleur de frame
         */
		ListenerTime(unsigned long seuil, ListenerFrame * listenerFrame);
        /*!
         * \brief Destructeur
         */
		~ListenerTime();
		
        /*!
         * \brief Méthode appelé pour la mise à jour de la frame régulée
         * \param useless NULL
         */
		void watchTime(const Ogre::FrameEvent &evt);
		
        /*!
         * \brief Change l'état de la pause
         * \param pausing Etat de la pause
         */
		void pause(bool pausing);

};


#endif //__LISTENER_TIME_H__
