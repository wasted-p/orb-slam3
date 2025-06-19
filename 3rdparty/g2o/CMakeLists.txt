cmake_minimum_required(VERSION 3.8)
project(g2o)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to Release build
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "g2o build type: ${CMAKE_BUILD_TYPE}")

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# Optimization flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -march=native")

# OpenMP support (optional)
find_package(OpenMP)
option(G2O_USE_OPENMP "Use OpenMP (optional)" OFF)
if(OpenMP_FOUND AND G2O_USE_OPENMP)
  message(STATUS "Enabling OpenMP")
  add_definitions(-DEIGEN_DONT_PARALLELIZE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Dependencies
find_package(Eigen3 REQUIRED)


# Source files
file(GLOB_RECURSE G2O_SOURCES CONFIGURE_DEPENDS
  ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# Header files (from include/g2o/)
file(GLOB_RECURSE G2O_HEADERS CONFIGURE_DEPENDS
  ${PROJECT_SOURCE_DIR}/include/g2o/*.hpp
)

# Library target
add_library(g2o STATIC ${G2O_SOURCES} ${G2O_HEADERS})

target_include_directories(g2o PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  ${EIGEN3_INCLUDE_DIR}
)
target_link_libraries(g2o PUBLIC Eigen3::Eigen)
