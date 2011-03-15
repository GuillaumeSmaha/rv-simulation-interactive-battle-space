# - Locate OGREAL LIBRARIES
# This module defines
#  OGREAL_FOUND, if false, do not try to link to OGREAL
#  OGREAL_INCLUDE_DIR, where to find headers.
#  OGREAL_LIBRARIES, the LIBRARIES to link against
#  OGREAL_BINARY_REL - location of the main bullet binary (release)
#  OGREAL_BINARY_DBG - location of the main bullet binaries (debug)


include(FindPkgMacros)
include(PreprocessorUtils)
findpkg_begin(OGREAL)
set(OGREAL_FIND_REQUIRED 1)


IF(NOT OGG_FOUND)
	MESSAGE(FATAL_ERROR "Ogg est nécessaire pour Vorbis !")
ENDIF(NOT OGG_FOUND)

IF(NOT VORBIS_FOUND)
	MESSAGE(FATAL_ERROR "Ogg est nécessaire pour Vorbis !")
ENDIF(NOT VORBIS_FOUND)

IF(NOT OPENAL_FOUND)
	MESSAGE(FATAL_ERROR "OpenAL est nécessaire pour OgreAL !")
ENDIF(NOT OPENAL_FOUND)

IF(NOT OGRE_FOUND)
	MESSAGE(FATAL_ERROR "Ogre est nécessaire pour OgreAL !")
ENDIF(NOT OGRE_FOUND)

# Get path, convert backslashes as ${ENV_${var}}
getenv_path(OGREAL_HOME)
getenv_path(OGREAL_DIR)
getenv_path(OGREAL_ROOT)
getenv_path(PROGRAMFILES)


set(OGREAL_LIBRARY_NAMES "OgreAL")

# construct search paths from environmental hints and
# OS specific guesses
if (WIN32)
  set(OGREAL_PREFIX_GUESSES
    ${ENV_PROGRAMFILES}/ogreal
    ${ENV_PROGRAMFILES}/OgreAL
    ${ENV_PROGRAMFILES}/OGREAL
    C:/OGREAL-SDK
	C:/lib/ogreal
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OGREAL_HOME]
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OGREAL_DIR]
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OGREAL_ROOT]
  )
elseif (UNIX)
  set(OGREAL_PREFIX_GUESSES
    /opt/ogreal
    /opt/OgreAL
    /opt/OGREAL
    /usr
    /usr/local
    $ENV{HOME}/ogreal
    $ENV{HOME}/OgreAL
    $ENV{HOME}/OGREAL
  )
endif ()

set(OGREAL_PREFIX_PATH
	$ENV{OGREAL_HOME} $ENV{OGREAL_DIR} $ENV{OGREAL_ROOT}
	${OGREAL_PREFIX_GUESSES}
)
create_search_paths(OGREAL)


set(OGREAL_RESET_VARS 
  OGREAL_INCLUDE_DIR 
  OGREAL_LIBRARY_REL OGREAL_LIBRARY_DBG)

set(OGREAL_PREFIX_WATCH ${OGREAL_PREFIX_PATH})
clear_if_changed(OGREAL_PREFIX_WATCH ${OGREAL_RESET_VARS})

# try to locate OGREAL via pkg-config
use_pkgconfig(OGREAL_PKGC "OgreAL")

# locate OGREAL include files

find_path(OGREAL_INCLUDE_DIR NAMES OgreAL.h HINTS ${OGREAL_INC_SEARCH_PATH} ${OGREAL_FRAMEWORK_INCLUDES} ${OGREAL_PKGC_INCLUDE_DIRS} PATH_SUFFIXES "" "ogreal" "OgreAL")
get_debug_names(OGREAL_LIBRARY_NAMES)
find_library(OGREAL_LIBRARY_REL NAMES ${OGREAL_LIBRARY_NAMES} HINTS ${OGREAL_LIB_SEARCH_PATH} ${OGREAL_PKGC_LIBRARY_DIRS} ${OGREAL_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
find_library(OGREAL_LIBRARY_DBG NAMES ${OGREAL_LIBRARY_NAMES_DBG} HINTS ${OGREAL_LIB_SEARCH_PATH} ${OGREAL_PKGC_LIBRARY_DIRS} ${OGREAL_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "debug")
make_library_set(OGREAL_LIBRARY)


list(REMOVE_DUPLICATES OGREAL_INCLUDE_DIR)
findpkg_finish(OGREAL)
add_parent_dir(OGREAL_INCLUDE_DIRS OGREAL_INCLUDE_DIR)


if (NOT OGREAL_FOUND)
  return()
endif ()



get_filename_component(OGREAL_LIBRARY_DIR_REL "${OGREAL_LIBRARY_REL}" PATH)
get_filename_component(OGREAL_LIBRARY_DIR_DBG "${OGREAL_LIBRARY_DBG}" PATH)
set(OGREAL_LIBRARY_DIRS ${OGREAL_LIBRARY_DIR_REL} ${OGREAL_LIBRARY_DIR_DBG})


# find binaries
if (WIN32)
	find_file(OGREAL_BINARY_REL NAMES "OgreAL.dll" HINTS ${OGREAL_BIN_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
	find_file(OGREAL_BINARY_DBG NAMES "OgreAL_d.dll" HINTS ${OGREAL_BIN_SEARCH_PATH} PATH_SUFFIXES "" "debug" )
endif()
	
get_filename_component(OGREAL_BINARY_DIR_REL "${OGREAL_BINARY_REL}" PATH)
get_filename_component(OGREAL_BINARY_DIR_DBG "${OGREAL_BINARY_DBG}" PATH)
set(OGREAL_LIBRARY_DIRS ${OGREAL_BINARY_DIR_REL} ${OGREAL_BINARY_DIR_DBG})
mark_as_advanced(OGREAL_BINARY_REL OGREAL_BINARY_DBG OGREAL_BINARY_DIR_REL OGREAL_BINARY_DIR_DBG)


clear_if_changed(OGREAL_PREFIX_WATCH)
