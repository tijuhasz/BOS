file(GLOB HEADERS *.hpp)
file(GLOB CFILES *.cpp)

add_library (Test_BMPHandling ${CFILES} ${HEADERS})
target_link_libraries (Test_BMPHandling
						Utilities
						ImageHandling
						${Boost_LIBRARIES})

# copy data files
copy_project_file(Test_BMPHandling "${BOS_SOURCE_DIR}/test/Test_BMPHandling/ImgFiles/bmp1.bmp" "bmp1.bmp")
copy_project_file(Test_BMPHandling "${BOS_SOURCE_DIR}/test/Test_BMPHandling/ImgFiles/bmp1_w2831.bmp" "bmp1_w2831.bmp")

SET_PROPERTY(TARGET Test_BMPHandling PROPERTY FOLDER "${BOS_VS_PREFIX}Tests")

