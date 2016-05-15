//
// Created by Ivan Kishchenko on 15.05.16.
//

#ifndef SOASERVICE_ROUTER_H
#define SOASERVICE_ROUTER_H


#include <map>
#include "../../handler/Handler.h"

template<class Handler>
class Router {
public:
    void Register(std::string route, std::shared_ptr<Handler> handler) {
        m_routes[route] = handler;
    }

    std::shared_ptr<Handler> Resolve(const std::string &route) {
        auto iter = m_routes.find(route);
        if (iter != m_routes.end()) {
            return iter->second;
        }

        return std::shared_ptr<Handler>();
    }

    ~Router() {
        m_routes.clear();
    }


private:
    std::map<std::string, std::shared_ptr<Handler> > m_routes;
};


#endif //SOASERVICE_ROUTER_H
