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
FIND_PACKAGE( OIS REQUIRED )
FIND_PACKAGE( OGRE REQUIRED )
FIND_PACKAGE( CEGUI REQUIRED )
 
IF (NOT "${OGRE_VERSION_NAME}" STREQUAL "Cthugha")
	MESSAGE(SEND_ERROR "You need Ogre 1.7 Cthugha to build this.")
ENDIF()

IF(NOT OIS_FOUND)
    MESSAGE(SEND_ERROR "Failed to find OIS.")
ENDIF()

IF(NOT CEGUI_FOUND)
    MESSAGE(SEND_ERROR "Failed to find CEGUI.")
ENDIF()

IF(NOT CEGUI_OgreRenderer_FOUND)
    MESSAGE(SEND_ERROR "Failed to find CEGUI Ogre Renderer.")
ENDIF()


#Gestion des includes
include_directories(
	${OIS_INCLUDE_DIR}
	${OGRE_INCLUDE_DIR}
	${CEGUI_INCLUDE_DIR}
	${CEGUI_OgreRenderer_INCLUDE_DIRS}
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
	${OIS_LIBRARIES}
	${OGRE_LIBRARIES}
	${CEGUI_LIBRARIES}
	${CEGUI_OgreRenderer_LIBRARIES}
)
