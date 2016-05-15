//
// Created by Ivan Kishchenko on 15.05.16.
//

#include "PingHandler.h"

#include <boost/property_tree/json_parser.hpp>

using namespace boost;

void PingRequest::Unmarshal(jsonTree &pt) {
    Username = pt.get<std::string>("username");
}

jsonTree PingResponse::Marshal() {
    property_tree::ptree pt;

    pt.put("answer", Answer);
    return pt;
}