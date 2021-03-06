#include <fstream>
#include <iostream>
#include <string>
#include <boost/test/unit_test.hpp>

#include "Processor.h"

namespace fdr { namespace test {

typedef boost::multiprecision::int1024_t IntType;

BOOST_AUTO_TEST_CASE(TestProcessorInFileOutCout)
{
    std::ifstream infile("fdr_test_input.txt");
    if (!infile)
        throw std::runtime_error("Error opening file: fdr_test_input.txt");
    fdr::Processor processor(infile, std::cout);
    processor.Process();

    // TODO do some check

}

BOOST_AUTO_TEST_CASE(TestProcessorInFileOutFile)
{
    {
        std::ifstream infile("fdr_test_input.txt");
        if (!infile)
            throw std::runtime_error("Error opening file: fdr_test_input.txt");
        std::ofstream outfile("TestProcessorInFileOutFile.txt");
        if (!outfile)
            throw std::runtime_error("Error opening file: TestProcessorInFileOutFile.txt");
        fdr::Processor processor(infile, outfile);
        processor.Process();
    }

    std::ifstream resultfile("TestProcessorInFileOutFile.txt");
    if (!resultfile)
        throw std::runtime_error("Error opening result file: TestProcessorInFileOutFile.txt");
    std::string strResultFile{ std::istreambuf_iterator<char>(resultfile), std::istreambuf_iterator<char>() };

    std::ifstream expectedfile("ExpectedTestProcessorInFileOutFile.txt");
    if (!expectedfile)
        throw std::runtime_error("Error opening expected file: ExpectedTestProcessorInFileOutFile.txt");
    std::string strExpectedFile{ std::istreambuf_iterator<char>(expectedfile), std::istreambuf_iterator<char>() };
    
    BOOST_TEST(strResultFile == strExpectedFile);

}


} }  // end namespaces 
