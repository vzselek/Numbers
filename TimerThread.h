#pragma once
#include <ostream>
#include <utility>
#include <vector>
#include "SharedData.h"

namespace fdr {

class TimerThread
{
public:
    TimerThread(int outputSeconds, SharedData& sharedData, std::ostream& outStream);    

    void operator()();

private:
    // this should be called inside locking block
    void CopyData(std::vector<std::pair<IntType, size_t>>& outCopiedData) const;    
    
    void PrintDataTable(std::vector<std::pair<IntType, size_t>>& dataCopy) const;

    int mOutputSeconds;
    SharedData& mSharedData;
    std::ostream& mOutStream;
};

} // namespaces
