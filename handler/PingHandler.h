//
// Created by Ivan Kishchenko on 15.05.16.
//

#ifndef SOASERVICE_PINGHANDLER_H
#define SOASERVICE_PINGHANDLER_H


#include "Handler.h"
#include "jsonrpc2/JsonRpc2RequestAbstract.h"
#include "jsonrpc2/JsonRpc2ResponseAbstract.h"
#include "jsonrpc2/JsonRpc2Handler.h"

class PingRequest : public JsonRpc2RequestAbstract {
public:
    virtual void Unmarshal(jsonTree &pt);

public:
    std::string Username;

};

class PingResponse : public JsonRpc2ResponseAbstract {
public:
    virtual jsonTree Marshal();

public:
    std::string Answer;
};

class PingHandler : public JsonRpc2HandlerAbstract {
public:
    virtual ResponsePtr Handle(RequestPtr request) {
        PingRequest *req = (PingRequest *) request.get();

        auto response = std::make_shared<PingResponse>();
        response->Answer = "Hello, " + req->Username + "!";

        return response;
    }

    virtual RequestPtr GetRequest() {
        return std::make_shared<PingRequest>();
    }
};


#endif //SOASERVICE_PINGHANDLER_H
