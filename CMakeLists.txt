cmake_minimum_required (VERSION 2.6)
project (sysstatd)

find_package (Boost REQUIRED COMPONENTS
	thread
	system)

add_subdirectory (deps)
include_directories (
	${CMAKE_CURRENT_SOURCE_DIR}/include/
	${Boost_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}/deps/asio_http/include/
	${CMAKE_CURRENT_SOURCE_DIR}/deps/jsoncpp/include/)

add_executable (sysstatd
	src/main.cpp
	src/request_handler.cpp)
target_link_libraries (sysstatd
	asio_http
	jsoncpp_lib
	${Boost_LIBRARIES})

