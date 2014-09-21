#include "sysstatd/request_handler.hpp"
#include "json/json.h"

void request_handler::operator()(const connection_type::pointer & ptr)
{
	std::cout << "URL: " << ptr->get_request_url() << std::endl;
	if (ptr->get_request_url() == "/")
	{
		Json::Value resources;
		resources["/cpu"] = "CPU usage";
		resources["/mem"] = "Memory usage";
		Json::Value res;
		res["version"] = "1.0";
		res["resources"] = resources;
		ptr->send_response(200, res.toStyledString());
		return;
	}
	ptr->send_response(404, "Unknown endpoint");
}