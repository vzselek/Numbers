#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "FibonacciStore.h"

namespace fdr { namespace test {

typedef boost::multiprecision::int1024_t IntType;

BOOST_AUTO_TEST_CASE(TestNumbers)
{
    FibonacciStore<IntType, 1000u> fibonacciStore;

    BOOST_TEST(fibonacciStore.Contains(3));
    BOOST_TEST(fibonacciStore.Contains(5));
    BOOST_TEST(!fibonacciStore.Contains(6));
    BOOST_TEST(fibonacciStore.Contains(IntType("137347080577163115432025771710279131845700275212767467264610201")));
    BOOST_TEST(!fibonacciStore.Contains(IntType("1373470805771631154320257717102791318457002752127674672646102012")));
}

} }  // end namespaces 
