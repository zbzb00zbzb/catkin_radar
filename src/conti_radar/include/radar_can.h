//
// Created by zxkj on 18-8-5.
//

#ifndef RADAR_CAN_H
#define RADAR_CAN_H

#include "ICANCmd.h"
#include "ros/ros.h"
#include <iostream>
#include "pnc_msgs/VehicleInfo.h"
#include "raw_sensor_msgs/GnssImuInfo.h"
#include "pnc_msgs/Gear.h"
#include <thread>

struct CanParameters
{
    int can_channel_index;
    int can_baudrate;
    bool can_is_extern;
    bool can_is_remote;
    int can_work_mode; //0:normal, 1:listening only
    int can_filter_mode; //0:no use, 1:double filter, 2:single filter
    uint32_t can_acc_code;
    uint32_t can_acc_mask;
    int can_status;
};

class RadarCan
{
public:
    RadarCan();
    ~RadarCan();

    int doListening();

//    void recvCmdCallBack();
    void recvInfoCallback(const ros::TimerEvent&);
    void recvVehicleInfoCallback(const pnc_msgs::VehicleInfo::ConstPtr vehicleinfo);
    void recvGnssInfoCallback(const raw_sensor_msgs::GnssImuInfo::ConstPtr gnssimuinfo);
    void checkMsgCallback(const ros::TimerEvent&);
    void sendReqVehiclemsgCallback(const ros::TimerEvent&);
//    void quit();
//different radar has different protocol
    virtual void setup() = 0;
    virtual void transformCanToInfo(std::vector<CAN_DataFrame>& can_frames, int len) = 0;
    virtual bool checkInfo() = 0;

protected:
    //ros interface
    ros::Publisher mid_radar_info_pub_;
    ros::Publisher left_radar_info_pub_;
    ros::Publisher right_radar_info_pub_;
    ros::Subscriber vehicle_info_sub_;
    ros::Subscriber gnss_info_sub_;

    ros::NodeHandle node_handle_;
    ros::Timer recv_info_sub_;
    ros::Timer check_msg_;
    ros::Timer send_req_vehicle_msg_;

    //can interface
    int can_device_handle_;
    std::vector<CanParameters> can_parameters_;

    //can operate function
    int canStart(CanParameters can_parameters);
    int canOpen();
    int canClose();
    int canWrite(CanParameters can_parameters, unsigned int id, unsigned char* buf, unsigned char len);

    int missing_vehicle_info_counter_;
    int missing_gnss_info_counter_;
    int missing_can_info_counter_;

    int time_sharing_counter_;

    int recv_info_freq_;
    int check_msg_freq_;
    int send_req_vehicle_msg_freq_;
    bool is_recv_info_quit_;

    int max_missing_times_;

    double vehicle_msg_speed_;//provide by speed
    double vehicle_msg_yaw_rate_;//provide by gnss_info
    int vehicle_msg_motion_status_;

public:
    static bool is_quit_;
};

#endif //CONTI_RADAR_RADAR_CAN_H
