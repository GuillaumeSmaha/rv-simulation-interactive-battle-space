# - Locate CEGUI LIBRARIES
# This module defines
#  CEGUI_INCLUDE_DIR, where to find headers.
#  CEGUI_LIBRARIES, the LIBRARIES to link against
#  CEGUI_FOUND, if false, do not try to link to CEGUI
# 	Modules :
#  CEGUI_OGRE_LIBRARIES, the module OGRE LIBRARIES
#  CEGUI_OGRE_INCLUDE_DIR, where to find headers module OGRE.
#  CEGUI_OPENGL_LIBRARIES, the module OPENGL LIBRARIES
#  CEGUI_OPENGL_INCLUDE_DIR, where to find headers module OPENGL.

#  CEGUI_FALAGARD_LIBRARIES, the module FALAGARD LIBRARIES
#  CEGUI_FALAGARD_INCLUDE_DIR, where to find headers module FALAGARD.

#  CEGUI_SAMPLEHELPER_LIBRARIES, the module SAMPLEHELPER LIBRARIES

#  CEGUI_IMAGECODEC_FREEIMAGE_LIBRARIES, the module IMAGECODEC_FREEIMAGE LIBRARIES
#  CEGUI_IMAGECODEC_FREEIMAGE_INCLUDE_DIR, where to find headers module IMAGECODEC_FREEIMAGE.
#  CEGUI_IMAGECODEC_SILLY_LIBRARIES, the module IMAGECODEC_SILLY LIBRARIES
#  CEGUI_IMAGECODEC_SILLY_INCLUDE_DIR, where to find headers module IMAGECODEC_SILLY.
#  CEGUI_IMAGECODEC_STB_LIBRARIES, the module IMAGECODEC_STB LIBRARIES
#  CEGUI_IMAGECODEC_STB_INCLUDE_DIR, where to find headers module IMAGECODEC_STB.
#  CEGUI_IMAGECODEC_TGA_LIBRARIES, the module IMAGECODEC_TGA LIBRARIES
#  CEGUI_IMAGECODEC_TGA_INCLUDE_DIR, where to find headers module IMAGECODEC_TGA.

#  CEGUI_TINYXML_LIBRARIES, the module TINYXML LIBRARIES
#  CEGUI_TINYXML_INCLUDE_DIR, where to find headers module TINYXML.
#  CEGUI_EXPAT_LIBRARIES, the module TINYXML LIBRARIES
#  CEGUI_EXPAT_INCLUDE_DIR, where to find headers module TINYXML.


MACRO(FIND_CEGUI_LIBRARIES MYLIBRARIES MYLIBRARIESNAMES)
    FIND_LIBRARY(${MYLIBRARIES}
        NAMES ${MYLIBRARIESNAMES}
        PATHS
        $ENV{CEGUI_DIR}/lib
        $ENV{CEGUI_DIR}
        $ENV{CEGUIDIR}/lib
        $ENV{CEGUIDIR}
        $ENV{CEGUI_ROOT}/lib
        $ENV{CEGUI_HOME}
        $ENV{CEGUI_HOME}/lib
        ${DELTA3D_EXT_DIR}/lib
        $ENV{DELTA_ROOT}/ext/lib
        ~/LIBRARIES/Frameworks
        /LIBRARIES/Frameworks
        /usr/local/lib
        /usr/lib
        /usr/lib/cegui-0.7.1
        /sw/lib
        /opt/local/lib
        /opt/csw/lib
        /opt/lib
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;CEGUI_ROOT]/lib
        /usr/freeware/lib64
    )
ENDMACRO(FIND_CEGUI_LIBRARIES LIBRARIES LIBRARIESNAME)

FIND_PATH(CEGUI_INCLUDE_DIR
CEGUI
PATHS
$ENV{CEGUI_DIR}
$ENV{CEGUI_DIR}/include
$ENV{CEGUIDIR}
$ENV{CEGUIDIR}/include
$ENV{CEGUI_ROOT}
$ENV{CEGUI_ROOT}/include
$ENV{CEGUI_HOME}
$ENV{CEGUI_HOME}/include
/usr/local/include
/usr/include
/sw/include
/opt/local/include
/opt/csw/include
/opt/include
PATH_SUFFIXES cegui CEGUI
)

SET(CEGUIList CEGUIBase CEGUI)
FIND_CEGUI_LIBRARIES(CEGUI_LIBRARIES "${CEGUIList}")

SET(CEGUIOgreList OgreGUIRenderer CEGUIOgreRenderer)
FIND_CEGUI_LIBRARIES(CEGUI_OGRE_LIBRARIES "${CEGUIOgreList}")

SET(CEGUIOpenGLList OpenGLGUIRenderer CEGUIOpenGLRenderer)
FIND_CEGUI_LIBRARIES(CEGUI_OPENGL_LIBRARIES "${CEGUIOpenGLList}")

SET(CEGUIFalagardList CEGUIFalagardWRBase CEGUIFalagard)
FIND_CEGUI_LIBRARIES(CEGUI_FALAGARD_LIBRARIES "${CEGUIFalagardList}")

SET(CEGUISampleHelperList CEGUISampleHelp CEGUISampleHelper)
FIND_CEGUI_LIBRARIES(CEGUI_SAMPLEHELPER_LIBRARIES "${CEGUISampleHelperList}")

SET(CEGUIFreeImageList CEGUIFreeImageImageCodec CEGUIFreeImage)
FIND_CEGUI_LIBRARIES(CEGUI_IMAGECODEC_FREEIMAGE_LIBRARIES "${CEGUIFreeImageList}")

SET(CEGUISILLYList CEGUISILLYImageCodec CEGUISILLY)
FIND_CEGUI_LIBRARIES(CEGUI_IMAGECODEC_SILLY_LIBRARIES "${CEGUISILLYList}")

SET(CEGUISTBList CEGUISTBImageCodec CEGUISTB)
FIND_CEGUI_LIBRARIES(CEGUI_IMAGECODEC_STB_LIBRARIES "${CEGUISTBList}")

SET(CEGUITGAList CEGUITGAImageCodec CEGUITGA)
FIND_CEGUI_LIBRARIES(CEGUI_IMAGECODEC_TGA_LIBRARIES "${CEGUITGAList}")

SET(CEGUITinyXmlList CEGUITinyXMLParser CEGUITinyXML)
FIND_CEGUI_LIBRARIES(CEGUI_TINYXML_LIBRARIES "${CEGUITinyXmlList}")

SET(CEGUIExpatList CEGUIExpatParser CEGUITinyXML)
FIND_CEGUI_LIBRARIES(CEGUI_EXPAT_LIBRARIES "${CEGUIExpatList}")



#Debug
FIND_CEGUI_LIBRARIES(CEGUI_LIBRARIES_DEBUG CEGUIBase_d)
FIND_CEGUI_LIBRARIES(CEGUI_OPENGL_LIBRARIES_DEBUG OpenGLGUIRenderer_d)


MESSAGE(STATUS "Looking for CEGUI...")
IF(CEGUI_LIBRARIES AND CEGUI_INCLUDE_DIR)
	SET(CEGUI_FOUND "YES")
	SET(CEGUI_INCLUDE_DIR "${CEGUI_INCLUDE_DIR}/CEGUI")
	MESSAGE(STATUS "Found CEGUI: ${CEGUI_LIBRARIES}")
	
	IF(CEGUI_OGRE_LIBRARIES)
		MESSAGE(STATUS "-- Found CEGUI Ogre Renderer: ${CEGUI_OGRE_LIBRARIES}")
		SET(CEGUI_OGRE_INCLUDE_DIR "${CEGUI_INCLUDE_DIR}/CEGUI/RendererModules/Ogre")
	ENDIF(CEGUI_OGRE_LIBRARIES)
	
	IF(CEGUI_OPENGL_LIBRARIES)
		MESSAGE(STATUS "-- Found CEGUI OpenGL Renderer: ${CEGUI_OGRE_LIBRARIES}")
		SET(CEGUI_OPENGL_INCLUDE_DIR "${CEGUI_INCLUDE_DIR}/CEGUI/RendererModules/OpenGL")
	ENDIF(CEGUI_OPENGL_LIBRARIES)
	
	IF(CEGUI_FALAGARD_LIBRARIES)
		MESSAGE(STATUS "-- Found CEGUI Falagard: ${CEGUI_FALAGARD_LIBRARIES}")
		SET(CEGUI_FALAGARD_INCLUDE_DIR "${CEGUI_INCLUDE_DIR}/CEGUI/falagard")
	ENDIF(CEGUI_FALAGARD_LIBRARIES)
	
	IF(CEGUI_SAMPLEHELPER_LIBRARIES)
		MESSAGE(STATUS "-- Found CEGUI Sample Helper: ${CEGUI_SAMPLEHELPER_LIBRARIES}")
	ENDIF(CEGUI_SAMPLEHELPER_LIBRARIES)
	
	IF(CEGUI_IMAGECODEC_FREEIMAGE_LIBRARIES)
		MESSAGE(STATUS "-- Found CEGUI FreeImage ImageCodec: ${CEGUI_IMAGECODEC_FREEIMAGE_LIBRARIES}")
		SET(CEGUI_IMAGECODEC_FREEIMAGE_INCLUDE_DIR "${CEGUI_INCLUDE_DIR}/CEGUI/ImageCodecModules/FreeImageImageCodec")
	ENDIF(CEGUI_IMAGECODEC_FREEIMAGE_LIBRARIES)
	
	IF(CEGUI_IMAGECODEC_SILLY_LIBRARIES)
		MESSAGE(STATUS "-- Found CEGUI SILLY ImageCodec: ${CEGUI_IMAGECODEC_SILLY_LIBRARIES}")
		SET(CEGUI_IMAGECODEC_SILLY_INCLUDE_DIR "${CEGUI_INCLUDE_DIR}/CEGUI/ImageCodecModules/SILLYImageCodec")
	ENDIF(CEGUI_IMAGECODEC_SILLY_LIBRARIES)
	
	IF(CEGUI_IMAGECODEC_STB_LIBRARIES)
		MESSAGE(STATUS "-- Found CEGUI STB ImageCodec: ${CEGUI_IMAGECODEC_STB_LIBRARIES}")
		SET(CEGUI_IMAGECODEC_STB_INCLUDE_DIR "${CEGUI_INCLUDE_DIR}/CEGUI/ImageCodecModules/STBImageCodec")
	ENDIF(CEGUI_IMAGECODEC_STB_LIBRARIES)
	
	IF(CEGUI_IMAGECODEC_TGA_LIBRARIES)
		MESSAGE(STATUS "-- Found CEGUI TGA ImageCodec: ${CEGUI_IMAGECODEC_TGA_LIBRARIES}")
		SET(CEGUI_IMAGECODEC_TGA_INCLUDE_DIR "${CEGUI_INCLUDE_DIR}/CEGUI/ImageCodecModules/TGAImageCodec")
	ENDIF(CEGUI_IMAGECODEC_TGA_LIBRARIES)
	
	IF(CEGUI_TINYXML_LIBRARIES)
		MESSAGE(STATUS "-- Found CEGUI TinyXML Parser: ${CEGUI_TINYXML_LIBRARIES}")
		SET(CEGUI_TINYXML_INCLUDE_DIR "${CEGUI_INCLUDE_DIR}/CEGUI/XMLParserModules/TinyXMLParser")
	ENDIF(CEGUI_TINYXML_LIBRARIES)
	
	IF(CEGUI_EXPAT_LIBRARIES)
		MESSAGE(STATUS "-- Found CEGUI Expat Parser: ${CEGUI_EXPAT_LIBRARIES}")
		SET(CEGUI_EXPAT_INCLUDE_DIR "${CEGUI_INCLUDE_DIR}/CEGUI/XMLParserModules/ExpatParser")
	ENDIF(CEGUI_EXPAT_LIBRARIES)
	
	
ELSE(CEGUI_LIBRARIES AND CEGUI_INCLUDE_DIR)
	MESSAGE(STATUS "Warning: Unable to find CEGUI!")
ENDIF(CEGUI_LIBRARIES AND CEGUI_INCLUDE_DIR)
