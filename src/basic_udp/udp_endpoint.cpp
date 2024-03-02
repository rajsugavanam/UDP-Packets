#include "udp_endpoint.h"

#include "boost/asio/detail/cstdint.hpp"
#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/udp.hpp"
#include "boost/system/error_code.hpp"
#include <_types/_uint16_t.h>
#include <array>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;

udp_endpoint::udp_endpoint(boost::asio::io_context& io_context)
    : io_context_(io_context),
    socket_(boost::asio::ip::udp::socket(io_context)),
    buf_(MAX_RECV_BYTES) {

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
            on_write_(buf_, transferred);
        };
    socket_.async_send_to(buffer(data), endpoint, handler_lambda);
}

void udp_endpoint::async_read() {
    auto handler_lambda = [this](const error_code& ec, const size_t& transferred){
        on_read_(buf_, transferred);
        read_handler(ec, transferred);
    };
    socket_.async_receive_from(buffer(buf_), read_endpoint_, handler_lambda);

}

void udp_endpoint::on_read(void(*func)(const std::vector<char>&,const size_t&)) {
    on_read_ = func;
}

void udp_endpoint::on_write(void(*func)(const std::vector<char>&,const size_t&)) {
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
