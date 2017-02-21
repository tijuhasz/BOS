cmake_minimum_required(VERSION 2.8.9)
project("BOS")

include("./cmake/declare_config.cmake")
include("./cmake/copy_files.cmake")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

DECL_CONFIG("EXCLUDE_IMAGEHANDLING" FALSE "Exclude ImageHandling from the project")
DECL_CONFIG("EXCLUDE_IMAGEPROCESSING" FALSE "Exclude ImageProcessing from the project")
DECL_CONFIG("WITH_TESTS" TRUE "Add/Ignore developer tests")
DECL_CONFIG("BOS_SINGLE_DLL" FALSE "Build ONE DLL containing everything")

# External settings - display them to the user
INFO_CONFIG("BOOST_INCLUDEDIR" "toolchain file" "include directory of boost")
INFO_CONFIG("BOOST_LIBRARYDIR" "toolchain file" "library directory of boost")
INFO_CONFIG("CMAKE_C_COMPILER" "toolchain file" "c compiler")
INFO_CONFIG("CMAKE_CXX_COMPILER" "toolchain file" "c++ compiler")
INFO_CONFIG("CMAKE_FIND_ROOT_PATH" "toolchain file" "root directory")
INFO_CONFIG("IS_BIG_ENDIAN" "system dependent" "endianess")
INFO_CONFIG("PLATFORM" "system dependent" "platform to build for")

include(src/Utilities/CMakeLists.txt)

if(NOT EXCLUDE_IMAGEHANDLING)
	include(src/ImageHandling/CMakeLists.txt)
endif()

if(NOT EXCLUDE_IMAGEPROCESSING)
	include(src/ImageProcessing/CMakeLists.txt)
endif()

# boost
#add_definitions( -DBOOST_ALL_DYN_LINK )
add_definitions( -DBOOST_ALL_NO_LIB )
set(Boost_NO_SYSTEM_PATHS OFF)
set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME ON)
#set(Boost_USE_DEBUG_RUNTIME ON)

find_package( Boost 
  COMPONENTS
  system program_options thread filesystem
  date_time chrono timer regex serialization
  REQUIRED )
include_directories(${Boost_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES})

if (WIN32)
  # disable autolinking in boost
  add_definitions( -DBOOST_ALL_NO_LIB )
  # force all boost libraries to dynamic link (we already disabled
  # autolinking, so I don't know why we need this, but we do!)
  add_definitions( -DBOOST_ALL_DYN_LINK )
endif()
# end boost

include_directories (${Boost_INCLUDE_DIRS})
include_directories (${BOS_SOURCE_DIR}/include)
include_directories (${BOS_SOURCE_DIR}/test)
#include_directories (${BOS_SOURCE_DIR})
#include_directories (${CMAKE_CURRENT_BINARY_DIR})
#include_directories (${THREADS_INCLUDE_DIRS})

add_library(BOS SHARED  ${Utilities_Sources}
						${ImageHandling_Sources}
						${ImageProcessing_Sources}	
			)
								
# add_dependencies(BOS ${Utilities_Depend}
					#  ${ImageHandling_Depend} 
					#  ${ImageProcessing_Depend}
				# )
							 
target_link_libraries(BOS ${Utilities_Link}	
						  ${ImageHandling_Link} 
						  ${ImageProcessing_Link}					  
						)		
 
if(WITH_TESTS)
	message(STATUS "Creating Tests." "")
	add_subdirectory(test)
endif()						