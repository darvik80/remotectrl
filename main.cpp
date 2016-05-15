#include <iostream>

using namespace std;

#include "service/TCPServer.h"
#include "service/transport/Router.h"
#include "handler/PingHandler.h"
#include "handler/jsonrpc2/JsonRpc2Handler.h"

int main() {
    try {
        Router<IHandler> jsonRpc2Router;
        jsonRpc2Router.Register("ping", std::make_shared<PingHandler>());

        Router<IHTTPHandler> httpRouter;
        httpRouter.Register("/rpc", std::make_shared<JsonRpc2Handler>(jsonRpc2Router));

        TCPServer server("0.0.0.0", 9080, httpRouter);
        server.Run();
    } catch (std::exception& ex) {
        std::cerr << ex.what();
    }

    return 0;
}