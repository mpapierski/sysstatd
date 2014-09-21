#if !defined(SYSSTATD_SIGAR_SERVICE_HPP_INCLUDED_)
#define SYSSTATD_SIGAR_SERVICE_HPP_INCLUDED_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "sigar.h"
#include "json/json.h"

struct sigar_service
	: boost::asio::io_service::service
{
	static boost::asio::io_service::id id;
	sigar_t *sigar_;
	sigar_service(boost::asio::io_service & io_service);
	void shutdown_service();
	Json::Value get_cpu_list(); // throws
	Json::Value get_mem(); // throws
};

#endif