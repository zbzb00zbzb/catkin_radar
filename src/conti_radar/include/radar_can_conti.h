//
// Created by zxkj on 18-12-01.
//

#ifndef RADAR_CAN_CONTI_H
#define RADAR_CAN_CONTI_H

#include "radar_can.h"
#include <iostream>

#include <conti_radar/radar_state_201.h>
#include <conti_radar/object_list_status_60a.h>
#include <conti_radar/object_general_info_60b.h>
#include <conti_radar/object_quality_info_60c.h>
#include <conti_radar/object_extended_info_60d.h>

#include <conti_radar_msgs/conti_Objects.h>
#include <conti_radar_msgs/conti_Object.h>

const int OBJECT_LIST_STATUS_MID = 0x0000060A;
const int OBJECT_GENERAL_INFO_MID = 0x0000060B;
const int OBJECT_QUALITY_INFO_MID = 0x0000060C;
const int OBJECT_EXTENDED_INFO_MID = 0x0000060D;

const int OBJECT_LIST_STATUS_LEFT = 0x0000061A;
const int OBJECT_GENERAL_INFO_LEFT = 0x0000061B;
const int OBJECT_QUALITY_INFO_LEFT = 0x0000061C;
const int OBJECT_EXTENDED_INFO_LEFT = 0x0000061D;

const int OBJECT_LIST_STATUS_RIGHT = 0x0000062A;
const int OBJECT_GENERAL_INFO_RIGHT = 0x0000062B;
const int OBJECT_QUALITY_INFO_RIGHT = 0x0000062C;
const int OBJECT_EXTENDED_INFO_RIGHT = 0x0000062D;

const int RADAR_STATE_MID = 0x00000201;
const int RADAR_STATE_LEFT = 0x00000211;
const int RADAR_STATE_RIGHT = 0x00000221;


class RadarCan_Conti:public RadarCan
{
public:
    RadarCan_Conti();

    virtual bool checkInfo();
    virtual void setup();
    virtual void transformCanToInfo(std::vector<CAN_DataFrame>& can_frames, int len);

    void midMessagePub();
    void leftMessagePub();
    void rightMessagePub();


private:

    ObjectListStatus60A object_list_status_;
    ObjectGeneralInfo60B object_general_info_;
    ObjectQualityInfo60C object_quality_info_;
    ObjectExtendedInfo60D object_extended_info_;
    RadarState201 radar_state_;

    std::vector<GeneralInfo> general_info_arr_mid_;
    std::vector<QualityInfo> quality_info_arr_mid_;
    std::vector<ExtendedInfo> extended_info_arr_mid_;

    std::vector<GeneralInfo> general_info_arr_left_;
    std::vector<QualityInfo> quality_info_arr_left_;
    std::vector<ExtendedInfo> extended_info_arr_left_;

    std::vector<GeneralInfo> general_info_arr_right_;
    std::vector<QualityInfo> quality_info_arr_right_;
    std::vector<ExtendedInfo> extended_info_arr_right_;

    int object_mid_num_;
    int object_left_num_;
    int object_right_num_;

//Used to transform the sensor coordinate system to the vehicle coordinate system.
    double long_offset_mid_;
    double lat_offset_mid_;
    double angular_deviation_mid_;

    double long_offset_left_;
    double lat_offset_left_;
    double angular_deviation_left_;

    double long_offset_right_;
    double lat_offset_right_;
    double angular_deviation_right_;

};

#endif
