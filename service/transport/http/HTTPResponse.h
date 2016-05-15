//
// Created by Ivan Kishchenko on 14.05.16.
//

#ifndef SOASERVICE_HTTPRESPONSE_H
#define SOASERVICE_HTTPRESPONSE_H

#include <boost/asio/buffer.hpp>
#import "HTTPObjects.h"

class HTTPResponse {
public:
    std::vector<boost::asio::const_buffer> ToBuffer();
    HTTPHeader& Header() {
        return m_header;
    }
    HTTPBody& Body() {
        return m_body;
    }
    void Write(const uint8_t* ptr, const size_t size);
    void Write(const std::string& data);
    void SetBody(const std::string& body, const std::string& ct);

private:
    HTTPHeader m_header;
    HTTPBody m_body;
};


#endif //SOASERVICE_HTTPRESPONSE_H
