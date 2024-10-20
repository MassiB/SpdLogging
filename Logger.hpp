/**
 * @file Logger.hpp
 * @author Massinissa Bandou
 * @brief
 * @version 0.1
 * @date 2024-10-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef LOGGER_HPP_
#define LOGGER_HPP_
// System headers
#include <mutex>
#include <memory>
#include <new>
#include <tuple>
#include <sstream>
#include <string>
// SPD headers
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace
{
    /// @brief log level enum
    enum class LogLevel
    {
        INFO,
        DEBUG,
        WARNING,
        ERROR,
        CRITICAL
    };
    /// @brief Singleton class to handle logging using spdlog library
    class Logger
    {
    public:
        Logger(const Logger &) = delete;
        Logger(Logger &&) = delete;
        Logger &operator=(const Logger &) = delete;
        Logger &operator=(Logger &&) = delete;
        /// @brief get a single instance of logger class
        /// @return
        static Logger *getInstance() noexcept
        {
            std::call_once(m_onceFlag, []()
                           { m_instance.reset(new (std::nothrow) Logger()); });
            return m_instance.get();
        }
        /// @brief logging function
        /// @tparam ...Arg
        /// @param level
        /// @param ...args
        template <typename... Arg>
        void log(LogLevel level, Arg &&...args)
        {
            std::lock_guard<std::mutex> lock(m_mtx);
            std::stringstream ss;
            ((ss << args << " "), ...);
            switch (level)
            {
            case LogLevel::INFO:
                m_logger->info(ss.str());
                break;
            case LogLevel::DEBUG:
                m_logger->debug(ss.str());
                break;
            case LogLevel::WARNING:
                m_logger->warn(ss.str());
                break;
            case LogLevel::ERROR:
                m_logger->error(ss.str());
                break;
            case LogLevel::CRITICAL:
                m_logger->critical(ss.str());
                break;
            default:
                break;
            }
        }
    private:
        Logger()
        {
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            m_logger = std::make_shared<spdlog::logger>("Console", console_sink);
            m_logger->info("Logger has been initialized!");
            m_logger->set_level(spdlog::level::trace);
        };
        inline static std::once_flag m_onceFlag;
        inline static std::unique_ptr<Logger> m_instance{nullptr};
        inline static std::shared_ptr<spdlog::logger> m_logger;
        inline static std::mutex m_mtx;
    };
} // namespace

// Logging interface
#define LOG_INFO(...) \
    Logger::getInstance()->log(LogLevel::INFO, __VA_ARGS__)
#define LOG_DEBUG(...) \
    Logger::getInstance()->log(LogLevel::DEBUG, __VA_ARGS__)
#define LOG_WARN(...) \
    Logger::getInstance()->log(LogLevel::WARNING, __VA_ARGS__)
#define LOG_ERROR(...) \
    Logger::getInstance()->log(LogLevel::ERROR, __VA_ARGS__)
#define LOG_FAULT(...) \
    Logger::getInstance()->log(LogLevel::CRITICAL, __VA_ARGS__)

#endif // LOGGER_HPP_
