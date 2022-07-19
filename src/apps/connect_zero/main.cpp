#include <cmeg.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

#define TRY(FUNC, INIT_TEXT, SUCCESS_TEXT, FAILURE_TEXT) std::cout << INIT_TEXT;\
    if (!FUNC) { \
        std::cout << "\r" << FAILURE_TEXT; \
        std::cout.flush(); \
        return 1; \
    } else { \
        std::cout <<  "\r" << SUCCESS_TEXT; \
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

    std::cout << "Connecting to chassis...";
    if (!cmeg.connect(ips)) {
        std::cout << "\rUnable to connect.            \n";
        std::cout.flush();
        return 1;
    } else {
        std::cout << "\rConnected.                \n";
        std::cout.flush();
    }

    std::cout << "Restarting sensors...         ";
    if (!cmeg.resetSensorsBlocking()) {
        std::cout << "\rUnable to restart sensors.            \n";
        std::cout.flush();
        return 1;
    } else {
        std::cout << "\rSensors restarted.                \n";
        std::cout.flush();
    }

    std::cout << "Coarse zeroing sensors...         ";
    if (!cmeg.resetSensorsBlocking()) {
        std::cout << "\rCoarse zeroing failed.              \n";
        std::cout.flush();
        return 1;
    } else {
        std::cout << "\rCoarse zeroing completed               \n";
        std::cout.flush();
    }

    std::cout << "Fine zeroing sensors...         ";
    if (!cmeg.resetSensorsBlocking()) {
        std::cout << "\rFine zeroing failed.              \n";
        std::cout.flush();
        return 1;
    } else {
        std::cout << "\rFine zeroing completed               \n";
        std::cout.flush();
    }

    // 
    // std::this_thread::sleep_for(std::chrono::milliseconds(200));



    return 0;
}