//
// Created by zxkj on 18-12-12.
//

#include "radar_visualizer.h"



RadarVisualizer::RadarVisualizer()
{

}


RadarVisualizer::~RadarVisualizer()
{

}


void RadarVisualizer::init()
{
    ROS_INFO("begin to run!");
}


void RadarVisualizer::objectsCallback(const conti_radar_msgs::conti_Objects::ConstPtr &msgs)
{
    visualization_msgs::Marker marker;
    int marker_id_ = 0;
    for(size_t i = 0; i < msgs->objects.size(); ++i)
    {
        conti_radar_msgs::conti_Object obj = msgs->objects[i];
        geometry_msgs::Point sz;
        sz.x = obj.Object_DistLat;//sz.x = obj.object_box_center.x;
        sz.y = obj.Object_DistLong;//sz.y = obj.object_box_center.y;
        sz.z = 0;
        marker.points.push_back(sz);
    }
    //ROS_ERROR("$$$$$$$$$$");
    marker.header.frame_id = "smartcar";
    marker.header.stamp = ros::Time(0);
    marker.ns = "objects";
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.orientation.w = 1.0;
    marker.id = marker_id_++;
    marker.lifetime = ros::Duration(0.1);
    marker.type = visualization_msgs::Marker::POINTS;
    marker.scale.x = 1.5;
    marker.scale.y = 1.5;
    marker.color.r = 1.0;
    marker.color.g = 0.0;
    marker.color.a = 1.0;
    
    send_visualizer_pub_.publish(marker);

}


void RadarVisualizer::doListening()
{
    send_visualizer_pub_ = node_handle_.advertise<visualization_msgs::Marker>(
            "visualization_makers",10);
    
    recv_objects_sub_ = node_handle_.subscribe(
            "/conti_radar_1/objects", 1, &RadarVisualizer::objectsCallback, this);//conti_radar_1/objects


    ros::spin();

}



