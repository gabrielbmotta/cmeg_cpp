#include <cmeg.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

#define TRY(FUNC, INIT_TEXT, SUCCESS_TEXT, FAILURE_TEXT)    std::cout << INIT_TEXT << "                        "; \
                                                            if (!FUNC) { \
                                                                std::cout << "\r" << FAILURE_TEXT << "                        \n"; \
                                                                std::cout.flush(); \
                                                                return 1; \
                                                            } else { \
                                                                std::cout <<  "\r" << SUCCESS_TEXT << "                        \n"; \
                                                                std::cout.flush(); \
                                                            }

int main(int argc, char* argv[])
{
    std::cout << "CMEG Connect and Zero\n";
    std::cout << "Chassis ips:\n";
    
    std::vector<std::string> ips;
    for(int i = 1; i < argc; ++i){
        ips.push_back(argv[i]);
        std::cout << "[" << i << "] - " << argv[i] << "\n";
    }

    if(ips.empty())
    {
        std::cout << "No ips provided.\n";
        return 0;
    }

    CMeg cmeg;

    TRY(cmeg.connect(ips),
    "Connecting to chassis...",
    "Connected.",
    "Unable to connect.");

    TRY(cmeg.resetSensorsBlocking(),
    "Restarting sensors...",
    "Sensors restarted.",
    "Unable to restart sensors.");

    TRY(cmeg.coarseZeroBlocking(),
    "Coarse zeroing sensors...",
    "Coarse zeroing completed.",
    "Coarse zeroing failed.");

    TRY(cmeg.fineZeroBlocking(),
    "Fine zeroing sensors...",
    "Fine zeroing completed.",
    "Fine zeroing failed.");

    return 0;
}