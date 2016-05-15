//
// Created by Ivan Kishchenko on 14.05.16.
//

#include "TCPServer.h"
#include "transport/http/HTTPTransport.h"
#include <boost/lexical_cast.hpp>

using namespace boost;

int TCPServer::doAccept() {
    m_acceptor.async_accept(
            m_socket,
            [this](boost::system::error_code ec) {
                // Check whether the server was stopped by a signal before this
                // completion handler had a chance to run.
                if (!m_acceptor.is_open()) {
                    return;
                }

                if (!ec) {
                    TransportPtr transport(new HTTPTransport(std::move(m_socket), m_manager, m_router));
                    m_manager.Register(transport);
                }

                doAccept();
            }
    );

    return 0;
}

TCPServer::TCPServer(std::string address, int16_t port, Router<IHTTPHandler> &router)
        : m_service(), m_acceptor(m_service), m_socket(m_service), m_router(router) {
    asio::ip::tcp::resolver resolver(m_service);
    asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, lexical_cast<std::string>(port)});
    m_acceptor.open(endpoint.protocol());
    m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    m_acceptor.bind(endpoint);
    m_acceptor.listen();

    doAccept();
}

void TCPServer::Run() {

    m_service.run();
}

