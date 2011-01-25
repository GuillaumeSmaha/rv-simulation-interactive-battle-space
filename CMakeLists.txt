cmake_minimum_required(VERSION 2.8)

#Déclaration du projet
project(RV-simulation-bataille)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
set(PROJECT_VERSION_FULL "${PROJECT_VERSION}.${PROJECT_VERSION_PATCH}")

set(CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/cmake"
	"${CMAKE_MODULE_PATH}"
)

#Include des dépendances
FIND_PACKAGE( OGRE REQUIRED )


#Gestion des includes
include_directories(
	${OGRE_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_BINARY_DIR}/include
)

#Génération du fichier de configuration
configure_file(${CMAKE_SOURCE_DIR}/config.h.cmake ${CMAKE_BINARY_DIR}/include/config.h)
	
#Génération de la liste des fichiers
file(
	GLOB_RECURSE
	source_files
	src/*.cpp
	include/*.h
)

#Déclaration de l'exécutable
add_executable(
	rv-simulation-bataille
	${source_files}
)

#Configuration de l'édition de liens
target_link_libraries(
	rv-simulation-bataille
	${OGRE_LIBRARIES}
)
