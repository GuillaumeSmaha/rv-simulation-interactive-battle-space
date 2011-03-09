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
		
		std::string file;
		
		file.assign(PROJECT_SOURCE_DIR);
		file.append("/media/sound/tir.ogg");
		this->soundManager->createSound(Utils::toString(GestSound::SOUND_SHOOT), file, false, false);
		file.assign(PROJECT_SOURCE_DIR);
		file.append("/media/sound/traitre.ogg");
		this->soundManager->createSound(Utils::toString(GestSound::SOUND_TRAITRE), file, false, false);
		file.assign(PROJECT_SOURCE_DIR);
		file.append("/media/sound/explosion.ogg");
		this->soundManager->createSound(Utils::toString(GestSound::SOUND_EXPLOSION), file, false, false);
		file.assign(PROJECT_SOURCE_DIR);
		file.append("/media/sound/touche.ogg");
		this->soundManager->createSound(Utils::toString(GestSound::SOUND_DEGATS), file, false, false);
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
