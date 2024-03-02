#include "boost/asio.hpp"
#include "boost/asio/io_context.hpp"
#include <algorithm>
#include <iterator>
#include <client.h>
#include <sstream>

int main(int argc, char* argv[]) {
    boost::asio::io_context context;
    udp_client client(context);
    client.resolve_location("127.0.0.1", "2000");

    std::ostringstream stream;
    for (unsigned int i=1; i<argc; i++) {
        stream << argv[i];
    }

    client.write_bytes(stream.str());

    client.do_work();
    return 0;
}
