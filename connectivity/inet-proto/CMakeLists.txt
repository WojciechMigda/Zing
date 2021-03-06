################################################################################
## Copyright (c) 2013, Wojciech Migda
## All Rights Reserved.
## Distributed under the terms of the GNU LGPL v3
################################################################################
##
## Filename: CMakeLists.txt
##
## Description:
##      Main CMakeLists.txt file.
##      To build:
##      1. cd .build
##      2. cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=DEBUG ..
##         or e.g.
##         cmake -DCMAKE_BUILD_TYPE=RELEASE ..
##      3. make
##
## Authors:
##          Wojciech Migda (wm)
##
################################################################################
## History:
## --------
## Date         Who  Ticket     Description
## ----------   ---  ---------  ------------------------------------------------
## 16-03-2013   wm              Initial version
##
################################################################################

cmake_minimum_required( VERSION 2.8.3 )

################################################################################

set( CXXTEST_USE_PYTHON YES CACHE INTERNAL "" )
find_program(CXXTEST_PYTHON_TESTGEN_EXECUTABLE cxxtestgen
    PATHS ${CXXTEST_INCLUDE_DIR}
)
find_package( CxxTest )

set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake-modules )

################################################################################

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/api
)

################################################################################

include( CheckIncludeFiles )

check_include_files( net/ethernet.h HAS_NET_ETHERNET_H )

if( HAS_NET_ETHERNET_H )
    add_definitions( -DHAS_NET_ETHERNET_H )
endif( HAS_NET_ETHERNET_H )

################################################################################

set( src_list
    src/eth_unpack.c
    src/ip_unpack.c
    src/udp_unpack.c
)

set( lib_name inet_proto )

################################################################################

add_library( ${lib_name} ${src_list} )
set_target_properties( ${lib_name} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib
)

################################################################################

set( CONF_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( CONF_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/api )
get_target_property( CONF_LIBRARIES ${lib_name} LOCATION )

configure_file( ${CMAKE_CURRENT_LIST_DIR}/InetProtoConfig.cmake.in
    "${CMAKE_CURRENT_LIST_DIR}/InetProtoConfig.cmake" @ONLY
)

################################################################################

if( CXXTEST_FOUND )
    include_directories( ${CXXTEST_INCLUDE_DIR} )
    enable_testing()

    find_package( GMock )
    find_package( GTest )

    function( my_test_add name test_src_dir )
        cxxtest_add_test( ${name} ${name}.cpp ${test_src_dir}/${name}.hpp )
        target_link_libraries( ${name}
            ${lib_name}
            ${GMOCK_BOTH_LIBRARIES}
            ${GTEST_BOTH_LIBRARIES}
            pthread
        )
    endfunction( my_test_add )

    my_test_add( test_inet_proto_unpack ${CMAKE_CURRENT_LIST_DIR}/tests )

endif( CXXTEST_FOUND )
