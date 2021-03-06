#pragma once

#include <unordered_set>

namespace fdr {

template <typename T, size_t N> class FibonacciStore
{
public:
    FibonacciStore()
    {
        T f1 = 0;
        T f2 = 1;
        mPrecalculated.reserve(N);        
        mPrecalculated.insert(f1);               
        mPrecalculated.insert(f2);

        for (size_t i = 3; i <= N; ++i)
        {
            auto fi = f1 + f2;
            mPrecalculated.insert(fi);
            f1 = f2;
            f2 = fi;
        }
    }

    bool Contains(const T& num) const
    {
        return (mPrecalculated.find(num) != mPrecalculated.end());
    }

private:
    std::unordered_set<T> mPrecalculated;
};

} // namespaces
