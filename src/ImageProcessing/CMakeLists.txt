file(GLOB IMAGEPROCESSING_HEADERS "${BOS_SOURCE_DIR}/include/ImageProcessing/*.hpp")
file(GLOB IMAGEPROCESSING_HEADERS_I "${BOS_SOURCE_DIR}/internal/ImageProcessing/*.hpp")
file(GLOB IMAGEPROCESSING_CFILES "${BOS_SOURCE_DIR}/src/ImageProcessing/*.cpp")

set(ImageProcessing_Sources "")
set(ImageProcessing_Depend "")
set(ImageProcessing_Link "")

list(APPEND ImageProcessing_Sources ${IMAGEPROCESSING_CFILES} ${IMAGEPROCESSING_HEADERS} ${IMAGEPROCESSING_HEADERS_I} ${VersionFiles})

add_library(ImageProcessing ${ImageProcessing_Sources})
add_dependencies(ImageProcessing ImageHandling)

SET_PROPERTY(TARGET ImageProcessing PROPERTY FOLDER "${BOS_VS_PREFIX}Modules")