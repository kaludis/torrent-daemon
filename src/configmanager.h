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

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include <string>
#include <map>
#include <memory>

#include "tcexception.h"

namespace tclient
{

static const char*
config_name = ".torrent_daemon.cfg";

static const char*
global_config_path = "/etc/torrent_daemon";

class ConfigManager {
public:

    typedef std::unique_ptr<ConfigManager> config_manager_t;
    typedef std::map<std::string, std::string> config_map_t;
    typedef std::pair<std::string, std::string> config_pair_t;

    static ConfigManager* instance();
    const std::string& config_path() const;
    void reload_config();
    const config_map_t& config_map() const;

protected:
    ConfigManager() throw (TCException);

private:
    void check_config_file();
    bool load_config();

private:
    std::string config_file_;
    config_map_t config_map_;
    static config_manager_t instance_;
};

}

#endif // CONFIGMANAGER_H_
