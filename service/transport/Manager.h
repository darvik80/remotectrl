//
// Created by Ivan Kishchenko on 14.05.16.
//

#ifndef SOASERVICE_MANAGER_H
#define SOASERVICE_MANAGER_H


#include <set>
#include "Interface.h"

class Manager {
public:
    void Register(TransportPtr transport);
    void Unregister(TransportPtr transport);
    ~Manager();
private:
    std::set<TransportPtr> m_set;
};

#endif //SOASERVICE_MANAGER_H
