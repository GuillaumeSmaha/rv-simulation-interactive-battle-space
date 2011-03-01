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

    private:
        /*!
         * \brief seuil auquel on dispatch un signal
         */
        unsigned long seuil;
        /*!
         * \brief permet de vérifier que le timer tourne déja ou pas
         */
        bool started;
         /*!
         * \brief Le timer en lui même
         */
        Ogre::Timer * timer;
        /*!
         * \brief Pause
         */
         bool paused;


    public:
    void pause(bool pausing);
    Signal<void *> signalTimerElapsed;
    ListenerTime(long unsigned int seuil, ListenerFrame * listenerFrame);
    ~ListenerTime();
    void watchTime(void *);

};


#endif //__LISTENER_TIME_H__
