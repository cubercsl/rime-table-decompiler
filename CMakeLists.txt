cmake_minimum_required(VERSION 3.13)
project(rime_table_bin_decompiler)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_STATIC "Build with dependencies as static libraries" OFF)
option(BOOST_USE_CXX11 "Boost has been built with C++11 support" OFF)
option(BOOST_USE_SIGNALS2 "Boost use signals2 instead of signals" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

set(Boost_USE_STATIC_LIBS ${BUILD_STATIC})
set(Marisa_STATIC ${BUILD_STATIC})

if(NOT BOOST_USE_CXX11)
  add_definitions("-DBOOST_NO_CXX11_SCOPED_ENUMS")
endif()

set(BOOST_COMPONENTS system filesystem)
if(BOOST_USE_SIGNALS2)
  set(RIME_BOOST_SIGNALS2 1)
else()
  set(BOOST_COMPONENTS ${BOOST_COMPONENTS} signals)
endif()

find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif()

find_package(Marisa REQUIRED)
if(Marisa_FOUND)
  include_directories(${Marisa_INCLUDE_PATH})
endif()

configure_file(
  "${PROJECT_SOURCE_DIR}/src/rime/build_config.h.in"
  "${PROJECT_BINARY_DIR}/src/rime/build_config.h")

include_directories(${PROJECT_BINARY_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)
  
add_subdirectory(src)
