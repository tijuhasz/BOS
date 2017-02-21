file(GLOB IMAGEHANDLING_HEADERS "${BOS_SOURCE_DIR}/include/ImageHandling/*.hpp")
file(GLOB IMAGEHANDLING_HEADERS_I "${BOS_SOURCE_DIR}/internal/ImageHandling/*.hpp")
file(GLOB IMAGEHANDLING_CFILES "${BOS_SOURCE_DIR}/src/ImageHandling/*.cpp")

set(ImageHandling_Sources "")
set(ImageHandling_Depend "")
set(ImageHandling_Link "")

list(APPEND ImageHandling_Sources ${IMAGEHANDLING_CFILES} ${IMAGEHANDLING_HEADERS} ${IMAGEHANDLING_HEADERS_I} ${VersionFiles})

add_library(ImageHandling ${ImageHandling_Sources})
add_dependencies(ImageHandling Utilities)

SET_PROPERTY(TARGET ImageHandling PROPERTY FOLDER "${BOS_VS_PREFIX}Modules")