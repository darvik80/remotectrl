//
// Created by Ivan Kishchenko on 14.05.16.
//

#include "HTTPRequest.h"
#include <string.h>

int HTTPRequest::onMessageBegin(http_parser *parser) {
    // HTTPRequest *self = (HTTPRequest *) parser->data;

    return 0;
}

int HTTPRequest::onURL(http_parser *parser, const char *at, size_t length) {
    HTTPRequest *self = (HTTPRequest *) parser->data;
    http_parser_url urlParser;
    auto res = http_parser_parse_url(at, length, 0, &urlParser);
    if (!res) {
        if (urlParser.field_set & (1 << UF_SCHEMA)) {
            self->m_url.Schema.assign(at + urlParser.field_data[UF_SCHEMA].off, urlParser.field_data[UF_SCHEMA].len);
        }
        if (urlParser.field_set & (1 << UF_HOST)) {
            self->m_url.Host.assign(at + urlParser.field_data[UF_HOST].off, urlParser.field_data[UF_HOST].len);
        }
        if (urlParser.field_set & (1 << UF_PORT)) {
            self->m_url.Port = urlParser.port;
        }
        if (urlParser.field_set & (1 << UF_PATH)) {
            self->m_url.Path.assign(at + urlParser.field_data[UF_PATH].off, urlParser.field_data[UF_PATH].len);
        }
        if (urlParser.field_set & (1 << UF_QUERY)) {
            self->m_url.Query.assign(at + urlParser.field_data[UF_QUERY].off, urlParser.field_data[UF_QUERY].len);
        }
        if (urlParser.field_set & (1 << UF_FRAGMENT)) {
            self->m_url.Fragment.assign(at + urlParser.field_data[UF_FRAGMENT].off,
                                        urlParser.field_data[UF_FRAGMENT].len);
        }
        if (urlParser.field_set & (1 << UF_USERINFO)) {
            self->m_url.UserInfo.assign(at + urlParser.field_data[UF_PATH].off, urlParser.field_data[UF_USERINFO].len);
        }
    }

    return res;
}

int HTTPRequest::onStatus(http_parser *parser, const char *at, size_t length) {
    HTTPRequest *self = (HTTPRequest *) parser->data;

    return 0;
}

int HTTPRequest::onHeaderField(http_parser *parser, const char *at, size_t length) {
    HTTPRequest *self = (HTTPRequest *) parser->data;
    self->m_header.Set(std::string(at, length), "");

    return 0;
}

int HTTPRequest::onHeaderValue(http_parser *parser, const char *at, size_t length) {
    HTTPRequest *self = (HTTPRequest *) parser->data;
    self->m_header.rbegin()->second.append(at, length);
    return 0;
}

int HTTPRequest::onHeaderComplete(http_parser *parser) {
    // HTTPRequest *self = (HTTPRequest *) parser->data;

    return 0;
}

int HTTPRequest::onBody(http_parser *parser, const char *at, size_t length) {
    HTTPRequest *self = (HTTPRequest *) parser->data;
    auto pos = self->m_body.size();
    self->m_body.resize(pos + length);
    memcpy(self->m_body.data() + pos, at, length);

    return 0;
}

int HTTPRequest::onMessageComplete(http_parser *parser) {
    HTTPRequest *self = (HTTPRequest *) parser->data;
    self->m_complete = true;

    return 0;
}

HTTPRequest::HTTPRequest()
        : m_complete(false) {
    m_settings.on_message_begin = onMessageBegin;
    m_settings.on_url = onURL;
    m_settings.on_status = onStatus;
    m_settings.on_header_field = onHeaderField;
    m_settings.on_header_value = onHeaderValue;
    m_settings.on_headers_complete = onHeaderComplete;
    m_settings.on_body = onBody;
    m_settings.on_message_complete = onMessageComplete;
    m_parser.data = this;

    http_parser_init(&m_parser, HTTP_REQUEST);
}

int HTTPRequest::Parse(const char *ptr, std::size_t size) {
    size_t pos = m_cache.size();
    m_cache.resize(size);
    memcpy(m_cache.data() + pos, ptr, size);

    auto block = http_parser_execute(&m_parser, &m_settings, m_cache.data(), m_cache.size());
    m_cache.erase(m_cache.begin(), m_cache.begin() + block);

    return 0;
}

bool HTTPRequest::IsComplete() {
    return m_complete;
}
