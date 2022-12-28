# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.11)

project ("c")

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Please dertermine CMAKE_TOOLCHAIN_FILE variable "
                        "either in cmake commandline or environment variable "
                        "it's value should be the path to vcpkg cmake file")    
endif()

if(NOT EXISTS ${CMAKE_TOOLCHAIN_FILE})
    message(FATAL_ERROR "Please provide valid CMAKE_TOOLCHAIN_FILE")    
endif()


if (CMAKE_HOST_WIN32)
    # /MTX is for static liking crt libraries
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

    # this is for enabling debugging
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
endif()


include_directories("includes")

# Include sub-projects.
add_subdirectory ("src")

