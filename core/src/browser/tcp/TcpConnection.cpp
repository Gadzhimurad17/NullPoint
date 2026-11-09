#include <browser/tcp/TcpConnection.hpp>
#include <functional>
#include <iostream>
namespace TCP {

TcpConnection::pointer TcpConnection::Create(boost::asio::io_context &ioContext) {
    return pointer(new TcpConnection(ioContext));
}

void TcpConnection::Start() {
    message = "Hello from Nullpoint";
    boost::asio::async_write(
        socket, boost::asio::buffer(message),
        std::bind(&TcpConnection::HandleWrite, shared_from_this(), std::placeholders::_1, std::placeholders::_2)

    );
}

boost::asio::ip::tcp::socket &TcpConnection::GetSocket() { return socket; }

void TcpConnection::HandleWrite(const boost::system::error_code &error, std::size_t bytesTransferred) {
    if (error) {
        std::cerr << "send failed: " << error.message() << std::endl;
    }

    std::cout << "Sent " << bytesTransferred << " bytes\n";
}
}  // namespace TCP
