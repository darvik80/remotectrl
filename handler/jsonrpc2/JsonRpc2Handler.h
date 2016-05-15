//
// Created by Ivan Kishchenko on 15.05.16.
//

#ifndef SOASERVICE_JSONRPC2HANDLER_H
#define SOASERVICE_JSONRPC2HANDLER_H


#include <boost/optional.hpp>
#include "../Handler.h"
#include "../../service/transport/Router.h"
#include "JsonRpc2RequestAbstract.h"
#include "JsonRpc2ResponseAbstract.h"
#include "../../service/transport/http/HTTPRequest.h"
#include "../../service/transport/http/HTTPResponse.h"
#include "../../service/transport/http/HTTPHeaders.h"

class JsonRpc2Request : public JsonRpc2RequestAbstract {
public:
    virtual void Unmarshal(jsonTree &tree);

public:
    std::string Version;
    std::string Method;
    boost::optional<jsonTree> Params;
    std::string Id;
};

class JsonRpc2Response : public JsonRpc2ResponseAbstract {
public:
    virtual jsonTree Marshal();

public:
    std::string Version;
    boost::optional<jsonTree> Result;
    boost::optional<jsonTree> Error;
    std::string Id;
};

class JsonRpc2Error : public IJsonMarshaler {
public:
    enum Codes {
        ParseError = -32700,
        InvalidRequest = -32600,
        MethodNotFound = -32601,
        InvalidParams = -32602,
        InternalError = -32603,
        ServerError = -32000,
    };

    JsonRpc2Error(int code);

    JsonRpc2Error(int code, const std::string &message);

    virtual jsonTree Marshal();

private:
    int m_code;
    std::string m_message;
};

class JsonRpc2HandlerAbstract : public IHandler {
public:
    std::string GetContentType() {
        return HTTPContentTypeJson;
    }
};

class JsonRpc2Handler : public IHTTPHandler {
public:
    JsonRpc2Handler(Router<IHandler> &router);

    virtual void Handle(HTTPRequest &request, HTTPResponse &response);

private:
    Router<IHandler> &m_router;
};


#endif //SOASERVICE_JSONRPC2HANDLER_H
