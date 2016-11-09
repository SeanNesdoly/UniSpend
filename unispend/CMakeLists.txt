cmake_minimum_required(VERSION 3.5)
project(unispend)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES UniSpend.cpp)
add_executable(unispend.wt ${SOURCE_FILES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package( Wt REQUIRED )
include_directories( ${Wt_INCLUDE_DIR} )
target_link_libraries( unispend.wt
    ${Wt_DEBUG_LIBRARY}        # or {Wt_LIBRARY}
    ${Wt_HTTP_DEBUG_LIBRARY}   # or {Wt_HTTP_LIBRARY}
)