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

/*
 * Logger singleton thread-safe implementation
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <memory>
#include <string>
#include <fstream>
#include <ctime>
#include <mutex>

#include "logexcept.h"

namespace logger
{

class Logger {
public:
    typedef std::unique_ptr<Logger> LoggerPtr_t;
    typedef std::ofstream LogStream_t;
    typedef std::unique_ptr<LogStream_t> LogStreamPtr_t;
    typedef std::unique_ptr<std::mutex> MutexPtr_t;
    
    enum Severity {
        NONE = -1,        
        FATAL,
        ERROR,
        WARNING,
        INFO
    };

    enum TimeFormat {
        UTC,
        LOCAL
    };

    static Logger* instance();

    void set_severity_level(Severity level = Severity::INFO);
    void set_log_file(std::string& logfile);
    void set_log_file(const char* logfile);    
    void log(Severity level = Severity::NONE,
             const char* msg = nullptr) throw (LoggerException);
    void set_time_format(TimeFormat timeformat);

protected:
    Logger();

private:
    void check_stream(const LogStreamPtr_t& log_stream) throw (LoggerException);
    std::string severity_encode(Severity level);
    std::string time_str(const std::time_t* time);

private:
    static LoggerPtr_t instance_;
    Severity severity_;
    std::string log_file_;
    TimeFormat time_format_;
    LogStreamPtr_t stream_;
    MutexPtr_t mutex_;
};

}

#endif // LOGGER_H_
