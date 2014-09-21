#include "sysstatd/sigar_service.hpp"

boost::asio::io_service::id sigar_service::id;


sigar_service::sigar_service(boost::asio::io_service & io_service)
	: boost::asio::io_service::service(io_service)
	, sigar_(NULL)
{
	if (::sigar_open(&sigar_) != SIGAR_OK)
	{
		throw std::runtime_error("Unable to initialize sigar");
	}
}

void sigar_service::shutdown_service()
{
	assert(sigar_);
	int rc = ::sigar_close(sigar_);
	if (rc != SIGAR_OK)
	{
		throw std::runtime_error("Unable to close sigar");
	}
}

Json::Value sigar_service::get_cpu_list()
{
	assert(sigar_);
	sigar_cpu_list_t cpulist;
	int status = sigar_cpu_list_get(sigar_, &cpulist);
	if (status != SIGAR_OK)
	{
		// TODO: error codes
		throw std::runtime_error("cpu_list_get error");
	}
	// Serialize
	Json::Value res;
	for (unsigned int i = 0; i < cpulist.number; ++i)
	{
		Json::Value cpu;
		cpu["idle"] = static_cast<Json::LargestUInt>(cpulist.data[i].idle);
		cpu["user"] = static_cast<Json::LargestUInt>(cpulist.data[i].user);
		cpu["sys"] = static_cast<Json::LargestUInt>(cpulist.data[i].sys);
		cpu["nice"] = static_cast<Json::LargestUInt>(cpulist.data[i].nice);
		cpu["idle"] = static_cast<Json::LargestUInt>(cpulist.data[i].idle);
		cpu["wait"] = static_cast<Json::LargestUInt>(cpulist.data[i].wait);
		cpu["irq"] = static_cast<Json::LargestUInt>(cpulist.data[i].irq);
		cpu["soft_irq"] = static_cast<Json::LargestUInt>(cpulist.data[i].soft_irq);
		cpu["stolen"] = static_cast<Json::LargestUInt>(cpulist.data[i].stolen);
		cpu["total"] = static_cast<Json::LargestUInt>(cpulist.data[i].total);
		res.append(cpu);
	}
	if (sigar_cpu_list_destroy(sigar_, &cpulist) != SIGAR_OK)
	{
		throw std::runtime_error("cpu_list_destroy error");
	}
	return res;
}

Json::Value sigar_service::get_mem()
{
	sigar_mem_t mem;
	if (sigar_mem_get(sigar_, &mem) != SIGAR_OK)
	{
		throw std::runtime_error("mem_get error");
	}
	Json::Value res;
	res["ram"] = static_cast<Json::LargestUInt>(mem.ram);
    res["total"] = static_cast<Json::LargestUInt>(mem.total);
    res["used"] = static_cast<Json::LargestUInt>(mem.used);
    res["free"] = static_cast<Json::LargestUInt>(mem.free);
    res["actual_used"] = static_cast<Json::LargestUInt>(mem.actual_used);
    res["actual_free"] = static_cast<Json::LargestUInt>(mem.actual_free);
    res["used_percent"] = mem.used_percent;
    res["free_percent"] = mem.free_percent;
    return res;
}