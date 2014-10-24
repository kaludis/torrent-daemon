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

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

#include "configmanager.h"
//#include "utils.h"

namespace tclient
{

ConfigManager::ConfigManager()  throw (TCException)
        : config_file_(std::string()),
          config_map_(ConfigManager::config_map_t())
{
    check_config_file();
    if (!load_config()) {
        throw TCException("Error occurred with config loading");
    }

}

ConfigManager* ConfigManager::instance()
{
    if (!instance_) {
        instance_.reset(new ConfigManager());
    }

    return instance_.get();
}

void ConfigManager::check_config_file()
{
    using namespace boost::filesystem;

    std::string local_file(std::string(std::getenv("HOME"))
                           .append("/")
                           .append(config_name));

    std::string global_file(std::string(global_config_path)
                            .append("/")
                            .append(config_name));

    if (exists(path(local_file.c_str()))) {
        config_file_ = local_file;
    } else if (exists(path(global_file.c_str()))) {
        config_file_ = global_file;
    }
}

bool ConfigManager::load_config()
{
    std::ifstream in(config_file_);

    if (!in) {
        return false;
    }

    std::string line;

    while (!in.eof() && std::getline(in, line)) {
        if (line[0] == '#') {
            continue;
        }

        std::string key;
        std::string value;

        std::size_t pos = line.find('=');
        if (pos == std::string::npos) {
            continue;
        }
        
        key = line.substr(0, pos);
        value = line.substr(pos + 1, line.length() - pos);

        config_map_.insert(config_pair_t(key, value));
    }

    if (!config_map_.size()) {
        return false;
    }

    return true;
}

void ConfigManager::reload_config()
{
    if (!load_config()) {
        throw TCException("Error occurred with config reloading");
    }    
}

const std::string& ConfigManager::config_path() const
{
    return config_file_;
}

const ConfigManager::config_map_t& ConfigManager::config_map() const
{
    return config_map_;
}

ConfigManager::config_manager_t ConfigManager::instance_(nullptr);

}
















