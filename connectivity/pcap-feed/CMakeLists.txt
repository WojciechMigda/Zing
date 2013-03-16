cmake_minimum_required( VERSION 2.8.3 )

set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake-modules )

################################################################################

set(CXXTEST_USE_PYTHON TRUE)
find_package( CxxTest )

if( CXXTEST_FOUND )
    message( STATUS "CxxTest FOUND" )
endif( CXXTEST_FOUND )

################################################################################

find_package( PCAP )

if( H_PCAP_OPEN )
    add_definitions( -DH_PCAP_OPEN )
endif( H_PCAP_OPEN )
if( H_PCAP_OPEN_OFFLINE )
    add_definitions( -DH_PCAP_OPEN_OFFLINE )
endif( H_PCAP_OPEN_OFFLINE )
if( H_PCAP_FOPEN_OFFLINE )
    add_definitions( -DH_PCAP_FOPEN_OFFLINE )
endif( H_PCAP_FOPEN_OFFLINE )

################################################################################

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/api
    ${PCAP_INCLUDE_DIRS}
)

################################################################################

#include( CheckIncludeFiles )

#check_include_files( net/ethernet.h HAS_NET_ETHERNET_H )

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
