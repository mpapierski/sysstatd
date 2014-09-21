#include "sysstatd/request_handler.hpp"
#include "sysstatd/sigar_service.hpp"
#include "json/json.h"

void request_handler::operator()(const connection_type::pointer & ptr)
{
	std::cout << "URL: " << ptr->get_request_url() << std::endl;
	// Resources
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
	// CPU usage
	if (ptr->get_request_url() == "/cpu/")
	{
		Json::Value cpu_list = boost::asio::use_service<sigar_service>(ptr->get_socket().get_io_service())
			.get_cpu_list();
		ptr->send_response(200, cpu_list.toStyledString());
		return;
	}
	// Memory usage
	if (ptr->get_request_url() == "/mem/")
	{
		Json::Value mem = boost::asio::use_service<sigar_service>(ptr->get_socket().get_io_service())
			.get_mem();
		ptr->send_response(200, mem.toStyledString());
		return;
	}
	ptr->send_response(404, "Unknown endpoint");
}