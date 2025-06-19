cmake_minimum_required(VERSION 3.14)

project(ORB_SLAM3)

# ------------------------------
# Compiler settings
# ------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=native")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")

# ------------------------------
# CMake modules path
# ------------------------------
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

# ------------------------------
# Dependencies
# ------------------------------
find_package(OpenCV 4.6 REQUIRED COMPONENTS core imgproc calib3d highgui imgcodecs)
find_package(Eigen3 3.1.0 REQUIRED)
find_package(Pangolin REQUIRED)

message(STATUS "OpenCV version: ${OpenCV_VERSION}")

# ------------------------------
# Output directory for libraries
# ------------------------------
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# ------------------------------
# Source files
# ------------------------------
file(GLOB_RECURSE ORBSLAM3_SOURCES
    src/*.cc
    src/*.cpp
)
file(GLOB_RECURSE ORBSLAM3_HEADERS
    include/*.h
    include/*.hpp
)

# ------------------------------
# Add third-party libraries
# ------------------------------
add_subdirectory(3rdparty/g2o)
add_subdirectory(3rdparty/Sophus)
add_subdirectory(3rdparty/DBoW2)

# ------------------------------
# Define ORB_SLAM3 library
# ------------------------------
add_library(${PROJECT_NAME} SHARED
    ${ORBSLAM3_SOURCES}
    ${ORBSLAM3_HEADERS}
)

# ------------------------------
# Include directories
# ------------------------------
target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/3rdparty
    ${OpenCV_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS}
    ${Pangolin_INCLUDE_DIRS}
)

# ------------------------------
# Link libraries
# ------------------------------
target_link_libraries(${PROJECT_NAME}
    g2o
    Sophus
    DBoW2
    ${OpenCV_LIBS}
    ${EIGEN3_LIBS}
    ${Pangolin_LIBRARIES}
    # ${PROJECT_SOURCE_DIR}/Thirdparty/DBoW2/lib/libDBoW2.so
    -lboost_serialization
    -lcrypto
)

##### Old Code
#
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=native")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
#
# # Module path
# list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
#
# # Find dependencies
# find_package(OpenCV 4.6 REQUIRED COMPONENTS core imgproc calib3d highgui imgcodecs)
# if(NOT OpenCV_FOUND)
#   message(FATAL_ERROR "OpenCV > 4.4 not found.")
# endif()
#
# project(ORB_SLAM3)
#
# IF(NOT CMAKE_BUILD_TYPE)
#   SET(CMAKE_BUILD_TYPE Release)
# ENDIF()
#
# MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})
#
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall   -O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=native")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
#
# LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
#
# find_package(OpenCV 4.6 REQUIRED COMPONENTS core imgproc calib3d highgui imgcodecs)
# if(NOT OpenCV_FOUND)
#   message(FATAL_ERROR "OpenCV > 4.4 not found.")
# endif()
#
# MESSAGE("OPENCV VERSION:")
# MESSAGE(${OpenCV_VERSION})
#
# find_package(Eigen3 3.1.0 REQUIRED)
# find_package(Pangolin REQUIRED)
#
#
# target_include_directories(${PROJECT_NAME}
#   PUBLIC
#     ${PROJECT_SOURCE_DIR}/include
#     ${PROJECT_SOURCE_DIR}/Thirdparty/Sophus
#     ${OpenCV_INCLUDE_DIRS}
#     ${EIGEN3_INCLUDE_DIR}
#     ${Pangolin_INCLUDE_DIRS}
# )
#
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
#
# # Glob all source files
# file(GLOB_RECURSE ORBSLAM3_SOURCES
#     src/*.cc
#     src/*.cpp
# )
#
# # Glob all header files
# file(GLOB_RECURSE ORBSLAM3_HEADERS
#     include/*.h
#     include/*.hpp
# )
#
# # Add the shared library
# add_library(${PROJECT_NAME} SHARED
#     ${ORBSLAM3_SOURCES}
#     ${ORBSLAM3_HEADERS}
# )
#
# add_subdirectory(Thirdparty/g2o)
#
# target_link_libraries(${PROJECT_NAME}
# ${OpenCV_LIBS}
# ${EIGEN3_LIBS}
# ${Pangolin_LIBRARIES}
# ${PROJECT_SOURCE_DIR}/Thirdparty/DBoW2/lib/libDBoW2.so
# ${PROJECT_SOURCE_DIR}/Thirdparty/g2o/lib/libg2o.so
# -lboost_serialization
# -lcrypto
# )
#
