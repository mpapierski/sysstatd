#if !defined(SYSSTATD_REQUEST_HANDLER_HPP_INCLUDED)
#define SYSSTATD_REQUEST_HANDLER_HPP_INCLUDED

#include <iostream>
#include <asio_http/http_server.hpp>

struct request_handler
{
	typedef basic_http_connection<request_handler> connection_type;
	void operator()(const connection_type::pointer & ptr);
};

#endif