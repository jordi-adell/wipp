cmake_minimum_required(VERSION 2.8.3)
project(wipp)

set(PROJECT_VERSION_MAJOR 2)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# add C++11 -O3 and -sse here
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O3 -msse4")

find_package(IPP)
find_package(FFTW)

if(IPP_FOUND)
    message(STATUS "IPP found")
    add_definitions(-DIPP_FOUND)
endif(IPP_FOUND)

if(FFTW_FOUND)
    message(STATUS "FFTW found")
    add_definitions(-DFFTW_FOUND)
endif(FFTW_FOUND)

if (NOT IPP_FOUND AND NOT FFTW_FOUND)
    message(ERROR "Either IPP or FFTW must be available")
endif()

include_directories(
  include
  ${IPP_INCLUDE_DIRS}
  ${FFTW_INCLUDE_DIRS}
)

## Declare a cpp library
add_library(wipp
  src/${PROJECT_NAME}/wipputils.cpp
  src/${PROJECT_NAME}/wippfilter.cpp
  src/${PROJECT_NAME}/wippfft.cpp
  src/${PROJECT_NAME}/wippexception.cpp
  src/${PROJECT_NAME}/wippsignal.cpp
  src/${PROJECT_NAME}/wippstats.cpp
  src/${PROJECT_NAME}/wippdefs.cpp
)

## Specify libraries to link a library or executable target against
target_link_libraries(wipp
  ${IPP_LIBRARIES}
  ${FFTW_LIBRARIES}
)

#############
## Install ##
#############

set(LIB_DESTINATION "lib")
set(BIN_DESTINATION "bin")
set(INCLUDE_DESTINATION "include/${PROJECT_NAME}")

## Mark executables and/or libraries for installation
install(TARGETS wipp
  ARCHIVE DESTINATION ${LIB_DESTINATION}
  LIBRARY DESTINATION ${LIB_DESTINATION}
  RUNTIME DESTINATION ${BIN_DESTINATION}
)

## Mark cpp header files for installation
install(FILES
  include/${PROJECT_NAME}/wipp.h
  include/${PROJECT_NAME}/wippdefs.h
  include/${PROJECT_NAME}/wippfft.h
  include/${PROJECT_NAME}/wippfilter.h
  include/${PROJECT_NAME}/wippexception.h
  include/${PROJECT_NAME}/wipputils.h
  include/${PROJECT_NAME}/wippsignal.h
  include/${PROJECT_NAME}/wippstats.h
  DESTINATION ${INCLUDE_DESTINATION}
)

#############
## Testing ##
#############

if (test)
    enable_testing()

    find_package(GTest REQUIRED COMPONENTS system)
    find_package(Threads REQUIRED COMPONENTS system)

    add_executable(${PROJECT_NAME}-test test/test_wipp.cpp)
    target_link_libraries(${PROJECT_NAME}-test wipp)
    target_link_libraries(${PROJECT_NAME}-test ${GTEST_BOTH_LIBRARIES})
    target_link_libraries(${PROJECT_NAME}-test ${CMAKE_THREAD_LIBS_INIT})

    add_test(NAME ${PROJECT_NAME}-test COMMAND ${PROJECT_NAME}-test)
endif()


