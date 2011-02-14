#include "ListenerWindow.h"

ListenerWindow::ListenerWindow(Ogre::Root * root, Ogre::String nameWindow)
{
	this->renderWindow = root->initialise(true, nameWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(this->renderWindow, this);
	this->windowResized(this->renderWindow);
}

ListenerWindow::~ListenerWindow()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(this->renderWindow, this);
	this->windowClosed(this->renderWindow);
}

void ListenerWindow::windowResized(Ogre::RenderWindow * rw)
{
	unsigned int width, height, depth;
	int left, top;

	// Adjust mouse clipping area
	/*
	rw->getMetrics(width, height, depth, left, top);
	const OIS::MouseState &ms = this->mouse->getMouseState();
	ms.width = width;
	ms.height = height;*/
	

}

void ListenerWindow::windowClosed(Ogre::RenderWindow * rw)
{
	// Only close for window that created OIS (the main window)
	if(rw == this->renderWindow)
	{
		this->signalWindowClosed.dispatch();
	}
}
