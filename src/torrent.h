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

#ifndef TORRENTENTITY_H_
#define TORRENTENTITY_H_

#include <string>
#include <memory>

#include <libtorrent/session.hpp>

#include "tcexception.h"

namespace tclient
{

using namespace libtorrent;

class TorrentEntity {
public:
    TorrentEntity(const std::string& file_name,
                  const std::string& save_path) throw (TCException);

    add_torrent_params params() const;
    const std::string& file_name() const;
    const std::string& save_path() const;

private:
    std::string file_name_;
    std::string save_path_;
    std::unique_ptr<add_torrent_params> tparams_ptr_;
};

}

#endif // TORRENTENTITY_H_
