cmake_minimum_required(VERSION 3.5)
project(unispend)


SET(GCC_COVERAGE_LINK_FLAGS    "-Wall -I/usr/include -L/usr/lib -L/usr/include -lmysqlcppconn -lmysqlcppconn-static")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES UniSpend.cpp US_Login.cpp US_Login.h US_Workspace.cpp US_Workspace.h)
add_executable(unispend.wt ${SOURCE_FILES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )


find_package( Wt REQUIRED )
include_directories( ${Wt_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/resources)
include_directories(/usr/include/cppconn)
include_directories(/usr/lib)
target_link_libraries( unispend.wt
    ${Wt_DEBUG_LIBRARY}        # or {Wt_LIBRARY}
    ${Wt_HTTP_DEBUG_LIBRARY}   # or {Wt_HTTP_LIBRARY} 
    mysqlcppconn
)

