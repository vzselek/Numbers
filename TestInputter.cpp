#include <fstream>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "Inputter.h"

namespace fdr { namespace test {

typedef boost::multiprecision::int1024_t IntType;

BOOST_AUTO_TEST_CASE(TestInputter)
{
    std::ifstream infile("fdr_test_input.txt");
    if (!infile)
        throw std::runtime_error("Error opening file: fdr_test_sinput.txt");

    Inputter inputter(infile, std::cout);

    std::vector<char> expectedValues = { '2', '2', 'N' };
    for (int i = 0; i < 3; ++i)
    {
        char input = inputter.GetInput<char>(std::string(), [](const char&) {return true; });

        BOOST_TEST(input == expectedValues[i]);
    }
    
}

} }  // end namespaces 
