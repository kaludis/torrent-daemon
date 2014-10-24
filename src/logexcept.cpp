#include "logexcept.h"

namespace logger
{

LoggerException::LoggerException(const char* msg) noexcept
        : msg_(msg)
{}

LoggerException::LoggerException(std::string& msg) noexcept
        : msg_(msg)
{}

LoggerException::LoggerException(const LoggerException& logexc) noexcept
        : msg_(logexc.msg_)
{}

LoggerException&
LoggerException::operator=(const LoggerException& logexc) noexcept
{
    if (this != &logexc) {
        msg_ = logexc.msg_;
    }

    return *this;
}

const char* LoggerException::what() const noexcept
{
    return msg_.c_str();
}

}
