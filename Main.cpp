#include <iostream>
#include "Processor.h"


int main(int argc, char* argv[])
{
    int ret = 0;   
        
    try
    {
        fdr::Processor processor(std::cin, std::cout);
        processor.Process();
    }
    catch (const std::exception & e)
    {
        ret = 1;
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        ret = 1;
        std::cerr << "Unknown error happened" << std::endl;
    }

    return ret;
}
