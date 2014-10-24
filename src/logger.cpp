/*
  Copyright (c) 2014 Alexander Bezsilko <demonsboots@gmail.com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
 */

#include <cassert>

#include "logger.h"

namespace logger
{

Logger* Logger::instance()
{
    if (!instance_) {
        instance_.reset(new Logger());
    }

    return instance_.get();
}

Logger::Logger()
        : severity_(Severity::INFO),
          log_file_(std::string()),
          time_format_(TimeFormat::LOCAL),
          stream_(new LogStream_t),
          mutex_(new std::mutex())
{}

void Logger::set_severity_level(Logger::Severity level)
{
    severity_ = level;
}

void Logger::set_log_file(std::string& logfile)
{
    log_file_ = logfile;
}

void Logger::set_log_file(const char* logfile)
{
    log_file_ = logfile;
    stream_.reset(new LogStream_t());
}

void Logger::log(Severity level /*=Severity::NONE*/,
                 const char* msg /*=nullptr*/) throw (LoggerException)
{
    assert(msg != nullptr);

    if (level == Severity::NONE) {
        level = severity_;
    }
    
    std::time_t event_time = std::time(nullptr);        
    /*
    LogStream_t log_stream(log_file_,
                           std::ios_base::out | std::ios_base::app);
    */

    mutex_->lock();

    stream_->open(log_file_, std::ios_base::out | std::ios_base::app);
    check_stream(stream_);
    *stream_ << time_str(&event_time)
               << severity_encode(level) << msg << std::endl;
    stream_->close();

    mutex_->unlock();
    //log_stream.close();
}

void Logger::check_stream(const LogStreamPtr_t& log_stream)
        throw (LoggerException)
{
    if (!*log_stream) {
        throw LoggerException("Can't open log file");
    }
}

std::string Logger::severity_encode(Severity level)
{
    switch (level) {
        case Severity::INFO: {
            return std::string(" *** INFO *** : ");
            break;
        }

        case Severity::FATAL: {
            return std::string(" *** FATAL *** : ");
            break;
        }

        case Severity::ERROR: {
            return std::string(" *** ERROR *** : ");
            break;
        }

        case Severity::WARNING: {
            return std::string(" *** WARNING *** : ");
            break;
        }

        default: {
            return std::string();
        }
    }
}

void Logger::set_time_format(TimeFormat timeformat)
{
    time_format_ = timeformat;
}

std::string Logger::time_str(const std::time_t* time)
{
    char time_buf[100];

    switch (time_format_) {
        case TimeFormat::UTC: {
            std::strftime(time_buf, sizeof(time_buf), "%c %Z",
                          std::gmtime(time));
            break;
        }

        case TimeFormat::LOCAL: {
            std::strftime(time_buf, sizeof(time_buf), "%c %Z",
                          std::localtime(time));
            break;
        }
    }

    std::string ret_time;
    ret_time.append(1, '[')
            .append(time_buf)
            .append(1, ']');

    return ret_time;
}

Logger::LoggerPtr_t Logger::instance_(nullptr);

}



















