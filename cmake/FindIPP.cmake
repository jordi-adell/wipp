# - Find Intel IPP
# Find the IPP libraries
# Options:
#
#   IPP_STATIC: true if using static linking
#   IPP_MULTI_THREADED: true if using multi-threaded static linking
#
# This module defines the following variables:
#
#   IPP_FOUND       : True if IPP_INCLUDE_DIR are found
#   IPP_INCLUDE_DIR : where to find ipp.h, etc.
#   IPP_INCLUDE_DIRS: set when IPP_INCLUDE_DIR found
#   IPP_LIBRARIES   : the library to link against.

include(FindPackageHandleStandardArgs)


# Test 32/64 bits
if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    message(STATUS "Target is 64 bits")
    set(IPP_LIBRARY_DIR intel64)
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    message(STATUS "Target is 32 bits")
    set(IPP_LIBRARY_DIR ia32)
endif("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")

set(IPP_ROOT /opt/intel/ipp CACHE PATH "Folder contains IPP")

# Find header file dir
find_path(IPP_INCLUDE_DIR ipp.h
    PATHS ${IPP_ROOT}/include)

# Find libraries

# Handle suffix
set(_IPP_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})

#if(WIN32)
#    set(CMAKE_FIND_LIBRARY_SUFFIXES .lib)
#else()
#    if(IPP_STATIC)
#        set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
#    else()
#        set(CMAKE_FIND_LIBRARY_SUFFIXES .so)
#    endif()
#endif()

if(IPP_STATIC)
#    if(IPP_MULTI_THREADED)
#        set(IPP_LIBNAME_SUFFIX _tl)
#    endif()
#else()
#    set(IPP_LIBNAME_SUFFIX "")
endif()


message(STATUS "Found the following IPP libraries:")
macro(find_ipp_library IPP_COMPONENT)
    string(TOLOWER ${IPP_COMPONENT} IPP_COMPONENT_LOWER)
    find_library(IPP_LIB_${IPP_COMPONENT} ipp${IPP_COMPONENT_LOWER} ${IPP_ROOT}/lib/${IPP_LIBRARY_DIR})
    if (IPP_LIB_${IPP_COMPONENT})
        message(STATUS "    - ${IPP_COMPONENT}")
    endif()
endmacro()

foreach(component ${IPP_FIND_COMPONENTS})
    find_ipp_library(${component})
    list(APPEND IPP_LIBRARY ${IPP_LIB_${component}})
endforeach()


find_package_handle_standard_args(IPP DEFAULT_MSG
    IPP_INCLUDE_DIR IPP_LIBRARY)

if (IPP_FOUND)
    set(IPP_INCLUDE_DIRS ${IPP_INCLUDE_DIR})
    set(IPP_LIBRARIES ${IPP_LIBRARY})
endif()


set(CMAKE_FIND_LIBRARY_SUFFIXES ${_IPP_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES})