//
// Created by zxkj on 18-12-12.
//

#ifndef RADAR_VISUALIZER_RADAR_VISUALIZER_H
#define RADAR_VISUALIZER_RADAR_VISUALIZER_H

#include "ros/ros.h"
#include "conti_radar_msgs/conti_Objects.h"
#include "conti_radar_msgs/conti_Object.h"
#include "visualization_msgs/Marker.h"

class RadarVisualizer
{
private:
    ros::NodeHandle node_handle_;
    ros::Subscriber recv_objects_sub_;

    ros::Publisher send_visualizer_pub_;

public:
    RadarVisualizer();
    ~RadarVisualizer();


    void init();
    void doListening();

    void objectsCallback(const conti_radar_msgs::conti_Objects::ConstPtr &objects);
};



#endif //SENSOR_VISUALIZER_SENSOR_VISUALIZER_H
