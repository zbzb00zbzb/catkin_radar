//
// Created by zxkj on 18-12-01.
//

#ifndef CONTI_RADAR_OBJECT_QUALITY_INFO_60C_H
#define CONTI_RADAR_OBJECT_QUALITY_INFO_60C_H

#include "ICANCmd.h"

struct QualityInfo
{
    int object_id_;
    int object_dist_long_rms_;
    int object_vrel_long_rms_;
    int object_dist_lat_rms_;
    int object_vrel_lat_rms_;
    int object_arel_long_rms_;
    int object_arel_lat_rms_;
    int object_orientation_rms_;
    int object_meas_state_;
    int object_prob_of_exist_;
};


class ObjectQualityInfo60C
{
private:
    int object_id_;
    int object_dist_long_rms_;
    int object_vrel_long_rms_;
    int object_dist_lat_rms_;
    int object_vrel_lat_rms_;
    int object_arel_long_rms_;
    int object_arel_lat_rms_;
    int object_orientation_rms_;
    int object_meas_state_;
    int object_prob_of_exist_;

public:
    ObjectQualityInfo60C();
    void unPackBytes(const CAN_DataFrame& can_frame);

    int getObjectId();
    int getObjectDistLongRms();
    int getObjectVrelLongRms();
    int getObjectDistLatRms();
    int getObjectVrelLatRms();
    int getObjectArelLongRms();
    int getObjectArelLatRms();
    int getOrientationRms();
    int getObjectMeasState();
    int getObjectProbOfExist();

    QualityInfo getQualityInfo();
};

/**
 * //    single value for rms
 *--------------------------------------------------
 *| parameter |      values for        |  value for
 *            |    orientation [deg]   | dist[m], vrel[m/s], arel[m/s²]
 *|------------------------------------------------------
 *|  0x0
 *|  0x1
 *|  0x2
 *|  0x3
 *|  0x4
 *|  0x5
 *|  0x6
 *|  0x7
 *|  0x8
 *|  0x9
 *|
 *|
 * ***/




#endif //CONTI_RADAR_OBJECT_QUALITY_INFO_60C_H
