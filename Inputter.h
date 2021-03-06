#pragma once
#include <istream>
#include <ostream>
#include <string>

namespace fdr {

class Inputter
{
public:
    Inputter(std::istream& inputStream, std::ostream& outputStream)
        : mInputStream(inputStream), mOutputStream(outputStream)
    {}

    template <typename T, typename F>
    T GetInput(const std::string& message, F filter)
    {
        T ret;        
        if (!message.empty())
            mOutputStream << message << std::endl;

        while (true)
        {
            if (mInputStream >> ret)
            {
                bool ok = true;
                ok = filter(ret);
                if (ok)
                    break;
            }            
            mInputStream.clear();
            mInputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!message.empty())
                mOutputStream << message << std::endl;
        }

        return ret;
    }    

private:
    std::istream& mInputStream;
    std::ostream& mOutputStream;
};

} // namespaces
