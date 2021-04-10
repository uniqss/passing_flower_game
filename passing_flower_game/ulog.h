#pragma once

#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_sinks.h"
#include <filesystem>

#if defined(WIN32)||defined(_WIN32)||defined(WINDOWS)
#include <string.h>
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#include <string.h>
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define ULOG_CRITICAL(fmt, ...) ULog::Instance()->GetLogger()->critical("{}#{} {} " fmt, __FILENAME__, __LINE__ , __FUNCTION__, __VA_ARGS__)
#define ULOG_ERROR(fmt,...) ULog::Instance()->GetLogger()->error("{}#{} {} " fmt, __FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define ULOG_WARN(fmt,...)  ULog::Instance()->GetLogger()->warn("{}#{} {} " fmt, __FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define ULOG_INFO(fmt,...)  ULog::Instance()->GetLogger()->info("{}#{} {} " fmt, __FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define ULOG_DEBUG(fmt,...) ULog::Instance()->GetLogger()->debug("{}#{} {} " fmt, __FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define ULOG_TRACE(fmt,...) ULog::Instance()->GetLogger()->trace("{}#{} {} " fmt, __FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__)

class ULog
{
public:
	ULog()
	{
		std::string strPath = std::filesystem::current_path().string() + "/logs/";
		std::filesystem::create_directories(strPath);
		std::string strFile = strPath + "ulog.log";

		spdlog::init_thread_pool(8192, 1);

#if 0
		logger_ = spdlog::stdout_logger_st<spdlog::async_factory>("logger");
#else

#if 1
		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
		sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_st>(strFile, 4, 0));
		logger_ = std::make_shared<spdlog::logger>("logger", begin(sinks), end(sinks));
		spdlog::register_logger(logger_);
#else
		//                logger_ = spdlog::create<spdlog::sinks::daily_file_sink<spdlog::details::null_mutex, spdlog::sinks::dateonly_daily_file_name_calculator> >("logger", path, SPDLOG_FILENAME_T("log"), 4, 0, false);
		logger_ = spdlog::daily_logger_st<spdlog::async_factory>("logger", strFile, 4, 0, false);
#endif

#endif
		//logger_->set_pattern("[%Y-%m-%d %H:%M:%S %f] [%t][%l] %v");
		//logger_->set_pattern("[source %s] [function %10!!] [line %#] %v");
		// https://github.com/gabime/spdlog/issues/235   redefine the macros to show file name/function/line
		//logger_->set_pattern("[%Y-%m-%d %H:%M:%S %f] [%t][%l] %v");
		// default pattern:
		//logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");

#if 1
		// no thread id
		logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%L] %v");
#else
		// multi thread, debug thread id
		logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%L][%t] %v");
#endif

		logger_->set_level((spdlog::level::level_enum)spdlog::level::trace);

		spdlog::flush_every(std::chrono::seconds(1));
	}
	~ULog()
	{
		spdlog::drop_all();
		logger_ = nullptr;
	}

	static ULog* Instance()
	{
		static ULog s_oT;
		return &s_oT;
	}

	inline std::shared_ptr<spdlog::logger> GetLogger()
	{
		return logger_;
	}

private:
	std::shared_ptr<spdlog::logger> logger_;
};
