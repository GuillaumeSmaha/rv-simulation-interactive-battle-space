# - Locate OGG LIBRARIES
# This module defines
#  OGG_FOUND, if false, do not try to link to OGG
#  OGG_INCLUDE_DIR, where to find headers.
#  OGG_LIBRARIES, the LIBRARIES to link against
#  OGG_BINARY_REL - location of the main bullet binary (release)
#  OGG_BINARY_DBG - location of the main bullet binaries (debug)


include(FindPkgMacros)
include(PreprocessorUtils)
findpkg_begin(OGG)
set(OGG_FIND_REQUIRED 1)

# Get path, convert backslashes as ${ENV_${var}}
getenv_path(OGG_HOME)
getenv_path(OGG_DIR)
getenv_path(OGG_ROOT)
getenv_path(PROGRAMFILES)


set(OGG_LIBRARY_NAMES "ogg")
if (WIN32)
	set(OGG_LIBRARY_NAMES "libogg")
endif (WIN32)

# construct search paths from environmental hints and
# OS specific guesses
if (WIN32)
  set(OGG_PREFIX_GUESSES
    ${ENV_PROGRAMFILES}/ogg
    ${ENV_PROGRAMFILES}/OGG
    C:/OGG-SDK
    C:/lib/ogg
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OGG_HOME]
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OGG_DIR]
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OGG_ROOT]
  )
elseif (UNIX)
  set(OGG_PREFIX_GUESSES
    /opt/ogg
    /opt/OGG
    /usr
    /usr/local
    $ENV{HOME}/ogg
    $ENV{HOME}/OGG
  )
endif ()

set(OGG_PREFIX_PATH
	$ENV{OGG_HOME} $ENV{OGG_DIR} $ENV{OGG_ROOT}
	${OGG_PREFIX_GUESSES}
)
create_search_paths(OGG)


set(OGG_RESET_VARS 
  OGG_INCLUDE_DIR 
  OGG_LIBRARY_REL OGG_LIBRARY_DBG)

set(OGG_PREFIX_WATCH ${OGG_PREFIX_PATH})
clear_if_changed(OGG_PREFIX_WATCH ${OGG_RESET_VARS})

# try to locate OGG via pkg-config
use_pkgconfig(OGG_PKGC "ogg")

# locate OGG include files

find_path(OGG_INCLUDE_DIR NAMES ogg/ogg.h HINTS ${OGG_INC_SEARCH_PATH} ${OGG_FRAMEWORK_INCLUDES} ${OGG_PKGC_INCLUDE_DIRS})
get_debug_names(OGG_LIBRARY_NAMES)
find_library(OGG_LIBRARY_REL NAMES ${OGG_LIBRARY_NAMES} HINTS ${OGG_LIB_SEARCH_PATH} ${OGG_PKGC_LIBRARY_DIRS} ${OGG_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
find_library(OGG_LIBRARY_DBG NAMES ${OGG_LIBRARY_NAMES_DBG} HINTS ${OGG_LIB_SEARCH_PATH} ${OGG_PKGC_LIBRARY_DIRS} ${OGG_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "debug")
make_library_set(OGG_LIBRARY)


list(REMOVE_DUPLICATES OGG_INCLUDE_DIR)
findpkg_finish(OGG)
add_parent_dir(OGG_INCLUDE_DIRS OGG_INCLUDE_DIR)


if (NOT OGG_FOUND)
  return()
endif ()



get_filename_component(OGG_LIBRARY_DIR_REL "${OGG_LIBRARY_REL}" PATH)
get_filename_component(OGG_LIBRARY_DIR_DBG "${OGG_LIBRARY_DBG}" PATH)
set(OGG_LIBRARY_DIRS ${OGG_LIBRARY_DIR_REL} ${OGG_LIBRARY_DIR_DBG})


# find binaries
if (WIN32)
	find_file(OGG_BINARY_REL NAMES "libogg.dll" HINTS ${OGG_BIN_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
	find_file(OGG_BINARY_DBG NAMES "libogg_d.dll" HINTS ${OGG_BIN_SEARCH_PATH} PATH_SUFFIXES "" "debug" )
endif()
	
get_filename_component(OGG_BINARY_DIR_REL "${OGG_BINARY_REL}" PATH)
get_filename_component(OGG_BINARY_DIR_DBG "${OGG_BINARY_DBG}" PATH)
set(OGG_LIBRARY_DIRS ${OGG_BINARY_DIR_REL} ${OGG_BINARY_DIR_DBG})
mark_as_advanced(OGG_BINARY_REL OGG_BINARY_DBG OGG_BINARY_DIR_REL OGG_BINARY_DIR_DBG)


clear_if_changed(OGG_PREFIX_WATCH)
