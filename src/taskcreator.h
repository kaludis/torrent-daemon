#ifndef TASKCREATOR_H_
#define TASKCREATOR_H_

#include <string>
#include <vector>
#include <memory>

#include "torrent.h"
#include "tcexception.h"

namespace tclient
{

class TaskCreator {
public:

    typedef std::shared_ptr<TorrentEntity> TorrentEntity_ptr;
    typedef std::vector<TorrentEntity_ptr> Tasks_t;

    TaskCreator(const std::string& taskpath,
                const std::string& savepath);
    const std::string& task_path() const;
    const std::string& save_path() const;
    void set_paths(const std::string& taskpath,
                   const std::string& savepath);
    Tasks_t create_tasks() throw (TCException);

private:
    void normalize_paths();

private:
    std::string task_path_;
    std::string save_path_;
};

}

#endif // TASKCREATOR_H_
