cmake_minimum_required (VERSION 2.6)
project (sysstatd)

find_package (Boost REQUIRED COMPONENTS
	thread
	system)

add_subdirectory (deps)
include_directories (
	${CMAKE_SOURCE_DIR}/include/
	${Boost_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/deps/asio_http/include/)

add_executable (sysstatd
	src/main.cpp
	src/request_handler.cpp)
target_link_libraries (sysstatd
	asio_http
	${Boost_LIBRARIES})

