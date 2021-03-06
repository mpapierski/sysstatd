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
	${CMAKE_CURRENT_SOURCE_DIR}/deps/jsoncpp/include/
	${CMAKE_CURRENT_SOURCE_DIR}/deps/sigar/include/)

set (SOURCES
	src/main.cpp
	src/request_handler.cpp
	src/sigar_service.cpp)

set (HEADERS
	include/sysstatd/request_handler.hpp
	include/sysstatd/sigar_service.hpp)

add_executable (sysstatd
	${SOURCES}
	${HEADERS})
target_link_libraries (sysstatd
	asio_http
	jsoncpp_lib
	sigar
	${Boost_LIBRARIES})
install (TARGETS sysstatd
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
