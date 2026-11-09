#include <boost/asio.hpp>
#include <browser/tcp/TcpServer.hpp>
#include <exception>
#include <iostream>

int main() {
    try {
        boost::asio::io_context ioContext;
        TCP::TcpServer server(ioContext, 8080);

        std::cout << "Server listening on port 8080\n";
        ioContext.run();
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
