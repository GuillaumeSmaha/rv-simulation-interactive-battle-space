#include "Utils.h"

int Utils::_count = 0;
Ogre::String Utils::_logFile = "";

int Utils::initialize(void)
{
	srand(time(NULL));
	return 0;
}

int Utils::randRangeInt(int min, int max)
{
    static bool init = false;
    if(init == false)
    {
        init = true;
        Utils::initialize();
    }
	return (int)((double)rand() / ((double)RAND_MAX + 1) * (max-min+1)+min);
}

int Utils::unique(void)
{
	return _count++;
}

void Utils::log(Ogre::String text)
{
	Ogre::LogManager::getSingletonPtr()->logMessage(text);
}

void Utils::logFileInit(Ogre::String file)
{
	if(file.compare("") != 0)
	{
		std::ofstream fileLog(file.c_str());
		if (fileLog.is_open())
		{
			Utils::_logFile.assign(file);

			fileLog.close();
			std::remove((file.c_str()));
		}
		else
		{
			Ogre::String text = "L'ouverture du fichier de sortie de log a échoué : ";
			text.append(file);
			Ogre::LogManager::getSingletonPtr()->logMessage(text);
		}
	}
	else
	{
		Ogre::String text = "Le fichier de sortie de log est invalide : ";
		text.append(file);
		Ogre::LogManager::getSingletonPtr()->logMessage(text);
	}
}

void Utils::logFile(Ogre::String text)
{
	if(Utils::_logFile.compare("") != 0)
	{
		time_t rawtime;
		struct tm * timeinfo;
		char bufferTime[10];
		std::ofstream fileLog(Utils::_logFile.c_str(), std::ios_base::app);

		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		strftime(bufferTime, 80, "%X: ", timeinfo);

		fileLog << bufferTime << text << "\n";

		fileLog.close();
	}
}

Ogre::Real Utils::radianToDegre (Ogre::Real angleRadian) {
	//Angle en degré = 180 * (angle en radian) / pi
	if (angleRadian==0)
	{
		return 0.0;
	}
	else
	{
		return 180*angleRadian/PI;
	}
}

Ogre::Radian Utils::degreToRadian (Ogre::Real angleDegre) {
	//Angle en radian = pi * (angle en degré) / 180
	return Ogre::Radian(PI*angleDegre/180);
}

Ogre::String Utils::toString( float Value )
{
	std::ostringstream oss;
	oss << Value;
	return oss.str();
}

Ogre::String Utils::toString( int Value )
{
	std::ostringstream oss;
	oss << Value;
	return oss.str();
}

Ogre::String Utils::toString( int * Value)
{
	return Utils::toString(*Value);
}
