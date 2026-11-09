#include <browser/tcp/TcpConnection.hpp>
#include <browser/tcp/TcpServer.hpp>
namespace TCP {

void TcpServer::StartAccept() {
    auto newConnection = TcpConnection::Create(ioContext);

    acceptor.async_accept(newConnection->GetSocket(), [this, newConnection](const boost::system::error_code &error) {
        if (!error) {
            newConnection->Start();
        }

        if (acceptor.is_open()) {
            StartAccept();
        }
    });
}

TcpServer::TcpServer(boost::asio::io_context &context, unsigned short port)
    : ioContext(context), acceptor(context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
    StartAccept();
}


}  // namespace TCP
