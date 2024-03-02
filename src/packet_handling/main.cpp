#include "boost/asio.hpp"
#include "boost/asio/io_context.hpp"
#include <server.h>

void foo(const char* buf, const size_t& transferred) {
    std::cout << buf << std::endl;
}

int main() {
    boost::asio::io_context context;
    udp_server server(context);
    server.bind_socket(2000);
    server.on_read(&foo);

    server.start_read();

    server.do_work();
}
