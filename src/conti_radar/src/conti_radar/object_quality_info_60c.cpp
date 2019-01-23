//
// Created by zxkj on 18-12-01.
//

#include "object_quality_info_60c.h"
#include <cstdint>
#include <iostream>

ObjectQualityInfo60C::ObjectQualityInfo60C()
{
    object_id_ = -1;
    object_dist_long_rms_ = -1;
    object_vrel_long_rms_ = -1;
    object_dist_lat_rms_ = -1;
    object_vrel_lat_rms_ = -1;
    object_arel_long_rms_ = -1;
    object_arel_lat_rms_ = -1;
    object_orientation_rms_ = -1;
    object_meas_state_ = -1;
    object_prob_of_exist_ = -1;
}

void ObjectQualityInfo60C::unPackBytes(const CAN_DataFrame &can_frame)
{
    object_id_ = (uint8_t)(can_frame.arryData[0]);
    object_dist_long_rms_ = (uint8_t)((can_frame.arryData[1] & 0xf8) >> 3);
    object_dist_lat_rms_ = (uint8_t)((can_frame.arryData[1] & 0x07)<<2 + (can_frame.arryData[2] & 0xc0) >>6);
    object_vrel_long_rms_ = (uint8_t)((can_frame.arryData[2] & 0x3e) >> 1);
    object_vrel_lat_rms_ = (uint8_t)((can_frame.arryData[2] & 0x01)<< 4 + (can_frame.arryData[3] &0xf0) >> 4);
    object_arel_long_rms_ = (uint8_t)((can_frame.arryData[3]&0x0f) + (can_frame.arryData[4]&0x80)>>7);
    object_arel_lat_rms_ = (uint8_t)((can_frame.arryData[4]&0x7c)>>2);
    object_orientation_rms_ = (uint8_t)((can_frame.arryData[4]&0x03)<<3 + (can_frame.arryData[5]&0xe0)>>5);
    object_prob_of_exist_ = (uint8_t)((can_frame.arryData[6]&0xe0)>>5);
    object_meas_state_ = (uint8_t)((can_frame.arryData[6]&0x1c)>>2);
}

int ObjectQualityInfo60C::getObjectId() {
    return object_id_;
}

int ObjectQualityInfo60C::getObjectDistLongRms() {
    return object_dist_long_rms_;
}

int ObjectQualityInfo60C::getObjectDistLatRms() {
    return object_dist_lat_rms_;
}

int ObjectQualityInfo60C::getObjectVrelLongRms() {
    return object_vrel_long_rms_;
}

int ObjectQualityInfo60C::getObjectVrelLatRms() {
    return object_vrel_lat_rms_;
}

int ObjectQualityInfo60C::getObjectArelLongRms() {
    return object_arel_lat_rms_;
}

int ObjectQualityInfo60C::getObjectArelLatRms() {
    return object_arel_lat_rms_;
}

int ObjectQualityInfo60C::getOrientationRms() {
    return object_orientation_rms_;
}
int ObjectQualityInfo60C::getObjectProbOfExist() {
    return object_prob_of_exist_;
}
int ObjectQualityInfo60C::getObjectMeasState() {
    return object_meas_state_;
}

QualityInfo ObjectQualityInfo60C::getQualityInfo()
{
    QualityInfo quality_info;
    quality_info.object_id_ = object_id_;
    quality_info.object_dist_long_rms_ = object_dist_long_rms_;
    quality_info.object_dist_lat_rms_ = object_dist_lat_rms_;
    quality_info.object_vrel_long_rms_ = object_vrel_long_rms_;
    quality_info.object_vrel_lat_rms_ = object_vrel_lat_rms_;
    quality_info.object_arel_long_rms_ = object_arel_long_rms_;
    quality_info.object_arel_lat_rms_ = object_arel_lat_rms_;
    quality_info.object_orientation_rms_ = object_orientation_rms_;
    quality_info.object_prob_of_exist_ = object_prob_of_exist_;
    quality_info.object_meas_state_ = object_meas_state_;
    return quality_info;
}

