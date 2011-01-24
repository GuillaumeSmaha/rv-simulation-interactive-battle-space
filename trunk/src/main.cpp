#include <iostream>
#include <Ogre.h>
#include "config.h"

int main(int argc, char * argv[])
{
	std::cout << "Project : " << PROJECT_NAME << std::endl;
	std::cout << "Version : " << PROJECT_VERSION_FULL << std::endl << std::endl;
	std::cout << "Ogre Version Name : " << OGRE_VERSION_NAME << std::endl;
	std::cout << "Ogre Version : " << OGRE_VERSION_MAJOR << "." << OGRE_VERSION_MINOR << "." << OGRE_VERSION_PATCH << std::endl;
	
	
	return EXIT_SUCCESS;
}
