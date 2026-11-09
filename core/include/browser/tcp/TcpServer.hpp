#pragma once

#include <boost/asio.hpp>

namespace TCP {

class TcpServer {
private:
    boost::asio::io_context &ioContext;
    boost::asio::ip::tcp::acceptor acceptor;

    void StartAccept();

public:
    TcpServer(boost::asio::io_context &context, unsigned short port);
};

}  // namespace TCP
