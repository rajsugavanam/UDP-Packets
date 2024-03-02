#include "client.h"
#include "boost/asio/buffer.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;

void udp_client::resolve_location(const std::string& address, const std::string& port) {
    udp::resolver resolver(io_context_);
    udp::resolver::query q(udp::v4(), address, port);
    endpoint_iterator_ = resolver.resolve(q);
}

void udp_client::write_bytes(const std::string& data) {
    async_write(data, *endpoint_iterator_);
}

void udp_client::async_read() {
    async_read();
}

/* int main() { */
/*     io_context context; */
/*     udp_client client(context); */

/*     const std::string s = "this is a test string containing an arbitrary amount of characters"; */

/*     client.resolve_location("127.0.0.1", "2000"); */
/*     client.write_bytes(s); */

/*     std::function<void(const char*,const size_t&)> onread = [](const char* buf, const size_t& transferred) { */
/*         std::cout << buf << std::endl; */
/*     }; */

/*     client.on_read(onread); */

/*     client.start(); */
/* } */
