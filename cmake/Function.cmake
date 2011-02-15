
#Macro pour copier les dll !

#Copie par fichier
macro(copyFile src destDir)
	get_filename_component(fileName "${src}" NAME)
	execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "${src}" "${destDir}/${fileName}")
endmacro(copyFile)

#Copie par dossier
macro(copyFiles srcDir destDir) 
	make_directory(${destDir})
	file(COPY "${srcDir}" DESTINATION "${destDir}" REGEX "[._]svn" EXCLUDE)
endmacro(copyFiles)

#Copie par dossier
macro(copyFilesFilter srcDir destDir filterExclude) 
	make_directory(${destDir})
	file(COPY "${srcDir}" DESTINATION "${destDir}" REGEX "${filterExclude}" EXCLUDE)
endmacro(copyFilesFilter)


#Ecrie un fichier de plugins
macro(writePluginFile destDir isDebug)
	make_directory(${destDir})
	
	IF(${isDebug} EQUAL 0)
		set(SUFFIXE_DEBUG "")
		set(END_VAR_TYPE "REL")
	ELSE(${isDebug} EQUAL 0)
		set(SUFFIXE_DEBUG "_d")
		set(END_VAR_TYPE "DBG")
	ENDIF(${isDebug} EQUAL 0)
	
	set(FILE_DEST "${destDir}/plugins${SUFFIXE_DEBUG}.cfg")
	
	file(WRITE ${FILE_DEST} "# Defines plugins to load\n\n# Define plugin folder\n")
	
	IF(WIN32)
		file(APPEND ${FILE_DEST} "	PluginFolder=${OGRE_PLUGIN_DIR_${END_VAR_TYPE}}\n")
	ELSE(WIN32)
		STRING(REPLACE "RenderSystem_GL.so" "" LIB_DIR ${OGRE_RenderSystem_GL_LIBRARY_REL})
		file(APPEND ${FILE_DEST} "	PluginFolder=${LIB_DIR}\n")
	ENDIF(WIN32)

	file(APPEND ${FILE_DEST} "\n# Defines plugins\n")
	file(APPEND ${FILE_DEST} "	")
	IF(NOT OGRE_RenderSystem_Direct3D9_LIBRARY_${END_VAR_TYPE})
		file(APPEND ${FILE_DEST} "# ")
	ENDIF(NOT OGRE_RenderSystem_Direct3D9_LIBRARY_${END_VAR_TYPE})
	file(APPEND ${FILE_DEST} "Plugin=RenderSystem_Direct3D9${SUFFIXE_DEBUG}\n")
	
	file(APPEND ${FILE_DEST} "	")
	IF(NOT OGRE_RenderSystem_Direct3D10_LIBRARY_${END_VAR_TYPE})
		file(APPEND ${FILE_DEST} "# ")
	ENDIF(NOT OGRE_RenderSystem_Direct3D10_LIBRARY_${END_VAR_TYPE})
	file(APPEND ${FILE_DEST} "Plugin=RenderSystem_Direct3D10${SUFFIXE_DEBUG}\n")
	
	file(APPEND ${FILE_DEST} "	")
	IF(NOT OGRE_RenderSystem_Direct3D11_LIBRARY_${END_VAR_TYPE})
		file(APPEND ${FILE_DEST} "# ")
	ENDIF(NOT OGRE_RenderSystem_Direct3D11_LIBRARY_${END_VAR_TYPE})
	file(APPEND ${FILE_DEST} "Plugin=RenderSystem_Direct3D11${SUFFIXE_DEBUG}\n")
	
	file(APPEND ${FILE_DEST} "	")
	IF(NOT OGRE_RenderSystem_GL_LIBRARY_${END_VAR_TYPE})
		file(APPEND ${FILE_DEST} "# ")
	ENDIF(NOT OGRE_RenderSystem_GL_LIBRARY_${END_VAR_TYPE})
	file(APPEND ${FILE_DEST} "Plugin=RenderSystem_GL${SUFFIXE_DEBUG}\n")
	
	file(APPEND ${FILE_DEST} "	")
	IF(NOT OGRE_RenderSystem_GLES_LIBRARY_${END_VAR_TYPE})
		file(APPEND ${FILE_DEST} "# ")
	ENDIF(NOT OGRE_RenderSystem_GLES_LIBRARY_${END_VAR_TYPE})
	file(APPEND ${FILE_DEST} "Plugin=RenderSystem_GLES${SUFFIXE_DEBUG}\n")
	
	file(APPEND ${FILE_DEST} "\n")
	
	file(APPEND ${FILE_DEST} "	")
	IF(NOT OGRE_Plugin_ParticleFX_LIBRARY_${END_VAR_TYPE})
		file(APPEND ${FILE_DEST} "# ")
	ENDIF(NOT OGRE_Plugin_ParticleFX_LIBRARY_${END_VAR_TYPE})
	file(APPEND ${FILE_DEST} "Plugin=Plugin_ParticleFX${SUFFIXE_DEBUG}\n")
	
	file(APPEND ${FILE_DEST} "	")
	IF(NOT OGRE_Plugin_BSPSceneManager_LIBRARY_${END_VAR_TYPE})
		file(APPEND ${FILE_DEST} "# ")
	ENDIF(NOT OGRE_Plugin_BSPSceneManager_LIBRARY_${END_VAR_TYPE})
	file(APPEND ${FILE_DEST} "Plugin=Plugin_BSPSceneManager${SUFFIXE_DEBUG}\n")
	
	file(APPEND ${FILE_DEST} "	")
	IF(NOT OGRE_Plugin_CgProgramManager_LIBRARY_${END_VAR_TYPE})
		file(APPEND ${FILE_DEST} "# ")
	ENDIF(NOT OGRE_Plugin_CgProgramManager_LIBRARY_${END_VAR_TYPE})
	file(APPEND ${FILE_DEST} "Plugin=Plugin_CgProgramManager${SUFFIXE_DEBUG}\n")
	
	file(APPEND ${FILE_DEST} "	")
	IF(NOT OGRE_Plugin_PCZSceneManager_LIBRARY_${END_VAR_TYPE})
		file(APPEND ${FILE_DEST} "# ")
	ENDIF(NOT OGRE_Plugin_PCZSceneManager_LIBRARY_${END_VAR_TYPE})
	file(APPEND ${FILE_DEST} "Plugin=Plugin_PCZSceneManager${SUFFIXE_DEBUG}\n")
	
	file(APPEND ${FILE_DEST} "	")
	IF(NOT OGRE_Plugin_OctreeZone_LIBRARY_${END_VAR_TYPE})
		file(APPEND ${FILE_DEST} "# ")
	ENDIF(NOT OGRE_Plugin_OctreeZone_LIBRARY_${END_VAR_TYPE})
	file(APPEND ${FILE_DEST} "Plugin=Plugin_OctreeZone${SUFFIXE_DEBUG}\n")
	
	file(APPEND ${FILE_DEST} "	")
	IF(NOT OGRE_Plugin_OctreeSceneManager_LIBRARY_${END_VAR_TYPE})
		file(APPEND ${FILE_DEST} "# ")
	ENDIF(NOT OGRE_Plugin_OctreeSceneManager_LIBRARY_${END_VAR_TYPE})
	file(APPEND ${FILE_DEST} "Plugin=Plugin_OctreeSceneManager${SUFFIXE_DEBUG}\n")
	
endmacro(writePluginFile)



#Ecrie un fichier de ressource
macro(writeResourceFile destDir isDebug)
	make_directory(${destDir})

	IF(${isDebug} EQUAL 0)
		set(FILE_DEST "${destDir}/resources.cfg")
	ELSE(${isDebug} EQUAL 0)
		set(FILE_DEST "${destDir}/resources_d.cfg")
	ENDIF(${isDebug} EQUAL 0)
	
	file(WRITE ${FILE_DEST} "[General]\n")
	file(APPEND ${FILE_DEST} "FileSystem=${CMAKE_SOURCE_DIR}/media\n")
	file(APPEND ${FILE_DEST} "FileSystem=${CMAKE_SOURCE_DIR}/media/ogre\n")	
	file(APPEND ${FILE_DEST} "Zip=${CMAKE_SOURCE_DIR}/media/packs/OgreCore.zip\n")
	file(APPEND ${FILE_DEST} "[Popular]\n")
	file(APPEND ${FILE_DEST} "FileSystem=${CMAKE_SOURCE_DIR}/media/materials/scripts\n")
	file(APPEND ${FILE_DEST} "FileSystem=${CMAKE_SOURCE_DIR}/media/materials/textures\n")
	file(APPEND ${FILE_DEST} "FileSystem=${CMAKE_SOURCE_DIR}/media/materials/shaders\n")
	file(APPEND ${FILE_DEST} "FileSystem=${CMAKE_SOURCE_DIR}/media/models\n")
	file(APPEND ${FILE_DEST} "FileSystem=${CMAKE_SOURCE_DIR}/media/particle\n")
	file(APPEND ${FILE_DEST} "Zip=${CMAKE_SOURCE_DIR}/media/packs/skybox.zip\n")	
	file(APPEND ${FILE_DEST} "[Imagesets]\n")
	file(APPEND ${FILE_DEST} "FileSystem=${CMAKE_SOURCE_DIR}/cegui/imagesets\n")	
   	file(APPEND ${FILE_DEST} "[Fonts]\n")
	file(APPEND ${FILE_DEST} "FileSystem=${CMAKE_SOURCE_DIR}/cegui/fonts\n")	
	file(APPEND ${FILE_DEST} "[LookNFeel]\n")
	file(APPEND ${FILE_DEST} "FileSystem=${CMAKE_SOURCE_DIR}/cegui/looknfeel\n")	
    file(APPEND ${FILE_DEST} "[Schemes]\n")
	file(APPEND ${FILE_DEST} "FileSystem=${CMAKE_SOURCE_DIR}/cegui/schemes\n")	
	file(APPEND ${FILE_DEST} "[Layouts]\n")
	file(APPEND ${FILE_DEST} "FileSystem=${CMAKE_SOURCE_DIR}/cegui/layouts\n")	
endmacro(writeResourceFile)
