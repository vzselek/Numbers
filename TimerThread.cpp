#include "TimerThread.h"
#include <chrono>

namespace fdr {

TimerThread::TimerThread(int outputSeconds, SharedData& sharedData, std::ostream& outStream)
    : mOutputSeconds(outputSeconds), mSharedData(sharedData), mOutStream(outStream)
{
}

void TimerThread::operator()()
{
    std::chrono::seconds seconds(mOutputSeconds);    
 
    while (true)
    {
        auto end = std::chrono::steady_clock::now() + std::chrono::seconds(mOutputSeconds);
        auto pred = [&end]() { return (std::chrono::steady_clock::now() >= end); };
        
        // This may not be the perfect solution as when spuriously awaken before time then it does not reduce the ammount of time to sleep again.
        // Better way to use wait_until, without predicate and check time lapsed and reduce remaining time. I'm just too tired now to dig more into chrono documentation.
        
        std::vector<std::pair<IntType, size_t>> copiedData;
        bool isRunning = false;
        
        {
            std::unique_lock<std::mutex> lock(mSharedData.mMutex);
            mSharedData.mCondVar.wait_for(lock, seconds, pred);
            if (mSharedData.mExitRequested)
                break;
            
            if (mSharedData.mIsRunning)
            {
                isRunning = true;
                CopyData(copiedData);
            }
        }

        if (isRunning)
            PrintDataTable(copiedData);
    }
    
    std::vector<std::pair<IntType, size_t>> copiedEndData;
    CopyData(copiedEndData);  // safe to call here without lock
    PrintDataTable(copiedEndData);
}

void TimerThread::CopyData(std::vector<std::pair<IntType, size_t>>& outCopiedData) const
{
    outCopiedData.reserve(mSharedData.mDataTable.size());
    std::copy(mSharedData.mDataTable.cbegin(), mSharedData.mDataTable.cend(), std::back_inserter(outCopiedData));    
}

void TimerThread::PrintDataTable(std::vector<std::pair<IntType, size_t>>& dataCopy) const
{
    auto comparer = [](const std::pair<IntType, size_t>& one, const std::pair<IntType, size_t>& two)
    {
        return one.second != two.second ? one.second > two.second : one.first < two.first;
    };

    std::sort(dataCopy.begin(), dataCopy.end(), comparer);
    bool first = true;
    for (const auto& p : dataCopy)
    {
        if (not first)
            mOutStream << ", ";
        else
            first = false;
        mOutStream << p.first << ":" << p.second;
    }
    mOutStream << std::endl;
}

} // namespaces
