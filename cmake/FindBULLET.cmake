# - Locate BULLET LIBRARIES
# This module defines
#  BULLET_FOUND, if false, do not try to link to BULLET
#  BULLET_INCLUDE_DIR, where to find headers.
#  BULLET_LIBRARIES, the LIBRARIES to link against
#  BULLET_BINARY_REL - location of the main bullet binary (release)
#  BULLET_BINARY_DBG - location of the main bullet binaries (debug)


include(FindPkgMacros)
include(PreprocessorUtils)
findpkg_begin(BULLET)
set(BULLET_FIND_REQUIRED 1)

# Get path, convert backslashes as ${ENV_${var}}
getenv_path(BULLET_HOME)
getenv_path(BULLET_DIR)
getenv_path(BULLET_ROOT)
getenv_path(PROGRAMFILES)


set(BULLET_LIBRARY_NAMES "BulletCollision")
set(BULLET_LIST_LIBRARY_REQUIRED_NAMES BulletCollision BulletDynamics BulletSoftBody LinearMath)
set(BULLET_LIST_LIBRARY_NAMES BulletMultiThreaded MiniCL ConvexDecomposition GIMPACTUtils OpenGLSupport glui BulletSoftBodySolvers_CPU BulletSoftBodySolvers_OpenCL_Mini BulletWorldImporter BulletFileLoader BulletMultiThreaded)
get_debug_names(BULLET_LIBRARY_NAMES)

# construct search paths from environmental hints and
# OS specific guesses
if (WIN32)
  set(BULLET_PREFIX_GUESSES
    ${ENV_PROGRAMFILES}/bullet
    ${ENV_PROGRAMFILES}/BULLET
    C:/lib/bullet
    C:/BULLET-SDK
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;BULLET_HOME]
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;BULLET_DIR]
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;BULLET_ROOT]
  )
elseif (UNIX)
  set(BULLET_PREFIX_GUESSES
    /opt/bullet
    /opt/BULLET
    /usr
    /usr/local
    $ENV{HOME}/bullet
    $ENV{HOME}/BULLET
  )
endif ()

set(BULLET_PREFIX_PATH
	$ENV{BULLET_HOME} $ENV{BULLET_DIR} $ENV{BULLET_ROOT}
	${BULLET_PREFIX_GUESSES}
)

create_search_paths(BULLET)


set(BULLET_RESET_VARS 
  BULLET_INCLUDE_DIR 
  BULLET_LIBRARY_REL BULLET_LIBRARY_DBG)

set(BULLET_PREFIX_WATCH ${BULLET_PREFIX_PATH})
clear_if_changed(BULLET_PREFIX_WATCH ${BULLET_RESET_VARS})

# try to locate BULLET via pkg-config
use_pkgconfig(BULLET_PKGC "bullet")

# locate BULLET include files
find_path(BULLET_INCLUDE_DIR NAMES btBulletDynamicsCommon.h HINTS ${BULLET_INC_SEARCH_PATH} ${BULLET_FRAMEWORK_INCLUDES} ${BULLET_PKGC_INCLUDE_DIRS})

if (BULLET_INCLUDE_DIR)
  # determine BULLET version
  file(READ ${BULLET_INCLUDE_DIR}/LinearMath/btScalar.h BULLET_TEMP_VERSION_CONTENT)
  get_preprocessor_entry(BULLET_TEMP_VERSION_CONTENT BULLET_VERSION_MAJOR BT_BULLET_VERSION)
  set(BULLET_VERSION "${BT_BULLET_VERSION}")
  pkg_message(BULLET "Found BULLET (${BULLET_VERSION})")
endif ()

find_library(BULLET_LIBRARY_REL NAMES ${BULLET_LIBRARY_NAMES} HINTS ${BULLET_LIB_SEARCH_PATH} ${BULLET_PKGC_LIBRARY_DIRS} ${BULLET_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
find_library(BULLET_LIBRARY_DBG NAMES ${BULLET_LIBRARY_NAMES_DBG} HINTS ${BULLET_LIB_SEARCH_PATH} ${BULLET_PKGC_LIBRARY_DIRS} ${BULLET_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "debug")

make_library_set(BULLET_LIBRARY)

foreach (comp ${BULLET_LIST_LIBRARY_REQUIRED_NAMES})
	set(BULLET_${comp}_FIND_REQUIRED)
	findpkg_begin(BULLET_${comp})
	set(BULLET_${comp}_INCLUDE_DIR ${BULLET_INCLUDE_DIR})
	set(BULLET_${comp}_LIBRARY_NAMES "${comp}")
	get_debug_names(BULLET_${comp}_LIBRARY_NAMES)
	find_library(BULLET_${comp}_LIBRARY_REL NAMES ${BULLET_${comp}_LIBRARY_NAMES} HINTS ${BULLET_LIB_SEARCH_PATH} ${BULLET_PKGC_LIBRARY_DIRS} ${BULLET_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
	find_library(BULLET_${comp}_LIBRARY_DBG NAMES ${BULLET_${comp}_LIBRARY_NAMES_DBG} HINTS ${BULLET_LIB_SEARCH_PATH} ${BULLET_PKGC_LIBRARY_DIRS} ${BULLET_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "debug")
		
	make_library_set(BULLET_${comp}_LIBRARY)
	findpkg_finish(BULLET_${comp})
endforeach (comp)


set(BULLET_LIBRARY_REL)
set(BULLET_LIBRARY_DBG)
set(BULLET_LIBRARY)
foreach (comp ${BULLET_LIST_LIBRARY_REQUIRED_NAMES})
	set(BULLET_LIBRARY_REL ${BULLET_LIBRARY_REL} ${BULLET_${comp}_LIBRARY_REL})
	set(BULLET_LIBRARY_DBG ${BULLET_LIBRARY_DBG} ${BULLET_${comp}_LIBRARY_DBG})
	set(BULLET_LIBRARY ${BULLET_LIBRARY} ${BULLET_${comp}_LIBRARY})
endforeach (comp)




foreach (comp ${BULLET_LIST_LIBRARY_NAMES})
	findpkg_begin(BULLET_${comp})
	set(BULLET_${comp}_INCLUDE_DIR ${BULLET_INCLUDE_DIR})
	set(BULLET_${comp}_LIBRARY_NAMES "${comp}")
	get_debug_names(BULLET_${comp}_LIBRARY_NAMES)
	find_library(BULLET_${comp}_LIBRARY_REL NAMES ${BULLET_${comp}_LIBRARY_NAMES} HINTS ${BULLET_LIB_SEARCH_PATH} ${BULLET_PKGC_LIBRARY_DIRS} ${BULLET_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
	find_library(BULLET_${comp}_LIBRARY_DBG NAMES ${BULLET_${comp}_LIBRARY_NAMES_DBG} HINTS ${BULLET_LIB_SEARCH_PATH} ${BULLET_PKGC_LIBRARY_DIRS} ${BULLET_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "debug")
		
	make_library_set(BULLET_${comp}_LIBRARY)
	findpkg_finish(BULLET_${comp})
endforeach (comp)


list(REMOVE_DUPLICATES BULLET_INCLUDE_DIR)
findpkg_finish(BULLET)
add_parent_dir(BULLET_INCLUDE_DIRS BULLET_INCLUDE_DIR)


if (NOT BULLET_FOUND)
  return()
endif ()


get_filename_component(BULLET_LIBRARY_DIR_REL "${BULLET_LIBRARY_REL}" PATH)
get_filename_component(BULLET_LIBRARY_DIR_DBG "${BULLET_LIBRARY_DBG}" PATH)
set(BULLET_LIBRARY_DIRS ${BULLET_LIBRARY_DIR_REL} ${BULLET_LIBRARY_DIR_DBG})

# find binaries
if (WIN32)
	find_file(BULLET_BINARY_REL NAMES "BulletCollision.dll" HINTS ${BULLET_BIN_SEARCH_PATH}
	  PATH_SUFFIXES "" release relwithdebinfo minsizerel)
	find_file(BULLET_BINARY_DBG NAMES "BulletCollision_d.dll" HINTS ${BULLET_BIN_SEARCH_PATH}
	  PATH_SUFFIXES "" debug )
endif()

get_filename_component(BULLET_BINARY_DIR_REL "${BULLET_BINARY_REL}" PATH)
get_filename_component(BULLET_BINARY_DIR_DBG "${BULLET_BINARY_DBG}" PATH)
set(BULLET_LIBRARY_DIRS ${BULLET_BINARY_DIR_REL} ${BULLET_BINARY_DIR_DBG})
mark_as_advanced(BULLET_BINARY_REL BULLET_BINARY_DBG BULLET_BINARY_DIR_REL BULLET_BINARY_DIR_DBG)


clear_if_changed(BULLET_PREFIX_WATCH)
