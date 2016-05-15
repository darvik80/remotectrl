//
// Created by Ivan Kishchenko on 14.05.16.
//

#ifndef SOASERVICE_HTTPREQUEST_H
#define SOASERVICE_HTTPREQUEST_H

#include "HTTPRequest.h"
#include "../../../utils/http_parser.h"
#include "HTTPObjects.h"

class HTTPRequest {
public:
    HTTPRequest();
    int Parse(const char* ptr, std::size_t size);
    bool IsComplete();

    HTTPUrl& Url() {
        return m_url;
    }
    HTTPHeader& Header() {
        return m_header;
    }
    HTTPBody& Body() {
        return m_body;
    }
private:
    static int onMessageBegin (http_parser* parser);
    static int onURL (http_parser* parser, const char *at, size_t length);
    static int onStatus (http_parser* parser, const char *at, size_t length);
    static int onHeaderField (http_parser* parser, const char *at, size_t length);
    static int onHeaderValue (http_parser* parser, const char *at, size_t length);
    static int onHeaderComplete (http_parser* parser);
    static int onBody (http_parser* parser, const char *at, size_t length);
    static int onMessageComplete (http_parser* parser);
private:
    HTTPUrl m_url;
    HTTPStatus m_status;
    HTTPHeader m_header;
    HTTPBody m_body;

    http_parser m_parser;
    http_parser_settings m_settings;
    std::vector<char> m_cache;

    bool m_complete;
};


#endif //SOASERVICE_HTTPREQUEST_H
