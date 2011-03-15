# - Locate VORBIS LIBRARIES
# This module defines
#  VORBIS_FOUND, if false, do not try to link to VORBIS
#  VORBIS_INCLUDE_DIR, where to find headers.
#  VORBIS_LIBRARIES, the LIBRARIES to link against
#  VORBIS_BINARY_REL - location of the main bullet binary (release)
#  VORBIS_BINARY_DBG - location of the main bullet binaries (debug)


include(FindPkgMacros)
include(PreprocessorUtils)
findpkg_begin(VORBIS)
set(VORBIS_FIND_REQUIRED 1)

IF(NOT OGG_FOUND)
	MESSAGE(FATAL_ERROR "Ogg est nécessaire pour Vorbis !")
ENDIF(NOT OGG_FOUND)

# Get path, convert backslashes as ${ENV_${var}}
getenv_path(VORBIS_HOME)
getenv_path(VORBIS_DIR)
getenv_path(VORBIS_ROOT)
getenv_path(PROGRAMFILES)


set(VORBIS_base_LIBRARY_NAMES "vorbis")
set(VORBIS_enc_LIBRARY_NAMES "vorbisenc")
set(VORBIS_file_LIBRARY_NAMES "vorbisfile")
if (WIN32)
	set(VORBIS_base_LIBRARY_NAMES "libvorbis")
	set(VORBIS_enc_LIBRARY_NAMES "libvorbisenc")
	set(VORBIS_file_LIBRARY_NAMES "libvorbisfile")
endif (WIN32)

# construct search paths from environmental hints and
# OS specific guesses
if (WIN32)
  set(VORBIS_PREFIX_GUESSES
    ${ENV_PROGRAMFILES}/ogreal
    ${ENV_PROGRAMFILES}/vorbis
    ${ENV_PROGRAMFILES}/VORBIS
    C:/VORBIS-SDK
    C:/lib/vorbis
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;VORBIS_HOME]
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;VORBIS_DIR]
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;VORBIS_ROOT]
  )
elseif (UNIX)
  set(VORBIS_PREFIX_GUESSES
    /opt/ogreal
    /opt/vorbis
    /opt/VORBIS
    /usr
    /usr/local
    $ENV{HOME}/ogreal
    $ENV{HOME}/vorbis
    $ENV{HOME}/VORBIS
  )
endif ()

set(VORBIS_PREFIX_PATH
	$ENV{VORBIS_HOME} $ENV{VORBIS_DIR} $ENV{VORBIS_ROOT}
	${VORBIS_PREFIX_GUESSES}
)
create_search_paths(VORBIS)


set(VORBIS_RESET_VARS 
  VORBIS_INCLUDE_DIR 
  VORBIS_LIBRARY_REL VORBIS_LIBRARY_DBG)

set(VORBIS_PREFIX_WATCH ${VORBIS_PREFIX_PATH})
clear_if_changed(VORBIS_PREFIX_WATCH ${VORBIS_RESET_VARS})

# try to locate VORBIS via pkg-config
use_pkgconfig(VORBIS_PKGC "vorbis")

# locate VORBIS include files
find_path(VORBIS_INCLUDE_DIR NAMES vorbis/vorbisenc.h HINTS ${VORBIS_INC_SEARCH_PATH} ${VORBIS_FRAMEWORK_INCLUDES} ${VORBIS_PKGC_INCLUDE_DIRS})


findpkg_begin(VORBIS_base)
set(VORBIS_base_FIND_REQUIRED 1)
set(VORBIS_base_INCLUDE_DIR ${VORBIS_INCLUDE_DIR})
get_debug_names(VORBIS_base_LIBRARY_NAMES)
find_library(VORBIS_base_LIBRARY_REL NAMES ${VORBIS_base_LIBRARY_NAMES} HINTS ${VORBIS_LIB_SEARCH_PATH} ${VORBIS_PKGC_LIBRARY_DIRS} ${VORBIS_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
find_library(VORBIS_base_LIBRARY_DBG NAMES ${VORBIS_base_LIBRARY_NAMES_DBG} HINTS ${VORBIS_LIB_SEARCH_PATH} ${VORBIS_PKGC_LIBRARY_DIRS} ${VORBIS_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "debug")
make_library_set(VORBIS_base_LIBRARY)
findpkg_finish(VORBIS_base)


findpkg_begin(VORBIS_file)
set(VORBIS_file_FIND_REQUIRED 1)
set(VORBIS_file_INCLUDE_DIR ${VORBIS_INCLUDE_DIR})
get_debug_names(VORBIS_file_LIBRARY_NAMES)
find_library(VORBIS_file_LIBRARY_REL NAMES ${VORBIS_file_LIBRARY_NAMES} HINTS ${VORBIS_LIB_SEARCH_PATH} ${VORBIS_PKGC_LIBRARY_DIRS} ${VORBIS_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
find_library(VORBIS_file_LIBRARY_DBG NAMES ${VORBIS_file_LIBRARY_NAMES_DBG} HINTS ${VORBIS_LIB_SEARCH_PATH} ${VORBIS_PKGC_LIBRARY_DIRS} ${VORBIS_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "debug")
make_library_set(VORBIS_file_LIBRARY)
findpkg_finish(VORBIS_file)


findpkg_begin(VORBIS_enc)
set(VORBIS_enc_INCLUDE_DIR ${VORBIS_INCLUDE_DIR})
get_debug_names(VORBIS_enc_LIBRARY_NAMES)
find_library(VORBIS_enc_LIBRARY_REL NAMES ${VORBIS_enc_LIBRARY_NAMES} HINTS ${VORBIS_LIB_SEARCH_PATH} ${VORBIS_PKGC_LIBRARY_DIRS} ${VORBIS_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
find_library(VORBIS_enc_LIBRARY_DBG NAMES ${VORBIS_enc_LIBRARY_NAMES_DBG} HINTS ${VORBIS_LIB_SEARCH_PATH} ${VORBIS_PKGC_LIBRARY_DIRS} ${VORBIS_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "debug")
make_library_set(VORBIS_enc_LIBRARY)
findpkg_finish(VORBIS_enc)


set(VORBIS_LIBRARY_REL ${VORBIS_base_LIBRARY_REL} ${VORBIS_enc_LIBRARY_REL} ${VORBIS_file_LIBRARY_REL})
set(VORBIS_LIBRARY_DBG ${VORBIS_base_LIBRARY_DBG} ${VORBIS_enc_LIBRARY_DBG} ${VORBIS_file_LIBRARY_DBG})
set(VORBIS_LIBRARY ${VORBIS_base_LIBRARY} ${VORBIS_enc_LIBRARY} ${VORBIS_file_LIBRARY})
	

list(REMOVE_DUPLICATES VORBIS_INCLUDE_DIR)
findpkg_finish(VORBIS)
add_parent_dir(VORBIS_INCLUDE_DIRS VORBIS_INCLUDE_DIR)


if (NOT VORBIS_FOUND)
  return()
endif ()



get_filename_component(VORBIS_LIBRARY_DIR_REL "${VORBIS_LIBRARY_REL}" PATH)
get_filename_component(VORBIS_LIBRARY_DIR_DBG "${VORBIS_LIBRARY_DBG}" PATH)
set(VORBIS_LIBRARY_DIRS ${VORBIS_LIBRARY_DIR_REL} ${VORBIS_LIBRARY_DIR_DBG})


# find binaries
if (WIN32)
	find_file(VORBIS_BINARY_REL NAMES "libvorbis.dll" HINTS ${VORBIS_BIN_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
	find_file(VORBIS_BINARY_DBG NAMES "libvorbis_d.dll" HINTS ${VORBIS_BIN_SEARCH_PATH} PATH_SUFFIXES "" "debug" )
endif()
	
get_filename_component(VORBIS_BINARY_DIR_REL "${VORBIS_BINARY_REL}" PATH)
get_filename_component(VORBIS_BINARY_DIR_DBG "${VORBIS_BINARY_DBG}" PATH)

set(VORBIS_LIBRARY_DIRS ${VORBIS_BINARY_DIR_REL} ${VORBIS_BINARY_DIR_DBG})
mark_as_advanced(VORBIS_BINARY_REL VORBIS_BINARY_DBG VORBIS_BINARY_DIR_REL VORBIS_BINARY_DIR_DBG)


clear_if_changed(VORBIS_PREFIX_WATCH)
