//
// Created by zxkj on 18-8-5.
//

#include "object_general_info_60b.h"
#include <cstdint>
#include <iostream>

ObjectGeneralInfo60B::ObjectGeneralInfo60B()
{
    object_id_ = -1;
    object_dist_long_ = -1;
    object_dist_lat_ = -1;
    object_vre_long_ = -1;
    object_vre_lat_ = -1;
    object_dyn_prop_ = -1;
    object_rcs_ = -1;    
}

void ObjectGeneralInfo60B::unPackBytes(const CAN_DataFrame& can_frame)
{
    object_id_ = (uint8_t)(can_frame.arryData[0]);
    object_dist_long_ = ((uint16_t)(can_frame.arryData[1]<<5) + (uint8_t)((can_frame.arryData[2] & 0xf8)>>3)) * 0.2  - 500;
    object_dist_lat_ = ((uint16_t)((can_frame.arryData[2] & 0x07) << 8) + (uint8_t)(can_frame.arryData[3])) * 0.2 - 204.6;
    object_vre_long_ = ((uint16_t)(can_frame.arryData[4]<<2) + (uint8_t)((can_frame.arryData[5] & 0xc0)>>6)) * 0.25 - 128;
    object_vre_lat_ = ((uint16_t)((can_frame.arryData[5] & 0x3f) << 3) + (uint8_t)((can_frame.arryData[6]&0xe0)>>5)) * 0.25 - 64;
    object_dyn_prop_ = (uint8_t)(can_frame.arryData[6] & 0x07);
    object_rcs_ = (uint8_t)(can_frame.arryData[7]) * 0.5 -64.0;
}

int ObjectGeneralInfo60B::getObjectID()
{
    return object_id_;
}
float ObjectGeneralInfo60B::getObjectDistLong()
{
    return object_dist_long_;
}
float ObjectGeneralInfo60B::getObjectDistLat()
{
    return object_dist_lat_;
}
float ObjectGeneralInfo60B::getObjectVreLong()
{
    return object_vre_long_;
}
float ObjectGeneralInfo60B::getObjectVreLat()
{
    return object_vre_lat_;
}
int ObjectGeneralInfo60B::getObjectDynProp()
{
    return object_dyn_prop_;
}
float ObjectGeneralInfo60B::getObjectRcs()
{
    return object_rcs_;
}
GeneralInfo ObjectGeneralInfo60B::getGeneralInfo()
{
    GeneralInfo general_info_;
    general_info_.object_id_ = object_id_;
    general_info_.object_dist_long_ = object_dist_long_;
    general_info_.object_dist_lat_ = object_dist_lat_;
    general_info_.object_vre_lat_ = object_vre_lat_;
    general_info_.object_vre_long_ = object_vre_long_;
    general_info_.object_dyn_prop_ = object_dyn_prop_;
    general_info_.object_rcs_ = object_rcs_;
    return general_info_;
}
