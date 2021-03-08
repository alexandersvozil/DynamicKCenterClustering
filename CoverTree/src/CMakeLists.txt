cmake_minimum_required(VERSION 3.5)
project(CoverTree VERSION 1.0)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set(EIGEN_DIR "${PROJECT_SOURCE_DIR}/lib/eigen")
#include_directories(${EIGEN_DIR})

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

#IF (NOT EIGEN3_INCLUDE_DIR)
#	MESSAGE( FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the
#	include directory of your Eigen3 installation.")
#ENDIF()
#find_package(Eigen3 3.3 REQUIRED)
#INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

##set(CMAKE_CXX_FLAGS "-O3" "-ffast-math" "-march=native" "-funroll-loops" "-Wall" "-Wextra"	"-Wconversion" "-pedantic-errors" "-DNDEBUG")
#set(CMAKE_CXX_FLAGS "-O3 -ffast-math -march=native -funroll-loops -Wall -Wextra -Wconversion -pedantic-errors")
#set(CMAKE_CXX_FLAGS "-ggdb3 -O2 -ffast-math -march=native -funroll-loops -Wall -Wextra -Wconversion -pedantic-errors")
set(CMAKE_CXX_FLAGS "-O2 -ffast-math -march=native -funroll-loops -Wall -Wextra -Wconversion -pedantic-errors -DNDEBUG")
#set(CMAKE_CXX_FLAGS "-pg -O2 -ffast-math -march=native -funroll-loops -Wall -Wextra -Wconversion -pedantic-errors -DNDEBUG")

FIND_PACKAGE(OpenMP)
  IF(OPENMP_FOUND)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
  ENDIF()
configure_file(covertree_config.h.in covertree_config.h)

#add_subdirectory(${PROJECT_SOURCE_DIR}/lib/eigen)
#add_executable(CoverTree /src/cover_tree/driver_main.cpp)


enable_testing()
add_executable(test_cover test_tree.cpp algorithm.cpp cover_tree_node.cpp cover_tree.cpp)
add_executable(kcenter driver_main.cpp algorithm.cpp cover_tree.cpp cover_tree_node.cpp cover_tree.cpp)


add_test(test_cover test_cover)
target_link_libraries(test_cover PUBLIC Eigen3::Eigen)
target_link_libraries(kcenter PUBLIC Eigen3::Eigen)
target_include_directories(test_cover PUBLIC "${PROJECT_BINARY_DIR}")


