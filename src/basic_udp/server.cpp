#include "server.h"
#include "boost/asio/buffer.hpp"
#include <iostream>
#include <sstream>

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;

void udp_server::bind_socket(const unsigned int &port) {
    if (socket_.is_open()) {
        socket_.bind(udp::endpoint(udp::v4(), port));
    } else {
        std::cout << "Failed to bind socket. Socket was not open." << std::endl;
    }
}

void udp_server::start_read() {
    async_read();
}

/* int main() { */
/*     io_context context; */
/*     udp_server server(context); */
/*     server.bind_socket(2000); */
/*     server.start_read(); */

/*     server.start(); */
/* } */
