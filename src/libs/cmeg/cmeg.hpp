#ifndef CMEG_CMEG_HPP
#define CMEG_CMEG_HPP

#include "net-protocol.pb.h"

#include <vector>
#include <string>


class CMeg
{
public:
    struct Sensor
    {
        enum State{
        SENSOR_OFF,
        SENSOR_COARSE_ZEROING,
        SENSOR_COARSE_ZEROED,
        SENSOR_FINE_ZEROING,
        SENSOR_FINE_ZEROED
        };
        int chassis;
        int id;
        State state;
    };

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
    void setResetTimeout(int msec);

    void coarseZero();
    bool coarseZeroBlocking();
    void setCoarseZeroTimeout(int msec);

    void fineZero();
    bool fineZeroBlocking();
    void setFineZeroTimeout(int msec);

    void start();
    void stop();

private:
    bool connect();

    void checkAvailableSensors();

    void *(_callback)();
    std::vector<std::string> _ipList;
    std::vector<Sensors> _sensorList;

    int _resetTiemout;
    int _coarseZeroTimeout;
    int _fineZeroTimeout;
};

#endif