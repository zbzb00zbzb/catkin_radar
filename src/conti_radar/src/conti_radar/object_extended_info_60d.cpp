//
// Created by zxkj on 18-12-01.
//

#include "object_extended_info_60d.h"
#include <cstdint>
#include <iostream>

ObjectExtendedInfo60D::ObjectExtendedInfo60D()
{
    object_id_ = -1;
    object_arel_long_ = -1;
    object_class_ = -1;
    object_arel_lat_ = -1;
    object_orientation_angel_ = -1;
    object_length_ = -1;
    object_width_ = -1;
}

void ObjectExtendedInfo60D::unPackBytes(const CAN_DataFrame &can_frame)
{
    object_id_ = (uint8_t)(can_frame.arryData[0] & 0xff);
    object_arel_long_ = ((uint16_t)(can_frame.arryData[1] << 3) + (uint8_t)((can_frame.arryData[2]&0xe0)>>5)) * 0.01 -10;
    object_arel_lat_ = ((uint16_t)((can_frame.arryData[2]&0x1f)<<4) + (uint8_t)((can_frame.arryData[3]&0xf0)>>4)) * 0.01 - 2.5;
    object_class_ = (uint8_t)(can_frame.arryData[3] & 0x0f);
    object_orientation_angel_ = ((uint16_t)(can_frame.arryData[4]<<2) + (uint8_t)((can_frame.arryData[5]&0xc0)>>6))*0.4-180;
    object_length_ = ((uint8_t)(can_frame.arryData[6])) * 0.2;
    object_width_ = ((uint8_t)(can_frame.arryData[7])) * 0.2;
}

int ObjectExtendedInfo60D::getObjectId()
{
    return object_id_;
}

float ObjectExtendedInfo60D::getObjectArelLong()
{
    return object_arel_long_;
}

int ObjectExtendedInfo60D::getObjectClass()
{
    return object_class_;
}

float ObjectExtendedInfo60D::getObjectArelLat()
{
    return object_arel_lat_;
}

float ObjectExtendedInfo60D::getObjectOrientationAngel()
{
    return object_orientation_angel_;
}

float ObjectExtendedInfo60D::getObjectLength()
{
    return object_length_;
}

float ObjectExtendedInfo60D::getObjectWidth()
{
    return object_width_;
}

ExtendedInfo ObjectExtendedInfo60D::getExtendedInfo()
{
    ExtendedInfo extended_info;
    extended_info.object_id_ = object_id_;
    extended_info.object_arel_long_ = object_arel_long_;
    extended_info.object_arel_lat_ = object_arel_lat_;
    extended_info.object_class_ = object_class_;
    extended_info.object_orientation_angel_ = object_orientation_angel_;
    extended_info.object_length_ = object_length_;
    extended_info.object_width_ = object_width_;
    return extended_info;
}


