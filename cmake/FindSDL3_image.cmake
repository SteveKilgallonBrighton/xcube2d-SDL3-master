# Locate SDL_image library (SDL3_image)
#
# This module defines:
#
# ::
#
#   SDL3_IMAGE_LIBRARIES, the name of the library to link against
#   SDL3_IMAGE_INCLUDE_DIRS, where to find the headers
#   SDL3_IMAGE_FOUND, if false, do not try to link against
#   SDL3_IMAGE_VERSION_STRING - human-readable string containing the version of SDL_image
#
#
#
# For backward compatibility the following variables are also set:
#
# ::
#
#   SDLIMAGE_LIBRARY (same value as SDL3_IMAGE_LIBRARIES)
#   SDLIMAGE_INCLUDE_DIR (same value as SDL3_IMAGE_INCLUDE_DIRS)
#   SDLIMAGE_FOUND (same value as SDL3_IMAGE_FOUND)
#
#
#
# $SDLDIR is an environment variable that would correspond to the
# ./configure --prefix=$SDLDIR used in building SDL.
#
# NOTE: SDL3_image ships its own CMake config-mode package
# (SDL3_image-config.cmake / SDL3_imageConfig.cmake depending on build) as
# part of its install tree. Prefer, when available:
#     find_package(SDL3_image REQUIRED CONFIG)
#     target_link_libraries(your_target PRIVATE SDL3_image::SDL3_image)
# over this legacy Find-module.
#
# Created by Eric Wing.  This was influenced by the FindSDL.cmake
# module, but with modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).

#=============================================================================
# Copyright 2005-2009 Kitware, Inc.
# Copyright 2012 Benjamin Eikel
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

find_path(SDL3_IMAGE_INCLUDE_DIR SDL_image.h
        HINTS
        ENV SDL3IMAGEDIR
        ENV SDL3DIR
        PATH_SUFFIXES SDL3
        # path suffixes to search inside ENV{SDLDIR}
        include/SDL3 include
        PATHS ${SDL3_IMAGE_PATH}
        )

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(VC_LIB_PATH_SUFFIX lib/x64)
else()
    set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

find_library(SDL3_IMAGE_LIBRARY
        NAMES SDL3_image
        HINTS
        ENV SDL3IMAGEDIR
        ENV SDL3DIR
        PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
        PATHS ${SDL3_IMAGE_PATH}
        )

if(SDL3_IMAGE_INCLUDE_DIR AND EXISTS "${SDL3_IMAGE_INCLUDE_DIR}/SDL_image.h")
    file(STRINGS "${SDL3_IMAGE_INCLUDE_DIR}/SDL_image.h" SDL3_IMAGE_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_IMAGE_MAJOR_VERSION[ \t]+[0-9]+$")
    file(STRINGS "${SDL3_IMAGE_INCLUDE_DIR}/SDL_image.h" SDL3_IMAGE_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_IMAGE_MINOR_VERSION[ \t]+[0-9]+$")
    file(STRINGS "${SDL3_IMAGE_INCLUDE_DIR}/SDL_image.h" SDL3_IMAGE_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_IMAGE_MICRO_VERSION[ \t]+[0-9]+$")
    string(REGEX REPLACE "^#define[ \t]+SDL_IMAGE_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL3_IMAGE_VERSION_MAJOR "${SDL3_IMAGE_VERSION_MAJOR_LINE}")
    string(REGEX REPLACE "^#define[ \t]+SDL_IMAGE_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL3_IMAGE_VERSION_MINOR "${SDL3_IMAGE_VERSION_MINOR_LINE}")
    string(REGEX REPLACE "^#define[ \t]+SDL_IMAGE_MICRO_VERSION[ \t]+([0-9]+)$" "\\1" SDL3_IMAGE_VERSION_PATCH "${SDL3_IMAGE_VERSION_PATCH_LINE}")
    set(SDL3_IMAGE_VERSION_STRING ${SDL3_IMAGE_VERSION_MAJOR}.${SDL3_IMAGE_VERSION_MINOR}.${SDL3_IMAGE_VERSION_PATCH})
    unset(SDL3_IMAGE_VERSION_MAJOR_LINE)
    unset(SDL3_IMAGE_VERSION_MINOR_LINE)
    unset(SDL3_IMAGE_VERSION_PATCH_LINE)
    unset(SDL3_IMAGE_VERSION_MAJOR)
    unset(SDL3_IMAGE_VERSION_MINOR)
    unset(SDL3_IMAGE_VERSION_PATCH)
endif()

set(SDL3_IMAGE_LIBRARIES ${SDL3_IMAGE_LIBRARY})
set(SDL3_IMAGE_INCLUDE_DIRS ${SDL3_IMAGE_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL3_image
        REQUIRED_VARS SDL3_IMAGE_LIBRARIES SDL3_IMAGE_INCLUDE_DIRS
        VERSION_VAR SDL3_IMAGE_VERSION_STRING)

# for backward compatibility
set(SDLIMAGE_LIBRARY ${SDL3_IMAGE_LIBRARIES})
set(SDLIMAGE_INCLUDE_DIR ${SDL3_IMAGE_INCLUDE_DIRS})
set(SDLIMAGE_FOUND ${SDL3_IMAGE_FOUND})

mark_as_advanced(SDL3_IMAGE_LIBRARY SDL3_IMAGE_INCLUDE_DIR)
