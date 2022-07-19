#ifndef CMEG_CMEG_HPP
#define CMEG_CMEG_HPP

#include "net-protocol.pb.h"

#include <vector>
#include <string>

class CMeg
{
public:
    CMeg();
    CMeg(std::string address);
    CMeg(std::vector<std::string> addresses);

    ~CMeg();
    
    bool connect(std::string address);
    bool connect(std::vector<std::string> addresses);
    bool connected();

    bool disconnect();

    std::vector<std::string> ipList();

    void resetSensors();
    bool resetSensorsBlocking();

    void coarseZero();
    bool coarseZeroBlocking();

    void fineZero();
    bool fineZeroBlocking();

    void start();
    void stop();

private:
    bool connect();

    void *(_callback)();
    std::vector<std::string> _ipList;
};

#endif