cmake_minimum_required(VERSION 3.5)
project(remotectrl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        utils/http_parser.c
        utils/http_parser.h
        service/TCPServer.cpp
        service/TCPServer.h
        service/transport/Interface.h
        service/transport/Manager.cpp
        service/transport/Manager.h
        service/transport/Router.h
        service/transport/http/HTTPTransport.cpp
        service/transport/http/HTTPTransport.h
        service/transport/http/HTTPRequest.cpp
        service/transport/http/HTTPRequest.h
        service/transport/http/HTTPResponse.cpp
        service/transport/http/HTTPResponse.h
        service/transport/http/HTTPObjects.h
        handler/Handler.h
        handler/PingHandler.cpp
        handler/PingHandler.h
        handler/jsonrpc2/JsonRpc2Handler.cpp
        handler/jsonrpc2/JsonRpc2Handler.h
        handler/jsonrpc2/JsonRpc2RequestAbstract.cpp
        handler/jsonrpc2/JsonRpc2RequestAbstract.h
        handler/jsonrpc2/JsonRpc2ResponseAbstract.cpp
        handler/jsonrpc2/JsonRpc2ResponseAbstract.h
        service/transport/http/HTTPHeaders.h)

FIND_PACKAGE(Boost COMPONENTS system REQUIRED)

if (Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif ()

add_executable(remotectrl ${SOURCE_FILES})

if (Boost_FOUND)
    target_link_libraries(remotectrl ${Boost_LIBRARIES})
endif ()