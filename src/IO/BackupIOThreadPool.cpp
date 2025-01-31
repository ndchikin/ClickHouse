#include <IO/BackupsIOThreadPool.h>
#include "Core/Field.h"

namespace DB
{

namespace ErrorCodes
{
    extern const int LOGICAL_ERROR;
}

std::unique_ptr<ThreadPool> BackupsIOThreadPool::instance;

void BackupsIOThreadPool::initialize(size_t max_threads, size_t max_free_threads, size_t queue_size)
{
    if (instance)
    {
        throw Exception(ErrorCodes::LOGICAL_ERROR, "The BackupsIO thread pool is initialized twice");
    }

    instance = std::make_unique<ThreadPool>(max_threads, max_free_threads, queue_size, false /*shutdown_on_exception*/);
}

ThreadPool & BackupsIOThreadPool::get()
{
    if (!instance)
    {
        throw Exception(ErrorCodes::LOGICAL_ERROR, "The BackupsIO thread pool is not initialized");
    }

    return *instance;
}

}
