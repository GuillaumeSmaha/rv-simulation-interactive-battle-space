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

include(Function)
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


#Copie des fichiers pour l'éxécution
writeResourceFile("${CMAKE_BINARY_DIR}/" 0)
writePluginFile("${CMAKE_BINARY_DIR}/" 0)
IF(WIN32)
	writeResourceFile("${CMAKE_BINARY_DIR}/" 1)
	writePluginFile("${CMAKE_BINARY_DIR}/" 1)
	
	STRING(REPLACE "CEGUIBase.dll" "" dirCegui ${CEGUI_BINARY_REL})

	writeResourceFile("${CMAKE_BINARY_DIR}/Debug/" 1)
	writePluginFile("${CMAKE_BINARY_DIR}/Debug/" 1)
	copyFilesFilter(${OGRE_PLUGIN_DIR_DBG} "${CMAKE_BINARY_DIR}/" "(.exe)|(.cfg)")
	copyFile("${dirCegui}CEGUIBase_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
	copyFile("${dirCegui}CEGUIOgreRenderer_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
	copyFile("${dirCegui}CEGUIExpatParser_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
	copyFile("${dirCegui}CEGUIFalagardWRBase_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
	copyFile("${dirCegui}CEGUIOpenGLRenderer_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
	copyFile("${dirCegui}CEGUIDirect3D9Renderer_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
	copyFile("${dirCegui}CEGUIDirect3D10Renderer_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
	copyFile("${dirCegui}CEGUIDirect3D11Renderer_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
	
	writeResourceFile("${CMAKE_BINARY_DIR}/Release/" 0)
	writePluginFile("${CMAKE_BINARY_DIR}/Release/" 0)
	copyFilesFilter(${OGRE_PLUGIN_DIR_REL} "${CMAKE_BINARY_DIR}/" "(.exe)|(.cfg)")
	copyFile("${dirCegui}CEGUIBase.dll" "${CMAKE_BINARY_DIR}/Release/")
	copyFile("${dirCegui}CEGUIOgreRenderer.dll" "${CMAKE_BINARY_DIR}/Release/")
	copyFile("${dirCegui}CEGUIExpatParser.dll" "${CMAKE_BINARY_DIR}/Release/")
	copyFile("${dirCegui}CEGUIFalagardWRBase.dll" "${CMAKE_BINARY_DIR}/Release/")
	copyFile("${dirCegui}CEGUIOpenGLRenderer.dll" "${CMAKE_BINARY_DIR}/Release/")
	copyFile("${dirCegui}CEGUIDirect3D9Renderer.dll" "${CMAKE_BINARY_DIR}/Release/")
	copyFile("${dirCegui}CEGUIDirect3D10Renderer.dll" "${CMAKE_BINARY_DIR}/Release/")
	copyFile("${dirCegui}CEGUIDirect3D11Renderer.dll" "${CMAKE_BINARY_DIR}/Release/")
ENDIF(WIN32)

IF(CMAKE_COMPILER_IS_GNUCC)
	ADD_DEFINITIONS(-pipe)
ENDIF(CMAKE_COMPILER_IS_GNUCC)



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
configure_file(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_BINARY_DIR}/include/config.h)

	
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

#Générateur de documentation
include(UseDoxygen OPTIONAL)

#Mise en garde du dossier pour la création du build en cas de non-spécification
string(COMPARE EQUAL ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} BUILD_IS_EQUAL)
IF(BUILD_IS_EQUAL)
	message(STATUS "")
	message(STATUS "/!\\ Il est préférable de construire le cmake dans un dossier différent de la racine (par exemple \"build\")  !")
	message(STATUS "")
ENDIF(BUILD_IS_EQUAL)
