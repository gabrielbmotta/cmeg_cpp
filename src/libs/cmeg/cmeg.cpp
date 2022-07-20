#include "cmeg.hpp"

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

void CMeg::resetSensors()
{
    
}

//==============================================================================

bool CMeg::resetSensorsBlocking()
{
    return false;
}

//==============================================================================

void CMeg::setResetTimeout(int msec)
{
    _resetTiemout = msec;
}

//==============================================================================

void CMeg::coarseZero()
{

}

//==============================================================================

bool CMeg::coarseZeroBlocking()
{
    return false;

}

//==============================================================================

void CMeg::setCoarseZeroTimeout(int msec)
{
    _coarseZeroTimeout = msec;
}

//==============================================================================

void CMeg::fineZero()
{

}

//==============================================================================

bool CMeg::fineZeroBlocking()
{
    return false;
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
