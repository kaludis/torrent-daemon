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

#include "torrent.h"

namespace tclient
{

TorrentEntity::TorrentEntity(const std::string& file_name,
                             const std::string& save_path) throw (TCException)
        : file_name_(file_name),
          save_path_(save_path),
          tparams_ptr_(new add_torrent_params)
{
    tparams_ptr_->save_path = save_path_;
    error_code ec;
    tparams_ptr_->ti = new torrent_info(file_name, ec);
    
    if (ec) {
        throw TCException("Error occurred with torrent params:\n" +
                          ec.message());
    }
}

add_torrent_params TorrentEntity::params() const
{
    if (tparams_ptr_) {
        return *tparams_ptr_;
    } else {
        return add_torrent_params();
    }
}

const std::string& TorrentEntity::file_name() const
{
    return file_name_;
}

const std::string& TorrentEntity::save_path() const
{
    return save_path_;
}

}
