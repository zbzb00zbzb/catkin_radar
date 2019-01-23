//
// Created by zxkj on 18-12-01.
//
#include "radar_state_201.h"
#include <cstdint>//??

RadarState201::RadarState201()
{
    MaxDistanceCfg = -1;
    OutputType = -1;
    RadarPower = -1;
    SendQuality = -1;
    SendExtInfo = -1;
    SensorID = -1;
    SortIndex = -1;
    MotionRxState = -1;
    RCS_Threshold = -1;
    Persistent_Error = -1;
    Interference = -1;
    Temperature_Error = -1;
    Temporary_Error = -1;
    Voltage_Error = -1;
}

void RadarState201::unPackBytes(const CAN_DataFrame& can_frame)
{
    MaxDistanceCfg = ((uint16_t)(can_frame.arryData[1] << 2) + (uint8_t)((can_frame.arryData[2]&0xc0)>>6)) * 2;//why mutl 2
    OutputType = (uint8_t)((can_frame.arryData[5]&0x0c)>>2);
    RadarPower = (uint8_t)((can_frame.arryData[4]&0x80)>>7);
    SendQuality = (uint8_t)((can_frame.arryData[5]&0x10)>>4);
    SendExtInfo = (uint8_t)((can_frame.arryData[5]&0x20) >>5);

    Persistent_Error = (uint8_t)((can_frame.arryData[2]&0x20) >>5);
    Interference = (uint8_t)((can_frame.arryData[2]&0x10) >>4);
    Temperature_Error = (uint8_t)((can_frame.arryData[2]&0x08) >>3);
    Temporary_Error = (uint8_t)((can_frame.arryData[2]&0x04) >>2);
    Voltage_Error = (uint8_t)((can_frame.arryData[2]&0x02) >>1);
    SensorID = (uint8_t)((can_frame.arryData[4]&0x07) >>0);
    SortIndex = (uint8_t)((can_frame.arryData[4]&0x70) >>4);
    MotionRxState = (uint8_t)((can_frame.arryData[5]&0xC0) >>6);
    RCS_Threshold = (uint8_t)((can_frame.arryData[7]&0x1C) >>2);


}

int RadarState201::getMaxDistanceCfg()
{
    return MaxDistanceCfg;
}
int RadarState201::getOutputType()
{
    return OutputType;
}
int RadarState201::getRadarPower()
{
    return RadarPower;
}
int RadarState201::getSendQuality()
{
    return SendQuality;
}
int RadarState201::getSendExtInfo()
{
    return SendExtInfo;
}

int RadarState201::getErrorState()
{
    return ((Persistent_Error << 4) + (Interference << 3) + (Temperature_Error << 2) + (Temporary_Error << 1) + Voltage_Error);
}
int RadarState201::getSensorID()
{
    return SensorID;
}
int RadarState201::getSortIndex()
{
    return SortIndex;
}
int RadarState201::getMotionRxState()
{
    return MotionRxState;
}
int RadarState201::getRCS_Threshold()
{
    return RCS_Threshold;
}
