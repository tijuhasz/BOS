if(NOT BOS_SINGLE_DLL)
	project (BOS)
endif()

file(GLOB UTILITIES_HEADERS "${BOS_SOURCE_DIR}/include/Utilities/*.hpp")
file(GLOB UTILITIES_HEADERS_I "${BOS_SOURCE_DIR}/internal/Utilities/*.hpp")
file(GLOB UTILITIES_CFILES "${BOS_SOURCE_DIR}/src/Utilities/*.cpp")

set(Utilities_Sources "")
set(Utilities_Depend "")
set(Utilities_Link "")

list(APPEND Utilities_Sources ${UTILITIES_CFILES} ${UTILITIES_HEADERS} ${UTILITIES_HEADERS_I} ${VersionFiles})

add_library(Utilities ${Utilities_Sources})

SET_PROPERTY(TARGET Utilities PROPERTY FOLDER "${BOS_VS_PREFIX}Modules")