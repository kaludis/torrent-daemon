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

#ifndef SESSION_H_
#define SESSION_H_

#include <memory>
#include <utility>
#include <cstdint>
#include <vector>

#include <libtorrent/session.hpp>

#include "torrent.h"
#include "tcexception.h"

namespace tclient
{

using namespace libtorrent;

class Session {
public:

    typedef std::shared_ptr<TorrentEntity> TorrentEntity_ptr;
    typedef std::vector<TorrentEntity_ptr> Tasks_t;

    Session(uint32_t start_port, uint32_t end_port);
    ~Session();
    void start_listen() throw (TCException);
    void add_entity(const TorrentEntity& entity) throw (TCException);
    void add_entries(const Tasks_t& entries);

private:
    std::pair<uint32_t, uint32_t> port_range_;    
    std::unique_ptr<session> session_ptr_;
};

}

#endif // SESSION_H_
