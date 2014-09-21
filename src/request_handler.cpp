#include "sysstatd/request_handler.hpp"

void request_handler::operator()(const connection_type::pointer & ptr)
{
	ptr->send_response(200, "Hello world");
}