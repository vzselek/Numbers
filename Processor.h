#pragma once

#include <istream>
#include <ostream>
#include "FibonacciStore.h"
#include "Inputter.h"
#include "SharedData.h"

namespace fdr {

typedef FibonacciStore<IntType, 1000u> FibonacciStoreN;

class Processor
{
public:
    Processor(std::istream& inStream, std::ostream& outStream)
        : mInputStream(inStream), mOutputStream(outStream), mInputter(inStream, outStream)
    {}
    void Process();

private:

    void ProcessInputtedNumber(const IntType& num);
    void ProcessN();
    bool ProcessP();    
    void ProcessQ();
    void ProcessR();

    std::istream& mInputStream;
    std::ostream& mOutputStream;

    FibonacciStoreN mFibonacciStore;
    Inputter mInputter;
};

} // namespaces
