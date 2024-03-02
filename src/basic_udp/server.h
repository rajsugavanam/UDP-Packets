#include "udp_endpoint.h"
#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/udp.hpp"
#include <iostream>
#include <iterator>

class udp_server : public udp_endpoint {
    private:
        void read_handler(const boost::system::error_code& ec, const size_t& transferred) {
            /* if (transferred > 0) { */
            /*     std::cout << "Transferred: " << transferred << std::endl; */
            /*     for (int i=0; i<transferred; i++) { */
            /*         std::cout << buf_[i]; */
            /*     } */
            /*     std::cout << std::endl; */
            /* } */
            on_read_(buf_, transferred);
            async_read();
        }
        void write_handler(const boost::system::error_code& ec, const size_t& transferred) {
            on_write_(buf_, transferred);
        }

    public:
        udp_server(boost::asio::io_context& io_context)
            : udp_endpoint(io_context) {}

        void start_read();
        void bind_socket(const unsigned int& port);
};
