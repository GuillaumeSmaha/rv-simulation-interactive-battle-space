#include "ListenerWindow.h"

ListenerWindow::ListenerWindow(Ogre::Root * root, Ogre::String nameWindow)
{
	this->mouseControl = NULL;
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
	if(this->mouseControl != NULL)
	{
		unsigned int width, height, depth;
		int left, top;

		rw->getMetrics(width, height, depth, left, top);
		const OIS::MouseState &ms = this->mouseControl->getMouse()->getMouseState();
		ms.width = width;
		ms.height = height;
	}
}

void ListenerWindow::windowClosed(Ogre::RenderWindow * rw)
{
	if(rw == this->renderWindow)
	{
		this->signalWindowClosed.dispatch();
	}
}
