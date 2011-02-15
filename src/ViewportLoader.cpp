#include "ViewportLoader.h"

ViewportLoader * ViewportLoader::_instance = NULL;


ViewportLoader * ViewportLoader::getSingleton(void)
{
	return _instance;
}


ViewportLoader::ViewportLoader(ListenerWindow * listenerWindow)
{
	this->listenerWindow = listenerWindow;
	if(_instance == NULL)
	{
	    _instance = this;
	}
}


bool ViewportLoader::deleteViewportLoader(void)
{
    if(_instance != NULL)
    {
		_instance->listenerWindow->getRenderWindow()->removeAllViewports();
		while(_instance->removeViewport(0)) {};
        delete _instance;
        return true;
    }
    
    return false;
}

ViewportLoader::~ViewportLoader(void)
{
}


int ViewportLoader::addViewport(CameraFixeAbstract * gestCamera)
{
	Ogre::Viewport * viewport = this->listenerWindow->getRenderWindow()->addViewport(gestCamera->getCamera(), this->countViewport());
	viewport->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f));
	
	this->listViewport.push_back(viewport);
	
	//setDimensions(left, top, width, height)
	
	for(int i = 0 ; i < this->countViewport() ; i++)
	{
		Ogre::Real left = viewport->getWidth()/this->countViewport()*i;
		Ogre::Real top = viewport->getTop();
		Ogre::Real width = viewport->getWidth()/this->countViewport();
		Ogre::Real height = viewport->getHeight();
		
		Ogre::Viewport * viewport = this->listViewport.at(i);
		viewport->setDimensions(left, top, width, height);
		viewport->getCamera()->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
	}
	
	return (this->countViewport()-1);
}


bool ViewportLoader::changeCameraViewport(int idViewport, CameraFixeAbstract * gestCamera)
{
	if(idViewport < this->countViewport())
	{
		Ogre::Viewport * viewport = this->listViewport.at(idViewport);
		if(viewport != NULL)
		{
			viewport->setCamera(gestCamera->getCamera());
			gestCamera->getCamera()->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
		
			return true;
		}
	}
	return false;
}

bool ViewportLoader::removeViewport(int idViewport)
{
	if(idViewport < this->countViewport())
	{
		Ogre::Viewport * viewport = this->listViewport.at(idViewport);
		if(viewport != NULL)
		{
			this->listViewport.erase(this->listViewport.begin()+idViewport);
			return true;
		}
	}
	return false;
}
