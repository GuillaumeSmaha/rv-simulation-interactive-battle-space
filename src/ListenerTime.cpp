#include "ListenerTime.h"

using namespace Ogre;

ListenerTime::ListenerTime(unsigned long seuil, ListenerFrame * listenerFrame)
{
    this->seuil=seuil;
    this->started=false;
    this->timer = new Timer();
    listenerFrame->signalFrameEnded.add(&ListenerTime::watchTime, this);
}

ListenerTime::~ListenerTime()
{
    delete(this->timer);
}

void ListenerTime::watchTime(void * useless)
{
    //si le starter n'a pas été démarré on le démarre
    if(this->started==false)
    {
        this->timer->reset();
        this->started=true;
    }

    //si le temps est écoulé
    if(this->timer->getMilliseconds()>seuil)
    {
        //emit dispatch
        this->signalTimerElapsed.dispatch();
        this->timer->reset();
    }
}
