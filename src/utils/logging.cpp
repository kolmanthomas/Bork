#include "logging.hpp"


namespace utils 
{
	namespace
	{
		const std::string default_sink_name = "fb.log";
	}


	void init_logger()
	{
		auto logger = spdlog::basic_logger_mt("def_logger", default_sink_name);	
		logger->set_pattern("[%l] | [%t] | [%v] ");
		spdlog::set_default_logger(logger);
		spdlog::info("Default logger");
	}
}


