//
// Created by Ivan Kishchenko on 14.05.16.
//

#include <iostream>
#include <boost/lexical_cast.hpp>
#include "HTTPTransport.h"
#include "HTTPHeaders.h"

using namespace boost;

HTTPTransport::HTTPTransport(asio::ip::tcp::socket socket, Manager &manager, Router<IHTTPHandler> &router)
        : m_socket(std::move(socket)), m_manager(manager), m_router(router) {

}

void HTTPTransport::Start() {
    doRead();
}

void HTTPTransport::OnRecv(const uint8_t *ptr, std::size_t size) {
    if (m_request.Parse((const char *) ptr, size)) {
        //send bad request
    } else if (m_request.IsComplete()) {
        try {
            // Handle request
            auto handler = m_router.Resolve(m_request.Url().Path);
            if (handler) {
                handler->Handle(m_request, m_response);
            }
        } catch (std::exception &ex) {
            m_response.SetBody(ex.what(), HTTPContentTypeText);
        }
        m_response.Header().Set(HTTPContentLength, boost::lexical_cast<std::string>(m_response.Body().size()));
        m_response.Header().Set(HTTPConnection, "close");

        doSend();
    }
}

void HTTPTransport::Stop() {
    m_socket.close();
}

void HTTPTransport::doRead() {
    auto self(shared_from_this());
    m_socket.async_read_some(
            asio::buffer(m_buffer),
            [this, self](system::error_code ec, std::size_t bytes_transferred) {
                if (!ec) {
                    OnRecv(&m_buffer.front(), bytes_transferred);
                } else if (ec != asio::error::operation_aborted) {
                    m_manager.Unregister(self);
                }
            }
    );
}

void HTTPTransport::doSend() {
    auto self(shared_from_this());
    asio::async_write(
            m_socket,
            m_response.ToBuffer(),
            [this, self](system::error_code ec, std::size_t) {
                if (!ec) {
                    // Initiate graceful connection closure.
                    system::error_code ignored_ec;
                    m_socket.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);
                }

                if (ec != asio::error::operation_aborted) {
                    m_manager.Unregister(self);
                }
            }
    );
}