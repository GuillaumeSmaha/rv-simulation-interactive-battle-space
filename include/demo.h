#ifndef __DEMO_H__
#define __DEMO_H__

#include <Ogre.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>


class Demo : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener {
private:
	Ogre::Root *root;
	Ogre::SceneManager *sceneMgr;
	Ogre::RenderWindow *window;
	Ogre::String resourcesCfg;
	Ogre::String pluginsCfg;
	
	OIS::InputManager *inputManager;
	OIS::Mouse *mouse;
	OIS::Keyboard *keyboard;

	Ogre::Camera *camera;
	bool shutDown;
		
	void loadRessources(void);
	void initListeners(void);
	void initScene(void);
	
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	
	// Ogre::WindowEventListener
	void windowResized(Ogre::RenderWindow* rw);
	void windowClosed(Ogre::RenderWindow* rw);
	
	// OIS::KeyListener
	bool keyPressed( const OIS::KeyEvent &evt );
	bool keyReleased( const OIS::KeyEvent &evt );
	
	// OIS::MouseListener
	bool mouseMoved( const OIS::MouseEvent &evt );
	bool mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id );
	bool mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id );

public:
	Demo(void);
	virtual ~Demo(void);
	bool start(void);	
	
};

#endif // __DEMO_H__
