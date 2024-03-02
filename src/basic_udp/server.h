#pragma once

#include "udp_endpoint.h"
#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/udp.hpp"
#include <iostream>
#include <iterator>

class udp_server : public udp_endpoint {
    private:
        void read_handler(const boost::system::error_code& ec, const size_t& transferred) {
            async_read();
        }
        void write_handler(const boost::system::error_code& ec, const size_t& transferred) {
        }

    public:
        udp_server(boost::asio::io_context& io_context)
            : udp_endpoint(io_context) {}

        void start_read();
        void bind_socket(const unsigned int& port);
};
