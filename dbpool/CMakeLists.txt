CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project (dbpool)

SET ( dbpool_src
    dbpool.cpp
)

SET ( dbpool_hfile
    dbpool.h
)

ADD_LIBRARY (dbpool SHARED ${dbpool_src} ${dbpool_hfile})
