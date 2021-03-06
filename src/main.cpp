#include <iostream>
#include <boost/asio.hpp>
#include "sysstatd/request_handler.hpp"
#include "sysstatd/sigar_service.hpp"

int
main()
{
	boost::asio::io_service io_service;
	boost::asio::use_service<sigar_service>(io_service);
	http_server<request_handler> server(io_service,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 5000));
	io_service.run();
}