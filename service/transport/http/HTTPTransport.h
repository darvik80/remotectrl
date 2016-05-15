//
// Created by Ivan Kishchenko on 14.05.16.
//

#ifndef SOASERVICE_HTTPTRANSPORT_H
#define SOASERVICE_HTTPTRANSPORT_H


#include <boost/asio.hpp>
#include "../Manager.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "../Router.h"

class HTTPTransport
        : public ITransport
        , public std::enable_shared_from_this<HTTPTransport>
{
public:
    HTTPTransport(boost::asio::ip::tcp::socket socket, Manager &manager, Router<IHTTPHandler>& router);
    virtual void Start();

    virtual void OnRecv(const uint8_t* ptr, std::size_t size);

    virtual void Stop();
private:
    void doRead();
    void doSend();
private:
    /// Buffer for incoming data.
    HTTPRequest m_request;
    HTTPResponse m_response;

    std::array<uint8_t, 8192> m_buffer;

    boost::asio::ip::tcp::socket m_socket;
    Manager& m_manager;
    Router<IHTTPHandler>& m_router;
};


#endif //SOASERVICE_HTTPTRANSPORT_H
