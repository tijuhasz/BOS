file(GLOB HEADERS *.hpp)
file(GLOB CFILES *.cpp)

add_executable (Test_Runner ${CFILES} ${HEADERS})
target_link_libraries (Test_Runner
						Utilities
						ImageHandling
						ImageProcessing
						
						#Test_BMPHandling
						#Test_ColorBox
						#Test_SchlierenProcessing
						
						${Boost_LIBRARIES})

SET_PROPERTY(TARGET Test_Runner PROPERTY FOLDER "${BOS_VS_PREFIX}Tests")

