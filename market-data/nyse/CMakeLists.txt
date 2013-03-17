cmake_minimum_required( VERSION 2.8.3 )

set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake-modules )

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

set( src_list
    src/nyse_unpack.c
)

set( lib_name nyse )

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

configure_file( ${CMAKE_CURRENT_LIST_DIR}/NyseConfig.cmake.in
    "${CMAKE_CURRENT_LIST_DIR}/NyseConfig.cmake" @ONLY
)
