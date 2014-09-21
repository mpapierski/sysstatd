#if !defined(SYSSTATD_SIGAR_SERVICE_HPP_INCLUDED_)
#define SYSSTATD_SIGAR_SERVICE_HPP_INCLUDED_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "sigar.h"

struct stat_service
	: boost::asio::io_service::service
{
	static boost::asio::io_service::id id;
	sigar_t *sigar_;
	stat_service(boost::asio::io_service & io_service);
	void shutdown_service();
	void get_cpu_list(sigar_cpu_list_t * cpulist); // throws
	
};

#endif