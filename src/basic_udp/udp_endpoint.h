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

        std::function<void(const char*, const size_t&)> on_read_ = [](const char*, const size_t&){};
        std::function<void(const char*, const size_t&)> on_write_ = [](const char*, const size_t&){};

        static const unsigned short RECV_SIZE = 16;
        char buf_[RECV_SIZE];

        void async_read();
        void print_handler_error(const boost::system::error_code& ec);
        virtual void read_handler(const boost::system::error_code& ec, const
                size_t& transferred) {
            on_write_(buf_, transferred);
        }
        virtual void write_handler(const boost::system::error_code& ec, const
                size_t& transferred) {
            on_read_(buf_, transferred);
        }
    public:
        udp_endpoint(boost::asio::io_context& io_context);
        ~udp_endpoint();
        void start();
        void stop();
        std::string get_local_ip();
        std::string get_remote_ip();
        void async_write(const std::string& data, const boost::asio::ip::udp::endpoint& endpoint);
        /*
         * `const char*`: the chunk of data read will be filled in here.
         * `const size_t&`: the size of what was read will be filled in here.
         */
        void on_read(std::function<void(const char*,const size_t&)>& func);
        /*
         * `const char*`: the chunk of data sent will be filled in here.
         * `const size_t&`: the size of what was written will be filled in here.
         */
        void on_write(std::function<void(const char*,const size_t&)>& func);
};
