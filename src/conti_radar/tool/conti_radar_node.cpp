//
// Created by zxkj on 18-8-6.
//


#include "radar_can_conti.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "conti_radar_node");

    RadarCan *radar_can = new RadarCan_Conti;

    radar_can->setup();
    radar_can->doListening();

    delete radar_can;

    return 0;
}
