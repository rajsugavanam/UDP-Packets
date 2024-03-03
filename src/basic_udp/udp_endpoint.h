#pragma once

#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/udp.hpp"
#include "boost/system/error_code.hpp"
#include <functional>
#include <string>

class udp_endpoint {
    protected:
        boost::asio::io_context& io_context_;
        boost::asio::ip::udp::socket socket_;
        boost::asio::ip::udp::endpoint read_endpoint_;

        void(*on_read_)(
                const std::vector<char>&,
                const boost::asio::ip::udp::endpoint&,
                const size_t&) =
            [](const std::vector<char>&, const boost::asio::ip::udp::endpoint&,
                    const size_t&){};
        void(*on_write_)(
                const std::vector<char>&, const size_t&) =
            [](const std::vector<char>&, const size_t&){};

        static const unsigned short MAX_RECV_BYTES = 16384; // say goodbye to 16kb of memory :)
        /* char buf_[RECV_SIZE]; */
        std::vector<char> buf_; // initialized with a max size of MAX_RECV_BYTES

        void async_read();
        void print_handler_error(const boost::system::error_code& ec);
        virtual void read_handler(const boost::system::error_code& ec, const
                size_t& transferred) {
        }
        virtual void write_handler(const boost::system::error_code& ec, const
                size_t& transferred) {
        }
    public:
        udp_endpoint(boost::asio::io_context& io_context);
        ~udp_endpoint();
        void do_work();
        void stop_work();
        std::string get_local_ip();
        std::string get_remote_ip();
        void async_write(const std::string& data, const boost::asio::ip::udp::endpoint& endpoint);
        void on_read(void(*func)(const std::vector<char>&,const
                    boost::asio::ip::udp::endpoint&,const size_t&));
        void on_write(void(*func)(const std::vector<char>&,const size_t&));
};
