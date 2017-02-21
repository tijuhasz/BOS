file(GLOB HEADERS *.hpp)
file(GLOB CFILES *.cpp)

add_library (Test_ColorBox ${CFILES} ${HEADERS})
target_link_libraries (Test_ColorBox
						Utilities
						ImageHandling
						ImageProcessing
						${Boost_LIBRARIES})

SET_PROPERTY(TARGET Test_ColorBox PROPERTY FOLDER "${BOS_VS_PREFIX}Tests")

