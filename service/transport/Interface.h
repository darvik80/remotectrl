//
// Created by Ivan Kishchenko on 14.05.16.
//

#ifndef SOASERVICE_INTERFACE_H
#define SOASERVICE_INTERFACE_H

#include <memory>

class ITransport {
public:
    virtual void Start() = 0;
    virtual void OnRecv(const uint8_t* ptr, std::size_t size) = 0;
    virtual void Stop() = 0;
};

typedef std::shared_ptr<ITransport> TransportPtr;

#endif //SOASERVICE_INTERFACE_H
