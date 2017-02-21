cmake_minimum_required(VERSION 2.6)
project (BOS)

add_subdirectory (Utilities) 

if(NOT EXCLUDE_IMAGEHANDLING)
	add_subdirectory (ImageHandling) 
else()
	message(STATUS "excluding imagehandling from solution")
endif()

if(NOT EXCLUDE_IMAGEPROCESSING)
	add_subdirectory (ImageProcessing) 
else()
	message(STATUS "excluding imageprocessing from solution")
endif()