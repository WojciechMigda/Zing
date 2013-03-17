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

set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake-modules )

################################################################################

set( CXXTEST_USE_PYTHON TRUE )
# for Ubuntu 12.04 cxxtest installation:
find_program(CXXTEST_PYTHON_TESTGEN_EXECUTABLE cxxtestgen
    PATHS ${CXXTEST_INCLUDE_DIR}
)
find_package( CxxTest )

################################################################################

find_package( PCAP )

if( H_PCAP_FOPEN_OFFLINE )
    add_definitions( -DH_PCAP_FOPEN_OFFLINE )
endif( H_PCAP_FOPEN_OFFLINE )

################################################################################

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/api
    ${PCAP_INCLUDE_DIRS}
)

################################################################################

set( src_list
    src/i_pcap_lib.c
    src/pcap_feeder.c
)

set( lib_name pcap_feeder )

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
set( CONF_LIBRARIES
    ${CONF_LIBRARIES}
    ${PCAP_LIBRARIES}
)

configure_file( ${CMAKE_CURRENT_LIST_DIR}/PcapFeederConfig.cmake.in
    "${CMAKE_CURRENT_LIST_DIR}/PcapFeederConfig.cmake" @ONLY
)

################################################################################

if( CXXTEST_FOUND )
    include_directories( ${CXXTEST_INCLUDE_DIR} )
    enable_testing()

    find_package( GMock )
    find_package( GTest )

    function( my_test_add name test_src_dir )
        cxxtest_add_test( ${name} ${name}.cpp ${test_src_dir}/${name}.h )
        target_link_libraries( ${name}
            ${CONF_LIBRARIES}
            ${GMOCK_LIBRARIES}
            ${GMOCK_MAIN_LIBRARIES}
            ${GTEST_BOTH_LIBRARIES}
            pthread
        )
    endfunction( my_test_add )

    my_test_add( test_pcap_feeder ${CMAKE_CURRENT_LIST_DIR}/tests )

endif( CXXTEST_FOUND )
