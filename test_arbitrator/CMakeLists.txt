cmake_minimum_required(VERSION 3.4.1)
project(erpc_server)

set(ERPC_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../erpc/erpc_c)

add_compile_options(-std=c++11)

#erpc module
include_directories(${ERPC_ROOT_DIR}/config)
include_directories(${ERPC_ROOT_DIR}/infra)
include_directories(${ERPC_ROOT_DIR}/port)
include_directories(${ERPC_ROOT_DIR}/setup)
include_directories(${ERPC_ROOT_DIR}/transports)

#erpc idl
include_directories(${CMAKE_CURRENT_LIST_DIR}/idl)

#erpc server
include_directories(${CMAKE_CURRENT_LIST_DIR}/server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -pthread" )


#compile
add_executable(erpc_server
	${ERPC_ROOT_DIR}/infra/erpc_arbitrated_client_manager.cpp
	${ERPC_ROOT_DIR}/infra/erpc_basic_codec.cpp
	${ERPC_ROOT_DIR}/infra/erpc_client_manager.cpp
	${ERPC_ROOT_DIR}/infra/erpc_crc16.cpp
	${ERPC_ROOT_DIR}/infra/erpc_framed_transport.cpp
	${ERPC_ROOT_DIR}/infra/erpc_message_buffer.cpp
	${ERPC_ROOT_DIR}/infra/erpc_message_loggers.cpp
	${ERPC_ROOT_DIR}/infra/erpc_server.cpp
	${ERPC_ROOT_DIR}/infra/erpc_simple_server.cpp
	${ERPC_ROOT_DIR}/infra/erpc_transport_arbitrator.cpp
	${ERPC_ROOT_DIR}/port/erpc_port_stdlib.cpp 
	${ERPC_ROOT_DIR}/port/erpc_threading_pthreads.cpp 
	${ERPC_ROOT_DIR}/setup/erpc_setup_mbf_dynamic.cpp 
	${ERPC_ROOT_DIR}/transports/erpc_inter_thread_buffer_transport.cpp 
	${ERPC_ROOT_DIR}/transports/erpc_tcp_transport.cpp
	${CMAKE_CURRENT_LIST_DIR}/idl/erpcCore1_client.cpp
	${CMAKE_CURRENT_LIST_DIR}/idl/erpcCore0_server.cpp
	${CMAKE_CURRENT_LIST_DIR}/server/test_arbitrator_server_impl.cpp
	${CMAKE_CURRENT_LIST_DIR}/server/test_arbitrator_server.cpp
	)


#compile
add_executable(erpc_client
	${ERPC_ROOT_DIR}/infra/erpc_arbitrated_client_manager.cpp
	${ERPC_ROOT_DIR}/infra/erpc_basic_codec.cpp
	${ERPC_ROOT_DIR}/infra/erpc_client_manager.cpp
	${ERPC_ROOT_DIR}/infra/erpc_crc16.cpp
	${ERPC_ROOT_DIR}/infra/erpc_framed_transport.cpp
	${ERPC_ROOT_DIR}/infra/erpc_message_buffer.cpp
	${ERPC_ROOT_DIR}/infra/erpc_message_loggers.cpp
	${ERPC_ROOT_DIR}/infra/erpc_server.cpp
	${ERPC_ROOT_DIR}/infra/erpc_simple_server.cpp
	${ERPC_ROOT_DIR}/infra/erpc_transport_arbitrator.cpp
	${ERPC_ROOT_DIR}/port/erpc_port_stdlib.cpp 
	${ERPC_ROOT_DIR}/port/erpc_threading_pthreads.cpp 
	${ERPC_ROOT_DIR}/setup/erpc_setup_mbf_dynamic.cpp 
	${ERPC_ROOT_DIR}/transports/erpc_inter_thread_buffer_transport.cpp 
	${ERPC_ROOT_DIR}/transports/erpc_tcp_transport.cpp
	${CMAKE_CURRENT_LIST_DIR}/idl/erpcCore0_client.cpp
	${CMAKE_CURRENT_LIST_DIR}/idl/erpcCore1_server.cpp
	${CMAKE_CURRENT_LIST_DIR}/client/test_arbitrator_client_impl.cpp
	${CMAKE_CURRENT_LIST_DIR}/client/test_arbitrator_client.cpp
	)














