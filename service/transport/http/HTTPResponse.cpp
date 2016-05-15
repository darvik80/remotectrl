//
// Created by Ivan Kishchenko on 14.05.16.
//

#include <iostream>
#include <boost/lexical_cast.hpp>
#include "HTTPResponse.h"
#include "HTTPHeaders.h"

std::vector<boost::asio::const_buffer> HTTPResponse::ToBuffer() {
    std::vector<boost::asio::const_buffer> buffers;
    std::string header = "HTTP/1.0 200 OK\r\n";
    for (auto field  : m_header) {
        header.append(field.first + ": " + field.second + "\r\n");
    }
    header.append("\r\n");
    buffers.push_back(boost::asio::buffer(header));
    buffers.push_back(boost::asio::buffer(m_body));

    return buffers;
}

void HTTPResponse::Write(const uint8_t *ptr, const size_t size) {
    size_t pos = m_body.size();
    m_body.resize(pos + size);
    memcpy(m_body.data() + size, ptr, size);
}

void HTTPResponse::Write(const std::string &data) {
    size_t pos = m_body.size();
    m_body.resize(pos + data.size());
    memcpy(m_body.data() + pos, data.data(), data.size());
}

void HTTPResponse::SetBody(const std::string &body, const std::string &ct) {
    m_header.Set(HTTPContentType, ct);

    m_body.resize(body.length());
    memcpy(m_body.data(), body.data(), body.length());
}
