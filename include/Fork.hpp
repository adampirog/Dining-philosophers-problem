#pragma once
#include <mutex>

class Fork
{
public:
    int forkID;
    std::mutex mutex;
};