#include "boost/asio.hpp"
#include "boost/asio/io_context.hpp"
#include <algorithm>
#include <iterator>
#include <server.h>

void foo(const std::vector<char>& buf, const size_t& transferred) {
    if (transferred > 0) {
        for (int i=0; i<transferred; i++) {
            std::cout << buf[i];
        }
        std::cout << std::endl;
    }
}

int main() {
    boost::asio::io_context context;
    udp_server server(context);
    server.bind_socket(2000);
    server.on_read(&foo);

    server.start_read();

    server.do_work();

    return 0;
}
