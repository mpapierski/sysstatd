add_subdirectory (asio_http)

set (JSONCPP_WITH_TESTS OFF CACHE BOOL "" FORCE)
set (JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "" FORCE)
set (JSONCPP_WITH_WARNING_AS_ERROR OFF CACHE BOOL "" FORCE)
set (JSONCPP_WITH_PKGCONFIG_SUPPORT OFF CACHE BOOL "" FORCE)

# Fix broken jsoncpp. Without these lines all bin/lib files
# are stored inside deps/jsoncpp/bin/ which is bad.
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ""
    CACHE PATH "Single directory for all static libraries.")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ""
    CACHE PATH "Single directory for all dynamic libraries on Unix.")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ""
    CACHE PATH "Single directory for all executable and dynamic libraries on Windows.")
mark_as_advanced (CMAKE_RUNTIME_OUTPUT_DIRECTORY
	CMAKE_LIBRARY_OUTPUT_DIRECTORY
	CMAKE_ARCHIVE_OUTPUT_DIRECTORY)

add_subdirectory (jsoncpp)
add_subdirectory (sigar)
