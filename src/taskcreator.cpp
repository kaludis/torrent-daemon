#include <cstdlib>
#include <algorithm>
#include <iterator>

#include <boost/filesystem.hpp>

#include "taskcreator.h"

namespace tclient
{

TaskCreator::TaskCreator(const std::string& taskpath,
                         const std::string& savepath)
        : task_path_(taskpath),
          save_path_(savepath)
{
    normalize_paths();
}

const std::string& TaskCreator::task_path() const
{
    return task_path_;
}

const std::string& TaskCreator::save_path() const
{
    return save_path_;
}

void TaskCreator::set_paths(const std::string& taskpath,
                                const std::string& savepath)
{
    task_path_ = taskpath;
    save_path_ = savepath;
    normalize_paths();
}

TaskCreator::Tasks_t TaskCreator::create_tasks() throw (TCException)
{
    using namespace boost::filesystem;

    path src_path(task_path_);
    std::vector<path> paths_in_dir;

    try {
        if (exists(src_path)) {
            if (is_directory(src_path)) {
                directory_iterator end;
                for (directory_iterator iter(src_path); iter != end; ++iter) {
                    if (!is_directory(*iter)) {
                        paths_in_dir.push_back(iter->path());
                    }
                }
            }
        }
    } catch (const filesystem_error& ex) {
        throw TCException("Error occurred with .torrent file rading\n" +
                          std::string(ex.what()));
    }

    TaskCreator::Tasks_t tasks;
    for (const path& p : paths_in_dir) {
        tasks.push_back(TaskCreator::TorrentEntity_ptr(
            new TorrentEntity(p.string(), save_path_)));
    }

    return tasks;
}

void TaskCreator::normalize_paths()
{
    std::size_t pos;
    
    if ((pos = task_path_.find('~')) != std::string::npos) {
        std::string tmp = task_path_.substr(pos + 1, task_path_.length() - pos);
        task_path_ = std::string(std::getenv("HOME")) + tmp;
    }

    if ((pos = save_path_.find('~')) != std::string::npos) {
        std::string tmp = save_path_.substr(pos + 1, save_path_.length() - pos);
        save_path_ = std::string(std::getenv("HOME")) + tmp;
    }    
}

}
