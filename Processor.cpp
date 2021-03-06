#include "Processor.h"
#include <thread>
#include "TimerThread.h"

namespace fdr {

SharedData gSharedData;

void Processor::ProcessInputtedNumber(const IntType& num)
{
    {
        std::unique_lock<std::mutex> lock(gSharedData.mMutex);
        ++gSharedData.mDataTable[num];
    }

    if (mFibonacciStore.Contains(num))
        mOutputStream << "FIB!" << std::endl;
}

void Processor::ProcessN()
{
    bool wasRunning = ProcessP();    

    {
        IntType num = mInputter.GetInput<IntType>("Please enter the new number:", [](const IntType&) {return true; });
        ProcessInputtedNumber(num);
    }

    if (wasRunning)
        ProcessR();
}

bool Processor::ProcessP()
{
    bool wasRunning;
    
    {
        std::unique_lock<std::mutex> lock(gSharedData.mMutex);
        wasRunning = gSharedData.mIsRunning;
        if (wasRunning)
        {
            gSharedData.mIsRunning = false;
            gSharedData.mCondVar.notify_one();
        }
    }

    return wasRunning;
}

void Processor::ProcessQ()
{
    std::unique_lock<std::mutex> lock(gSharedData.mMutex);
    gSharedData.mExitRequested = true;
    gSharedData.mCondVar.notify_one();
}

void Processor::ProcessR()
{    
    std::unique_lock<std::mutex> lock(gSharedData.mMutex);
    if (!gSharedData.mIsRunning)
    {
        gSharedData.mIsRunning = true;
        gSharedData.mCondVar.notify_one();
    }
}


void Processor::Process()
{    
    int outputPeriod = mInputter.GetInput<int>("Please enter output period:", [](const int& num) {return (num > 0); });
    IntType firstNum = mInputter.GetInput<IntType>("Please enter the first number:", [](const IntType&) {return true; });
    ProcessInputtedNumber(firstNum);

    auto commandFilter = [](const char& command)
    {
        return (command == 'N' || command == 'Q' || command == 'P' || command == 'R');
    };

    TimerThread timerThreadObj(outputPeriod, gSharedData, mOutputStream);
    std::thread timerThread(timerThreadObj);

    while (true)
    {
        char command = mInputter.GetInput<char>(std::string(), commandFilter);
        switch (command)
        {
        case 'P':
            ProcessP();
            mOutputStream << "Timer is paused." << std::endl;        
            break;
        case 'N':
            ProcessN();
            break;
        case 'R':
            ProcessR();
            mOutputStream << "Timer is running." << std::endl;
            break;
        case 'Q':
            ProcessQ();
            timerThread.join();
            mOutputStream << "See you next time!" << std::endl;
            return;
        }
    }
}

} // namespaces
