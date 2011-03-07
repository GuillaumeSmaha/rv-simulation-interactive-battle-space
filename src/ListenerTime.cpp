#include "ListenerTime.h"

using namespace Ogre;

ListenerTime::ListenerTime(unsigned long seuil, ListenerFrame * listenerFrame)
{
	this->seuil = seuil;
	this->started = false;
	this->timer = new Timer();
	listenerFrame->signalFrameEnded.add(&ListenerTime::watchTime, this);
	paused = false;
}

ListenerTime::~ListenerTime()
{
	delete this->timer;
}

void ListenerTime::watchTime(const Ogre::FrameEvent &evt)
{
	//si le starter n'a pas été démarré on le démarre
	if(this->started == false)
	{
		this->timer->reset();
		this->started = true;
	}

	//si le temps est écoulé
	if(this->timer->getMilliseconds()>seuil)
	{
		//emit dispatch
		if(!paused)
		{
			this->signalTimerElapsed.dispatch();
		}
		this->timer->reset();
	}
}

void ListenerTime::pause(bool pausing)
{
	this->paused = pausing;
}

