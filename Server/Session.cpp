#include <boost/beast/core/ostream.hpp>
#include "Session.h"
#include "Request.h"
#include "JsonParser.h"


Session::Session(tcp::socket&& socket, RequestsHandler* handler)
: ws_(std::move(socket)), handler(handler)
{

}

void Session::run()
{
    ws_.set_option(
            websocket::stream_base::timeout::suggested(
                    beast::role_type::server));

    ws_.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res)
            {
                res.set(http::field::server,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-server-async");
            }));

    ws_.async_accept(
            beast::bind_front_handler(
                    &Session::onAccept,
                    shared_from_this()));
}


void Session::onAccept(beast::error_code ec)
{
    if(ec)
        return fail(ec, "accept");

    doRead();
}


void Session::doRead()
{
    ws_.async_read(
            buffer_,
            beast::bind_front_handler(
                    &Session::onRead,
                    shared_from_this()));
}

void Session::onRead(
        beast::error_code ec,
        std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec == websocket::error::closed)
        return;

    if(ec)
        return fail(ec, "read");

    std::string data(boost::beast::buffers_to_string(buffer_.data()));

    Request r = JsonParser::JsonToRequest(nlohmann::json::parse(data));
    nlohmann::json j = handler->handleRequest(r);


    std::string response = to_string(j);
    buffer_.consume(buffer_.size());
    boost::asio::buffer_copy(buffer_.prepare(response.size()), boost::asio::buffer(response));
    buffer_.commit(response.size());


    ws_.text(ws_.got_text());
    ws_.async_write(
            buffer_.data(),
            beast::bind_front_handler(
                    &Session::onWrite,
                    shared_from_this()));
}

void Session::onWrite(
        beast::error_code ec,
        std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec)
        return fail(ec, "write");

    buffer_.consume(buffer_.size());
    doRead();
}

void Session::setHandler (RequestsHandler * handler){
    handler = handler;
}

void Session::fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}