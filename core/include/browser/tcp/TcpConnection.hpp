#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <string>

namespace TCP {

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
private:
    boost::asio::ip::tcp::socket socket;
    std::string message;

    explicit TcpConnection(boost::asio::io_context &ioContext) : socket(ioContext) {}

public:
    using pointer = std::shared_ptr<TcpConnection>;
    static pointer Create(boost::asio::io_context &ioContext);
    void Start();
    void HandleWrite(const boost::system::error_code &error, std::size_t bytesTransferred);
    boost::asio::ip::tcp::socket &GetSocket();
};

}  // namespace TCP
