//
// Created by Ivan Kishchenko on 15.05.16.
//

#ifndef SOASERVICE_JSONRPC2REQUESTABSTRACT_H
#define SOASERVICE_JSONRPC2REQUESTABSTRACT_H


#include "../Handler.h"

class JsonRpc2RequestAbstract : public IRequest {
public:
    virtual void Decode(const std::string &json);
};


#endif //SOASERVICE_JSONRPC2REQUESTABSTRACT_H
