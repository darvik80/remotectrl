//
// Created by Ivan Kishchenko on 14.05.16.
//

#ifndef SOASERVICE_HTTPOBJECTS_H
#define SOASERVICE_HTTPOBJECTS_H

#include <string>
#include <vector>
#include <map>

class HTTPHeader : public std::map<std::string, std::string> {
public:
    void Set(const std::string &field, const std::string &value) {
        this->insert(std::make_pair(field, value));
    }

    std::string Get(const std::string &field) {
        auto iter = this->find(field);
        if (iter != this->end()) {
            return iter->second;
        }

        return "";
    }


private:
};

typedef std::vector<uint8_t> HTTPBody;

struct HTTPUrl {
    std::string Schema;
    std::string Host;
    uint16_t Port;
    std::string Path;
    std::string Query;
    std::string Fragment;
    std::string UserInfo;
};

typedef int HTTPStatus;

#endif //SOASERVICE_HTTPOBJECTS_H
