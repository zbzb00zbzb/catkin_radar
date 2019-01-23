//
// Created by zxkj on 18-12-01.
//

#ifndef CONTI_RADAR_OBJECT_GENERAL_INFO_60B_H
#define CONTI_RADAR_OBJECT_GENERAL_INFO_60B_H

#include <vector>
#include "ICANCmd.h"

struct GeneralInfo
{
    int object_id_;
    float object_dist_long_;
    float object_dist_lat_;
    float object_vre_long_;
    float object_vre_lat_;
    int object_dyn_prop_;
    float object_rcs_;
};

class ObjectGeneralInfo60B
{
private:
    int object_id_;
    float object_dist_long_;
    float object_dist_lat_;
    float object_vre_long_;
    float object_vre_lat_;
    int object_dyn_prop_;
    float object_rcs_;    

public:
    ObjectGeneralInfo60B();
    void unPackBytes(const CAN_DataFrame& can_frame);
    int getObjectID();
    float getObjectDistLong();
    float getObjectDistLat();
    float getObjectVreLong();
    float getObjectVreLat();
    int getObjectDynProp();
    float getObjectRcs();
    GeneralInfo getGeneralInfo();
};

#endif //CONTI_RADAR_OBJECT_GENERAL_INFO_60B_H
