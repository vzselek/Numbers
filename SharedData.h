#pragma once
#include <condition_variable>
#include <mutex>
#include <unordered_map>
#include <boost/multiprecision/cpp_int.hpp>

namespace fdr {

typedef boost::multiprecision::int1024_t IntType;
//typedef int IntType;

typedef std::unordered_map<IntType, size_t> DataTable;

struct SharedData
{
    bool mExitRequested = false;
    bool mIsRunning = true;
    DataTable mDataTable;
    mutable std::mutex mMutex;
    std::condition_variable mCondVar;
};

} // namespaces
