//
// Created by Ivan Kishchenko on 14.05.16.
//

#include "Manager.h"

void Manager::Register(TransportPtr transport) {
    m_set.insert(transport);
    transport->Start();
}

void Manager::Unregister(TransportPtr transport) {
    auto iter = m_set.find(transport);
    if (iter != m_set.end()) {
        transport->Stop();
        m_set.erase(iter);
    }
}

Manager::~Manager() {
    for(auto iter: m_set) {
        iter->Stop();
    }

    m_set.clear();
}
