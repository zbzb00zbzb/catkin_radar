//
// Created by zxkj on 18-12-12.
//

#include "radar_visualizer.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "radar_visualizer");

    RadarVisualizer *radarvisualizer = new RadarVisualizer;

    radarvisualizer->init();
    radarvisualizer->doListening();


    delete(radarvisualizer);

    return 0;
}

