cmake_minimum_required(VERSION 2.8)
project (dbpool)
cmake_policy(SET CMP0015 OLD)

# flags
set(CMAKE_CXX_COMPILER  "g++")
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 ")

# pre define
#ADD_DEFINITIONS(
    #-D_FILE_OFFSET_BITS=64
    #-DAC_HAS_INFO
    #-DAC_HAS_WARNING
    #-DAC_HAS_ERROR
    #-DAC_HAS_CRITICAL
    #-DTIXML_USE_STL
    #-Wno-literal-suffix
    #-Wno-unused-variable
    #-Wno-unused-function
    #-Wno-sign-compare
    #-Wno-deprecated
    #-Wno-unused-parameter
    #-DAC_HAS_DEBUG
    #-DLINUX_DAEMON
    #-std=c++11
    #-DUSE_CACHE
    #-DENCRYPT
    #    )

# third party
set (MYSQL_INCLUDE_DIR /usr/include/mysql)
set (MYSQL_LIB /usr/lib64/mysql)

# lib & include
LINK_DIRECTORIES(./ ${MYSQL_LIB})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR} ${MYSQL_INCLUDE_DIR})

# src file
set (dbpool_SRC
    dbpool.cpp
)

# output path
set (LIBRARY_OUTPUT_PATH ./build)

add_library (dbpool SHARED ${dbpool_SRC})
#SET(EXECUTABLE_OUTPUT_PATH  ./)
#ADD_XXXX必须在TARGET_LINK_LIBRARIES前面，否则会报错
