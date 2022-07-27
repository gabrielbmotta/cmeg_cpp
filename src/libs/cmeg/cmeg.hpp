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
        SENSOR_ON,
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

    void setConnectionTimeout(int msec);
    void setPort(int port);

    bool disconnect();

    std::vector<std::string> ipList();

    bool restartSensors();
    void setRestartTimeout(int msec);

    bool coarseZeroSensors();
    void setCoarseZeroTimeout(int msec);

    bool fineZeroSensors();
    void setFineZeroTimeout(int msec);

    void start();
    void stop();

private:
    bool connect();

    void checkAvailableSensors();

    void *(_callback)();
    std::vector<std::string> _ipList;
    int _port;

    std::vector<Sensor> _sensorList;

    int _connectionTimeout;
    int _resetTiemout;
    int _coarseZeroTimeout;
    int _fineZeroTimeout;
};

#endif