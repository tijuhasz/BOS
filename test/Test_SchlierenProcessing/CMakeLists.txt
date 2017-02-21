file(GLOB HEADERS *.hpp)
file(GLOB CFILES *.cpp)

add_library (Test_SchlierenProcessing ${CFILES} ${HEADERS})
target_link_libraries(Test_SchlierenProcessing 
						ImageHandling
						ImageProcessing
						${Boost_LIBRARIES})

copy_project_file(Test_SchlierenProcessing "${BOS_SOURCE_DIR}/test/Test_SchlierenProcessing/ImgFiles/reference_2968.bmp" "reference_2968.bmp")
copy_project_file(Test_SchlierenProcessing "${BOS_SOURCE_DIR}/test/Test_SchlierenProcessing/ImgFiles/process_2975.bmp" "process_2975.bmp")
copy_project_file(Test_SchlierenProcessing "${BOS_SOURCE_DIR}/test/Test_SchlierenProcessing/ImgFiles/process_2976.bmp" "process_2976.bmp")
copy_project_file(Test_SchlierenProcessing "${BOS_SOURCE_DIR}/test/Test_SchlierenProcessing/ImgFiles/process_2978.bmp" "process_2978.bmp")



if(UNIX)
	target_link_libraries(Test_SchlierenProcessing ${CMAKE_THREAD_LIBS_INIT})
endif()

SET_PROPERTY(TARGET Test_SchlierenProcessing PROPERTY FOLDER "${BOS_VS_PREFIX}Tests")

