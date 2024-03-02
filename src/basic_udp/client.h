#include "udp_endpoint.h"
#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/udp.hpp"
#include "boost/system/error_code.hpp"
#include <iostream>
#include <string>

class udp_client : public udp_endpoint {
    private:
        boost::asio::ip::udp::resolver::results_type endpoint_iterator_;

        void read_handler(const boost::system::error_code& ec, const size_t& transferred) {
            /* print_handler_error(ec); */
            /* if (transferred > 0) { */
            /*     std::cout << buf_ << std::endl; */
            /* } */
            on_read_(buf_, transferred);
        }
        void write_handler(const boost::system::error_code& ec, const size_t& transferred) {
            /* print_handler_error(ec); */
            on_write_(buf_, transferred);
        }

    public:
        udp_client(boost::asio::io_context& io_context)
            : udp_endpoint(io_context) {}
        void async_read();
        void resolve_location(const std::string& address, const std::string& port);
        void write_bytes(const std::string& data);
};
