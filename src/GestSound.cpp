#include "GestSound.h"
#include "Utils.h"

using namespace std;

GestSound* GestSound::_instance = NULL;

GestSound* GestSound::getSingleton(void)
{
	if (_instance == NULL)
	{
		_instance = new GestSound();
	}
	return _instance;
}

GestSound::GestSound()
{
	if (_instance == NULL)
	{
		_instance = this;
		
		//initialisation du manager de son OpenAL
		this->soundManager = new OgreAL::SoundManager("Device Manager", 10);
		
		this->soundManager->createSound(Utils::toString(GestSound::SOUND_SHOOT), Utils::getFullPathSound("tir.ogg"), false, false);
		
		this->soundManager->createSound(Utils::toString(GestSound::SOUND_TRAITRE), Utils::getFullPathSound("traitre.ogg"), false, false);
		
		this->soundManager->createSound(Utils::toString(GestSound::SOUND_EXPLOSION), Utils::getFullPathSound("explosion.ogg"), false, false);
		
		this->soundManager->createSound(Utils::toString(GestSound::SOUND_DEGATS), Utils::getFullPathSound("touche.ogg"), false, false);
	}
}

GestSound::~GestSound()
{
	_instance->soundManager->destroyAllSounds();
}

void GestSound::play(GestSound::SoundType soundType)
{
	this->soundManager->getSound(Utils::toString(soundType))->play();
}

void GestSound::destroy()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}
