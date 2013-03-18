cmake_minimum_required( VERSION 2.8.3 )

################################################################################

set( PcapFeeder_DIR ${CMAKE_CURRENT_LIST_DIR}/connectivity/pcap-feed )
find_package( PcapFeeder )

set( InetProto_DIR ${CMAKE_CURRENT_LIST_DIR}/connectivity/inet-proto )
find_package( InetProto )

set( Xdp_DIR ${CMAKE_CURRENT_LIST_DIR}/market-data/xdp )
find_package( Xdp )

include_directories(
    ${PCAP_FEEDER_INCLUDE_DIRS}
    ${INET_PROTO_INCLUDE_DIRS}
    ${XDP_INCLUDE_DIRS}
)

add_executable( main
    ${CMAKE_CURRENT_LIST_DIR}/src/main.c
)

target_link_libraries( main
    ${INET_PROTO_LIBRARIES}
    ${PCAP_FEEDER_LIBRARIES}
    ${XDP_LIBRARIES}
)

set_target_properties( main PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib
)
