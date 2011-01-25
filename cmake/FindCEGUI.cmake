# - Locate CEGUI library
# This module defines
#  CEGUI_INCLUDE_DIR, where to find headers.
#  CEGUI_LIBRARIES, the library to link against
#  CEGUI_FOUND, if false, do not try to link to CEGUI

FIND_PATH(CEGUI_INCLUDE_DIR
CEGUI
PATHS
$ENV{CEGUI_DIR}/include
/usr/local/include
/usr/include
/sw/include
/opt/local/include
/opt/csw/include
/opt/include
PATH_SUFFIXES cegui CEGUI
)

FIND_LIBRARY(CEGUI_LIBRARIES
NAMES CEGUIBase
PATHS
$ENV{CEGUI_DIR}/lib
/usr/local/lib
/usr/lib
/usr/local/X11R6/lib
/usr/X11R6/lib
/sw/lib
/opt/local/lib
/opt/csw/lib
/opt/lib
/usr/freeware/lib64
)

MESSAGE(STATUS "Looking for CEGUI...")
IF(CEGUI_LIBRARIES AND CEGUI_INCLUDE_DIR)
SET(CEGUI_FOUND "YES")
SET(CEGUI_INCLUDE_DIR "${CEGUI_INCLUDE_DIR}/CEGUI")
	MESSAGE(STATUS "Found CEGUI: ${CEGUI_LIBRARIES}")
ELSE(CEGUI_LIBRARIES AND CEGUI_INCLUDE_DIR)
	MESSAGE(STATUS "Warning: Unable to find CEGUI!")
ENDIF(CEGUI_LIBRARIES AND CEGUI_INCLUDE_DIR)
