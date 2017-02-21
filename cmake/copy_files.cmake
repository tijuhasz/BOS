function(copy_file targetname filename targetfilename)
	add_custom_command(TARGET "${targetname}" COMMAND ${CMAKE_COMMAND} -E copy_if_different "${filename}" "${CMAKE_CURRENT_BINARY_DIR}/${targetfilename}")
#	install(FILES "${filename}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/${targetfilename}")
#	message(STATUS "Install (${filename} to = ${CMAKE_CURRENT_BINARY_DIR}/${targetfilename}")
endfunction (copy_file)

# function(copy_directory targetname directoryname targetdirectoryname)
	# add_custom_command(TARGET "${targetname}" COMMAND ${CMAKE_COMMAND} -E copy_directory "${directoryname}" "${CMAKE_CURRENT_BINARY_DIR}/${targetdirectoryname}")
# endfunction (copy_directory)

# function(copy_files_to_bin filename targetfilename)
	# if(NOT TARGET CopyFilesToBinaryDir)	
		# add_custom_target(CopyFilesToBinaryDir ALL COMMENT "Exporting files into build tree"
		# COMMAND ${CMAKE_COMMAND} -E copy_if_different "${filename}" "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/${targetfilename}"
		# DEPENDS ConfigFiles)
		# SET_PROPERTY(TARGET CopyFilesToBinaryDir PROPERTY FOLDER "CMakeCustomBuildSteps")
	# else()
		# add_custom_command(TARGET CopyFilesToBinaryDir COMMAND ${CMAKE_COMMAND} -E copy_if_different "${filename}" "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/${targetfilename}")
	# endif(NOT TARGET CopyFilesToBinaryDir)
# endfunction(copy_files_to_bin)

function(copy_files_to_bin_target targetname filename targetfilename)
	add_custom_command(TARGET ${targetname} COMMAND ${CMAKE_COMMAND} -E copy_if_different "${filename}" "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/${targetfilename}")
endfunction(copy_files_to_bin_target)

# function(copy_runtime_file targetname filename targetfilename)
	# copy_file(${targetname} ${filename} ${targetfilename})
	# copy_files_to_bin_target(${targetname} ${filename} ${targetfilename})
# endfunction (copy_runtime_file)

function(copy_project_file targetname filename targetfilename)
	copy_file(${targetname} ${filename} ${targetfilename})
	copy_files_to_bin_target(${targetname} ${filename} ${targetfilename})
endfunction (copy_project_file)

# function(copy_BOS_files targetname)
# # parameter file
	# copy_runtime_file(${targetname} "${BOS_Base_SOURCE_DIR}/externals/FirmwareDependencies/transform/samPara/samUserPara.xml" "samUserPara.xml")
	# copy_runtime_file(${targetname} "${BOS_Base_SOURCE_DIR}/externals/FirmwareDependencies/transform/samPara/samPara.xml" "samPara.xml")
# # configuration file
	# copy_runtime_file(${targetname} "${BOS_Base_SOURCE_DIR}/configfiles/configuration.xml" "configuration.xml")

# # files needed for compiling bs code
	# copy_runtime_file(${targetname} "${BOS_Base_SOURCE_DIR}/internal/FirmwareDependencies/Blocksequencer.h" "Blocksequencer.h")
	# copy_runtime_file(${targetname} "${BOS_Base_SOURCE_DIR}/configfiles/samParaDefs.h" "samParaDefs.h")
	# copy_runtime_file(${targetname} "${BOS_Base_SOURCE_DIR}/configfiles/samMsg.h" "samMsg.h")
# endfunction(copy_BOS_files)

# MACRO (copy_if_does_not_exist SOURCE DESTINATION)
	# IF(NOT EXISTS ${DESTINATION}) 
		# execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${SOURCE} ${DESTINATION})
	# ENDIF(NOT EXISTS ${DESTINATION})
# #	message(STATUS "Install-once! (${SOURCE} to = ${DESTINATION}")
# ENDMACRO (copy_if_does_not_exist SOURCE DESTINATION)

# MACRO(create_from_samples dir)
	# file(GLOB FILES "${dir}/sample_*")
	# foreach(source ${FILES})
		# string(REPLACE "/sample_" "/" target ${source})
		# copy_if_does_not_exist(${source} ${target})
	# endforeach()
# ENDMACRO(create_from_samples)