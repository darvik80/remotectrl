//
// Created by Ivan Kishchenko on 15.05.16.
//

#include <string>
#include <boost/property_tree/json_parser.hpp>
#include "JsonRpc2RequestAbstract.h"

void JsonRpc2RequestAbstract::Decode(const std::string &json) {
    jsonTree pt;

    std::istringstream is(json);

    boost::property_tree::read_json(is, pt);
    Unmarshal(pt);
}
