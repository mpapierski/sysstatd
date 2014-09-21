#include "sysstatd/request_handler.hpp"
#include "sysstatd/sigar_service.hpp"
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
	if (ptr->get_request_url() == "/cpu/")
	{
		Json::Value resource;
		sigar_cpu_list_t cpu_list;
		boost::asio::use_service<stat_service>(ptr->get_socket().get_io_service())
			.get_cpu_list(&cpu_list);
		for (unsigned int i = 0; i < cpu_list.number; ++i)
		{
			Json::Value cpu;
			cpu["idle"] = static_cast<Json::LargestUInt>(cpu_list.data[i].idle);
			cpu["user"] = static_cast<Json::LargestUInt>(cpu_list.data[i].user);
			cpu["sys"] = static_cast<Json::LargestUInt>(cpu_list.data[i].sys);
			cpu["nice"] = static_cast<Json::LargestUInt>(cpu_list.data[i].nice);
			cpu["idle"] = static_cast<Json::LargestUInt>(cpu_list.data[i].idle);
			cpu["wait"] = static_cast<Json::LargestUInt>(cpu_list.data[i].wait);
			cpu["irq"] = static_cast<Json::LargestUInt>(cpu_list.data[i].irq);
			cpu["soft_irq"] = static_cast<Json::LargestUInt>(cpu_list.data[i].soft_irq);
			cpu["stolen"] = static_cast<Json::LargestUInt>(cpu_list.data[i].stolen);
			cpu["total"] = static_cast<Json::LargestUInt>(cpu_list.data[i].total);
			resource.append(cpu);
		}
		ptr->send_response(200, resource.toStyledString());
		return;
	}
	ptr->send_response(404, "Unknown endpoint");
}