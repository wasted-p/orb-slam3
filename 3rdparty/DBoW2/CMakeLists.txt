cmake_minimum_required(VERSION 3.8)
project(DBoW2)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "DBoW2 Build Type: ${CMAKE_BUILD_TYPE}")

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -march=native")

# Source files
set(SRCS_DBOW2
  DBoW2/BowVector.cpp
  DBoW2/FORB.cpp
  DBoW2/FeatureVector.cpp
  DBoW2/ScoringObject.cpp
)
set(SRCS_DUTILS
  DUtils/Random.cpp
  DUtils/Timestamp.cpp
)
set(HDRS_DBOW2
  DBoW2/BowVector.h
  DBoW2/FORB.h
  DBoW2/FClass.h
  DBoW2/FeatureVector.h
  DBoW2/ScoringObject.h
  DBoW2/TemplatedVocabulary.h
)
set(HDRS_DUTILS
  DUtils/Random.h
  DUtils/Timestamp.h
)

# Find OpenCV (v4 preferred, fallback to v3)
find_package(OpenCV 4 QUIET)
if(NOT OpenCV_FOUND)
  find_package(OpenCV 3 REQUIRED)
endif()

message(STATUS "Using OpenCV version: ${OpenCV_VERSION}")

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Create shared library
add_library(DBoW2 SHARED
  ${SRCS_DBOW2}
  ${SRCS_DUTILS}
  ${HDRS_DBOW2}
  ${HDRS_DUTILS}
)

# Include paths (PUBLIC to propagate to targets using DBoW2)
target_include_directories(DBoW2
  PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/DBoW2
    ${PROJECT_SOURCE_DIR}/DUtils
    ${OpenCV_INCLUDE_DIRS}
)

# Link OpenCV
target_link_libraries(DBoW2 PUBLIC ${OpenCV_LIBS})
