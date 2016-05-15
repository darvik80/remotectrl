//
// Created by Ivan Kishchenko on 14.05.16.
//

#ifndef SOASERVICE_HANDLER_H
#define SOASERVICE_HANDLER_H

#include <string>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include "../service/transport/http/HTTPRequest.h"
#include "../service/transport/http/HTTPResponse.h"

typedef boost::property_tree::ptree jsonTree;

class IJsonMarshaler {
public:
    virtual jsonTree Marshal() = 0;
};

class IJsonUnmarshaler {
public:
    virtual void Unmarshal(jsonTree &tree) = 0;
};

class IRequest : public IJsonUnmarshaler {
public:
    virtual void Decode(const std::string &json) = 0;
};

typedef std::shared_ptr<IRequest> RequestPtr;

class IResponse : public IJsonMarshaler {
public:
    virtual std::string Encode() = 0;
};

typedef std::shared_ptr<IResponse> ResponsePtr;

class IHandler {
public:
    virtual ResponsePtr Handle(RequestPtr request) = 0;

    virtual RequestPtr GetRequest() = 0;

    virtual std::string GetContentType() = 0;
};

typedef std::shared_ptr<IHandler> HandlerPtr;

class IHTTPHandler {
public:
    virtual void Handle(HTTPRequest &request, HTTPResponse &response) = 0;
};

typedef std::shared_ptr<IHTTPHandler> HTTPHandlerPtr;

#endif //SOASERVICE_HANDLER_H
