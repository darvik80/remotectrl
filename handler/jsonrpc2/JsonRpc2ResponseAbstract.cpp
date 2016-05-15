//
// Created by Ivan Kishchenko on 15.05.16.
//

#include <boost/property_tree/json_parser.hpp>
#include "JsonRpc2ResponseAbstract.h"

std::string JsonRpc2ResponseAbstract::Encode() {
    auto pt = Marshal();
    std::ostringstream os;
    boost::property_tree::write_json(os, pt, false);

    return os.str();
}
