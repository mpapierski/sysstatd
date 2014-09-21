#include "sysstatd/sigar_service.hpp"

boost::asio::io_service::id stat_service::id;


stat_service::stat_service(boost::asio::io_service & io_service)
	: boost::asio::io_service::service(io_service)
	, sigar_(NULL)
{
	if (::sigar_open(&sigar_) != SIGAR_OK)
	{
		throw std::runtime_error("Unable to initialize sigar");
	}
}

void stat_service::shutdown_service()
{
	assert(sigar_);
	int rc = ::sigar_close(sigar_);
	if (rc != SIGAR_OK)
	{
		throw std::runtime_error("Unable to close sigar");
	}
}

void stat_service::get_cpu_list(sigar_cpu_list_t * cpulist)
{
	assert(sigar_);
	int status = sigar_cpu_list_get(sigar_, cpulist);
	if (status != SIGAR_OK)
	{
		// TODO: error codes
		throw std::runtime_error("cpu_list_get error");
	}
}
