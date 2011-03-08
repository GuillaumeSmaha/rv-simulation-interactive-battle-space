/*!
*  \file  Message.h
*  \brief Ce fichier contient la déclaration de la classe Message. Elle permet d'afficher de court messages pendant le jeux
*/
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <Fenetre.h>
#include "Utils.h"
#include "ListenerTime.h"
/*!
* \class Message
* \brief Permet d'afficher de court message pendant le jeux
*/


class Message: public ClassRoot, public Fenetre
{

public:
  

    Message(ListenerTime * listenerTime){
        listenerTime->signalTimerElapsed.add(&Message::timer, this);
        elapsedtime=0;
        affiche=false;
    }
    ~Message(){
    }
    void afficher_message(std::string titre,Ogre::String txt);        
    /*!
    * \brief Permet de supprimer une fenetre (appeler par create_std_window, ne devrait pas être utilisé ailleurs).
    */
    bool destroyWindow(const CEGUI::EventArgs & evt);
    bool destroyWindow();
    void timer(void *);

private:

    static int nbMessage;
    bool affiche;
    int elapsedtime;

};

#endif
