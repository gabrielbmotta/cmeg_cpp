#ifndef CMEG_CMEG_HPP
#define CMEG_CMEG_HPP

#include <vector>
#include <string>

class CMeg
{
public:
    CMeg();
    CMeg(std::string address);
    CMeg(std::vector<std::string> addresses);
    
    bool connect(std::string address);
    bool connect(std::vector<std::string> addresses);

    void resetSensors();
    bool resetSensorsBlocking();

    void coarseZero();
    bool coarseZeroBlocking();

    void fineZero();
    bool fineZeroBlocking();

    void start();
    void stop();

    ~CMeg();
private:

};

#endif