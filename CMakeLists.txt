cmake_minimum_required(VERSION 3.5.2)
project(wipp VERSION 2.2.0)

###########################
## Configure compilation ##
###########################

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
    add_definitions("-DWIPP_DEBUG")
    message(STATUS "DEBUG mode")
else(DEBUG)
  set(OPT_FLAGS, "-O3 -msse4")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPT_FLAGS}")
  message(STATUS "optimisation flags: ${OPT_FLAGS}")
endif(DEBUG)

#############################################
## Find modules and configure dependencies ##
#############################################

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(IPP)
find_package(FFTW)
find_package(Boost REQUIRED COMPONENTS system filesystem)

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
  ${Boost_INCLUDE_DIRS}
  )

###################################
## Declare and configure targets ##
###################################

add_library(wipp SHARED
  src/${PROJECT_NAME}/wipputils.cpp
  src/${PROJECT_NAME}/wippfilter.cpp
  src/${PROJECT_NAME}/wippfft.cpp
  src/${PROJECT_NAME}/wippexception.cpp
  src/${PROJECT_NAME}/wippsignal.cpp
  src/${PROJECT_NAME}/wippstats.cpp
  src/${PROJECT_NAME}/wippdefs.cpp
  src/${PROJECT_NAME}/wipplogger.cpp
  )

set_target_properties(wipp
PROPERTIES
VERSION ${PROJECT_VERSION}
SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_link_libraries(wipp
  ${IPP_LIBRARIES}
  ${FFTW_LIBRARIES}
  ${Boost_LIBRARIES}
)

#############
## Install ##
#############

set(LIB_DESTINATION "lib")
set(BIN_DESTINATION "bin")
set(INCLUDE_DESTINATION "include/${PROJECT_NAME}")

## Mark executables and/or libraries for installation
install(TARGETS wipp
  COMPONENT bin
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
  COMPONENT dev
)

########################
## Package generation ##
########################

SET(CPACK_GENERATOR "DEB")

SET(CPACK_PACKAGE_NAME "lib${PROJECT_NAME}")
SET(CPACK_PACKAGE_CONTACT "Jordi Adell <adellj@gmail.com>") #required
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
SET(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
SET(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Library for mathematical calculation signal processing-oriented.")

SET(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
SET(CPACK_RESOURCE_FILE_README ${CMAKE_SOURCE_DIR}/README.md)
SET(CPACK_RESOURCE_FILE_WELCOME ${CMAKE_SOURCE_DIR}/README.md)
SET(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/README.md)

SET(CPACK_STRIP_FILES TRUE)

if (${CMAKE_SIZEOF_VOID_P} EQUAL "8")
  SET(CPACK_SYSTEM_NAME "amd64")
else()
  SET(CPACK_SYSTEM_NAME "i386")
endif()

SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS 1)
SET(CPACK_DEB_COMPONENT_INSTALL 1)

SET(CPACK_DEBIAN_DEV_PACKAGE_DEPENDS "${CPACK_PACKAGE_NAME} (=${CPACK_PACKAGE_VERSION})")
SET(CPACK_DEBIAN_DEV_PACKAGE_NAME "lib${PROJECT_NAME}-dev")
SET(CPACK_DEBIAN_BIN_PACKAGE_NAME "lib${PROJECT_NAME}")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/shlibs "lib${PROJECT_NAME} ${CPACK_PACKAGE_VERSION_MAJOR} lib${PROJECT_NAME} (>= ${CPACK_PACKAGE_VERSION})")
SET(CPACK_DEBIAN_BIN_PACKAGE_CONTROL_EXTRA ${CMAKE_CURRENT_BINARY_DIR}/shlibs)

INCLUDE(CPack)

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

    add_custom_target(tests DEPENDS ${PROJECT_NAME}-test)

    add_test(NAME ${PROJECT_NAME}-test COMMAND ${PROJECT_NAME}-test)

endif()


