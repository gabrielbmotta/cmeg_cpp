#include "cmeg.hpp"

//==============================================================================

CMeg::CMeg()
{

}

//==============================================================================

CMeg::CMeg(std::string address)
: _ipList{{address}}
{
    if(connect())
    {
        checkAvailableSensors();
    }
}

//==============================================================================

CMeg::CMeg(std::vector<std::string> addresses)
: _ipList{addresses}
{
    if(connect())
    {
        checkAvailableSensors();
    }
}

//==============================================================================

CMeg::~CMeg()
{
    disconnect();
}

//==============================================================================

bool CMeg::connect(std::string address)
{
    _ipList = {address};
    if(connect())
    {
        checkAvailableSensors();
        return true;
    }
    return false;
}

//==============================================================================

bool CMeg::connect(std::vector<std::string> addresses)
{
    _ipList = addresses;
    if(connect())
    {
        checkAvailableSensors();
        return true;
    }
    return false;
}

//==============================================================================

bool CMeg::connect()
{
    return false;
}

//==============================================================================

bool CMeg::connected()
{
    return false;
}

//==============================================================================

void CMeg::setConnectionTimeout(int msec)
{
    _connectionTimeout = msec;
}

//==============================================================================

void CMeg::setPort(int _port)
{

}

//==============================================================================

bool CMeg::disconnect()
{
    return false;
}

//==============================================================================

std::vector<std::string> CMeg::ipList()
{
    return _ipList;
}

//==============================================================================

bool CMeg::restartSensors()
{
    
}

//==============================================================================

void CMeg::setRestartTimeout(int msec)
{
    _resetTiemout = msec;
}

//==============================================================================

bool CMeg::coarseZeroSensors()
{

}

//==============================================================================

void CMeg::setCoarseZeroTimeout(int msec)
{
    _coarseZeroTimeout = msec;
}

//==============================================================================

bool CMeg::fineZeroSensors()
{

}

//==============================================================================

void CMeg::setFineZeroTimeout(int msec)
{
    _fineZeroTimeout = msec;
}

//==============================================================================

void CMeg::start()
{

}

//==============================================================================

void CMeg::stop()
{

}

//==============================================================================

void CMeg::checkAvailableSensors()
{

}
