#include "udp_endpoint.h"

#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/udp.hpp"
#include "boost/system/error_code.hpp"
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;

udp_endpoint::udp_endpoint(boost::asio::io_context& io_context)
    : io_context_(io_context),
    socket_(boost::asio::ip::udp::socket(io_context)) {

    socket_.open(boost::asio::ip::udp::v4());
}

udp_endpoint::~udp_endpoint() {
    socket_.close();
}

void udp_endpoint::do_work() {
    io_context_.run();
}

void udp_endpoint::stop_work() {
    io_context_.stop();
}

void udp_endpoint::async_write(const std::string& data, const udp::endpoint& endpoint) {
    auto handler_lambda =
        [this](const error_code& ec, const size_t& transferred){
            write_handler(ec, transferred);
        };
    for (int i=0; i<data.size(); i=i+RECV_SIZE) {
        /* char data_arr[RECV_SIZE]; */
        std::vector<char> data_arr;
        for (int j=0; j<RECV_SIZE; j++) {
            if (i+j<data.size()) {
                data_arr.push_back(data[i+j]);
            } else {
                break;
            }
        }
        socket_.async_send_to(buffer(data_arr), endpoint, handler_lambda);
    }
}

void udp_endpoint::async_read() {
    auto handler_lambda = [this](const error_code& ec, const size_t& transferred){
        read_handler(ec, transferred);
    };
    socket_.async_receive_from(buffer(buf_), read_endpoint_, handler_lambda);
}

void udp_endpoint::on_read(void(*func)(const char*,const size_t&)) {
    on_read_ = func;
}

void udp_endpoint::on_write(void(*func)(const char*,const size_t&)) {
    on_write_ = func;
}

void udp_endpoint::print_handler_error(const boost::system::error_code& ec) {
    std::cout << ec.message() << std::endl;
}

std::string udp_endpoint::get_local_ip() {
    std::ostringstream strstream;
    strstream << socket_.local_endpoint().address() << ":" << socket_.local_endpoint().port() << std::endl;
    return strstream.str();
}

std::string udp_endpoint::get_remote_ip() {
    std::ostringstream strstream;
    strstream << socket_.remote_endpoint().address() << ":" << socket_.remote_endpoint().port() << std::endl;
    return strstream.str();
}
