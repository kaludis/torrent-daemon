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
#include "session.h"

namespace tclient
{

Session::Session(uint32_t start_port, uint32_t end_port)
        : port_range_(std::make_pair(start_port, end_port)),
          session_ptr_(new session())

{

}

Session::~Session()
{}

void Session::start_listen() throw(TCException)
{
    error_code e;
    session_ptr_->listen_on(port_range_, e);
    if (e) {
        throw TCException("Error occured with session start listening:\n" +
                          e.message());
    }
}

void Session::add_entity(const TorrentEntity& entity) throw (TCException)
{
    error_code ec;    
    session_ptr_->add_torrent(entity.params(), ec);

    if (ec) {
        throw TCException("Error occurred with addition new torrent:\n" +
                          ec.message());
    }
}

void Session::add_entries(const std::vector<TorrentEntity>& entries)
{
    // TODO
    // Add all valid entries from vector to session
}

}
