//
// Created by zxkj on 18-12-01.
//

#ifndef CONTI_RADAR_RADAR_STATE_201_H
#define CONTI_RADAR_RADAR_STATE_201_H

#include "ICANCmd.h"

struct RadarState
{
    int NVMReadStatus;
    int NVMWriteStatus;
    int MaxDistanceCfg;
    int Persistent_Error;
    int Interference;
    int Temperature_Error;
    int Temporary_Error;
    int Voltage_Error;
    int SensorID;
    int SortIndex;
    int RadarPower;
    int OutputType;
    int SendQuality;
    int SendExtInfo;
    int MotionRxState;
    int RCS_Threshold;
};

class RadarState201
{
private:
    int NVMReadStatus;
    int NVMWriteStatus;
    int MaxDistanceCfg;
    int Persistent_Error;
    int Interference;
    int Temperature_Error;
    int Temporary_Error;
    int Voltage_Error;
    int SensorID;
    int SortIndex;
    int RadarPower;
    int OutputType;
    int SendQuality;
    int SendExtInfo;
    int MotionRxState;
    int RCS_Threshold;

public:
    RadarState201();
    void unPackBytes(const CAN_DataFrame& can_frame);

    int getMaxDistanceCfg();
    int getOutputType();
    int getRadarPower();
    int getSendQuality();
    int getSendExtInfo();
    int getErrorState();
    int getSensorID();
    int getSortIndex();
    int getMotionRxState();
    int getRCS_Threshold();
};


#endif //CONTI_RADAR_RADAR_STATE_201_H
