//
// Created by Ivan Kishchenko on 15.05.16.
//

#ifndef SOASERVICE_JSONRPC2RESPONSEABSTACT_H
#define SOASERVICE_JSONRPC2RESPONSEABSTACT_H


#include "../Handler.h"

class JsonRpc2ResponseAbstract : public IResponse {
public:
    virtual std::string Encode();
};


#endif //SOASERVICE_JSONRPC2RESPONSEABSTACT_H
