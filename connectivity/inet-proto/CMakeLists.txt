cmake_minimum_required( VERSION 2.8.3 )

################################################################################

find_package( CxxTest )

if( CXXTEST_FOUND )
  message( STATUS "CxxTest FOUND" )
endif( CXXTEST_FOUND )

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
set( CONF_LIBRARIES
    ${CONF_LIBRARIES}
)

configure_file( ${CMAKE_CURRENT_LIST_DIR}/InetProtoConfig.cmake.in
    "${CMAKE_CURRENT_LIST_DIR}/InetProtoConfig.cmake" @ONLY
)
