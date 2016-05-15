//
// Created by Ivan Kishchenko on 14.05.16.
//

#ifndef SOASERVICE_HTTPSERVER_H
#define SOASERVICE_HTTPSERVER_H


#include <cstdint>
#include <string>
#include <boost/asio.hpp>
#include "transport/Manager.h"
#include "transport/Router.h"

class TCPServer {
public:
    TCPServer(std::string address, int16_t port, Router<IHTTPHandler> &router);

    void Run();

private:
    int doAccept();

private:

    boost::asio::io_service m_service;
    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::ip::tcp::socket m_socket;

    Manager m_manager;
    Router<IHTTPHandler> &m_router;
};

#endif //SOASERVICE_HTTPSERVER_H
