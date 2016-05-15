//
// Created by Ivan Kishchenko on 15.05.16.
//

#include "JsonRpc2Handler.h"
#include <boost/property_tree/json_parser.hpp>

using namespace boost;

void JsonRpc2Request::Unmarshal(jsonTree &pt) {
    Version = pt.get<std::string>("jsonrpc");
    Id = pt.get<std::string>("id");
    Method = pt.get<std::string>("method");
    Params = pt.get_child_optional("params");
}

jsonTree JsonRpc2Response::Marshal() {
    jsonTree pt;

    pt.put("jsonrpc", Version);
    pt.put("id", Id);
    if (Result) {
        pt.put_child("result", Result.get());
    }
    if (Error) {
        pt.put_child("error", Error.get());
    }

    return pt;
}

JsonRpc2Error::JsonRpc2Error(int code)
        : m_code(code) {
    switch (m_code) {
        case ParseError:
            m_message = "Invalid JSON was received by the server.\nAn error occurred on the server while parsing the JSON text.";
            break;
        case InvalidRequest:
            m_message = "The JSON sent is not a valid Request object.";
            break;
        case MethodNotFound:
            m_message = "The method does not exist / is not available.";
            break;
        case InvalidParams:
            m_message = "Invalid method parameter(s).";
            break;
        case InternalError:
            m_message = "Internal JSON-RPC error.";
            break;
        case ServerError:
            m_message = "Reserved for implementation-defined server-errors.";
            break;
        default:
            m_message = "Unknown error";
    }
}

JsonRpc2Error::JsonRpc2Error(int code, const std::string &message)
        : m_code(code), m_message(message) {

}

jsonTree JsonRpc2Error::Marshal() {
    property_tree::ptree pt;

    pt.put("code", m_code);
    pt.put("message", m_message);

    return pt;
}

JsonRpc2Handler::JsonRpc2Handler(Router<IHandler> &router)
        : m_router(router) {

}

void JsonRpc2Handler::Handle(HTTPRequest &request, HTTPResponse &response) {
    JsonRpc2Request jsonRequest;
    JsonRpc2Response jsonResponse;
    try {

        jsonRequest.Decode(std::string((const char *) request.Body().data(), request.Body().size()));
        jsonResponse.Id = jsonRequest.Id;
        jsonResponse.Version = jsonRequest.Version;
        auto handler = m_router.Resolve(jsonRequest.Method);
        if (handler) {
            auto req = handler->GetRequest();
            if (jsonRequest.Params) {
                req->Unmarshal(jsonRequest.Params.get());
            }
            auto resp = handler->Handle(req);
            if (!resp) {
                jsonResponse.Error = std::make_shared<JsonRpc2Error>(JsonRpc2Error::InternalError)->Marshal();
            } else {
                jsonResponse.Result = resp->Marshal();
            }
        } else {
            jsonResponse.Error = std::make_shared<JsonRpc2Error>(JsonRpc2Error::MethodNotFound)->Marshal();
        }
    } catch (property_tree::json_parser::json_parser_error &je) {
        jsonResponse.Error = std::make_shared<JsonRpc2Error>(JsonRpc2Error::InvalidParams, je.what())->Marshal();
    } catch (std::exception &ex) {
        jsonResponse.Error = std::make_shared<JsonRpc2Error>(JsonRpc2Error::InternalError, ex.what())->Marshal();
    }

    response.Header().Set(HTTPContentType, HTTPContentTypeJson);
    response.Write(jsonResponse.Encode());
}
