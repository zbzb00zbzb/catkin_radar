//
// Created by zxkj on 18-12-01.
//
#include "radar_can.h"
#include <boost/thread.hpp>
#include <csignal>
#include <conti_radar_msgs/conti_Objects.h>
#include <conti_radar_msgs/conti_Object.h>


bool RadarCan::is_quit_ = false;

RadarCan::RadarCan()
{
    is_recv_info_quit_ = false;
    missing_can_info_counter_ = 0;

    canOpen();
}

RadarCan::~RadarCan()
{
    mid_radar_info_pub_.shutdown();
    left_radar_info_pub_.shutdown();
    right_radar_info_pub_.shutdown();
    canClose();

    ros::shutdown();
}

void RadarCan::recvInfoCallback(const ros::TimerEvent&)
{
    CAN_DataFrame buf[100];  // data buffer
    std::vector<CAN_DataFrame> recs; // CAN data frame struct, is related to recv_info_freq_
    CAN_ErrorInformation err_info;

    for(size_t i = 0; i < can_parameters_.size(); ++i)
    {
        int rec_len = 0;
        if ((rec_len = CAN_ChannelReceive(can_device_handle_, can_parameters_[i].can_channel_index, buf,
                                         100, -1)) > 0)
        {
            missing_can_info_counter_ = 0;
            CAN_ClearReceiveBuffer(can_device_handle_, 0);
            for(int i = 0; i < rec_len; i++)
            {
                recs.emplace_back(buf[i]);
            }
            ROS_INFO("I recv %d CAN frames from radar",rec_len);
            transformCanToInfo(recs,rec_len);
        }
    }
}


void RadarCan::recvVehicleInfoCallback(const pnc_msgs::VehicleInfo::ConstPtr vehicleinfo)
{
    vehicle_msg_speed_ = vehicleinfo->vehicle_speed;
    switch (vehicleinfo->gear.value)
    {
        case pnc_msgs::Gear::GEAR_P :
        case pnc_msgs::Gear::GEAR_N : vehicle_msg_motion_status_ = 0; break;
        case pnc_msgs::Gear::GEAR_D : vehicle_msg_motion_status_ = 1; break;
        case pnc_msgs::Gear::GEAR_R : vehicle_msg_motion_status_ = 2; break;
        default:vehicle_msg_motion_status_ = 0; break;
    }

    missing_vehicle_info_counter_ = 0;
}


void RadarCan::recvGnssInfoCallback(const raw_sensor_msgs::GnssImuInfo::ConstPtr gnssimuinfo)
{
    vehicle_msg_yaw_rate_ = gnssimuinfo->yaw_rate;
    missing_gnss_info_counter_ = 0;
}

//void RadarCan::quit()
//{
//    mid_radar_info_pub_.shutdown();
//    left_radar_info_pub_.shutdown();
//    right_radar_info_pub_.shutdown();
//    canClose();
//
//    ros::shutdown();
//}


void RadarCan::checkMsgCallback(const ros::TimerEvent&)
{
    ++missing_can_info_counter_;
    ++missing_gnss_info_counter_;
    ++missing_vehicle_info_counter_;

    if (missing_can_info_counter_ > 10)
        ROS_ERROR("can't receive radar msgs!");

    if (missing_vehicle_info_counter_ > 10)
        ROS_ERROR("can't recevie vehicle_info msgs!");

    if (missing_gnss_info_counter_ > 10)
        ROS_ERROR("can't receive gnss_imu_info msgs!");

//    signal(SIGINT,&RadarCan::quit);
}

void RadarCan::sendReqVehiclemsgCallback(const ros::TimerEvent&)
{
    CAN_DataFrame  send[2];

    if(time_sharing_counter_ % 3 == 0)
    {
        send[0].uID = 0x300;
        send[1].uID = 0x301;
    }
    else if (time_sharing_counter_ % 3 == 1)
    {
        send[0].uID = 0x310;
        send[1].uID = 0x311;
    }
    else if (time_sharing_counter_ % 3 == 2)
    {
        send[0].uID = 0x320;
        send[1].uID = 0x321;
    }

    send[0].bRemoteFlag = 0;  // 0-数据帧；1-远程帧
    send[0].bExternFlag = 0;  // 0-标准帧；1-扩展帧
    send[0].nDataLen = 2;
    send[0].nSendType = 0;  // 0-正常发送;1-单次发送;2-自发自收;3-单次自发自收
    send[0].arryData[0] = (uint8_t)(((((uint16_t)(vehicle_msg_speed_ / 3.6 / 0.02)) >> 8) & 0x1F) + (vehicle_msg_motion_status_ << 6));
    send[0].arryData[1] = (uint8_t)(((uint16_t)(vehicle_msg_speed_ / 3.6 / 0.02)) & 0x00FF);
    while(CAN_ChannelSend(can_device_handle_, 0, &send[0] , 1) == 0);

    send[1].bRemoteFlag = 0;  // 0-数据帧；1-远程帧
    send[1].bExternFlag = 0;  // 0-标准帧；1-扩展帧
    send[1].nDataLen = 2;
    send[1].nSendType = 0;  // 0-正常发送;1-单次发送;2-自发自收;3-单次自发自收
    send[1].arryData[0] = (uint8_t)((((uint16_t)(vehicle_msg_yaw_rate_ / 0.01 + 32768)) & 0xFF00) >> 8);
    send[1].arryData[1] = (uint8_t)(((uint16_t)(vehicle_msg_yaw_rate_ / 0.01 + 32768)) & 0x00FF);
    while(CAN_ChannelSend(can_device_handle_, 0, &send[1] , 1) == 0);


    ++time_sharing_counter_;
}




int RadarCan::doListening()
{
    if(can_device_handle_ > 0)
    {
        for(size_t i = 0; i < can_parameters_.size(); ++i)
        {
            can_parameters_[i].can_status = canStart(can_parameters_[i]);
        }

        ROS_INFO("begin to listen!");

        vehicle_info_sub_ = node_handle_.subscribe(
                "pnc_msgs/vehicle_info", 1, &RadarCan::recvVehicleInfoCallback, this);
        gnss_info_sub_ = node_handle_.subscribe(
                "/trunk_info/gnss_ins", 1, &RadarCan::recvGnssInfoCallback, this);


        left_radar_info_pub_ = node_handle_.advertise<conti_radar_msgs::conti_Objects>(
                "/conti_radar_0/objects", 1);//conti_radar_left
        mid_radar_info_pub_ = node_handle_.advertise<conti_radar_msgs::conti_Objects>(
                "/conti_radar_1/objects", 1);//conti_radar_mid
        right_radar_info_pub_ = node_handle_.advertise<conti_radar_msgs::conti_Objects>(
                "/conti_radar_2/objects", 1);//conti_radar_right

        recv_info_sub_ = node_handle_.createTimer(
                ros::Duration(1.0 / recv_info_freq_), &RadarCan::recvInfoCallback, this, false, true);
        check_msg_ = node_handle_.createTimer(
                ros::Duration(1.0 / check_msg_freq_), &RadarCan::checkMsgCallback, this, false, true);
        send_req_vehicle_msg_ = node_handle_.createTimer(
                ros::Duration(1.0 / send_req_vehicle_msg_freq_), &RadarCan::sendReqVehiclemsgCallback, this, false, true);
        ros::spin();

        ROS_INFO("stop to listen!");
    }
}



int RadarCan::canOpen()
{
    if ((can_device_handle_ = CAN_DeviceOpen(LCMINIPCIE_252, 0, 0)) == 0) //LCMINIPCIE_252  ACUSB_132B
    {
        ROS_ERROR("open device error.");
        return -1;
    }
    ROS_INFO("open device ok.");
    return 0;
}

int RadarCan::canStart(CanParameters can_parameters)
{
    CAN_InitConfig can_init_config;

    can_init_config.dwAccCode = can_parameters.can_acc_code;
    can_init_config.dwAccMask = can_parameters.can_acc_mask;
    can_init_config.nFilter = can_parameters.can_filter_mode;   //滤波方式
    can_init_config.bMode = can_parameters.can_work_mode;       //工作模式
    can_init_config.nBtrType = 1;       //定位时参数模式（1表示SJA1000, O表示LPC21XX)

    switch (can_parameters.can_baudrate)
    {
        case 250:
        {
            can_init_config.dwBtr[0] = 0x01;   //BTR0  0014-1M  0016-800K 001C-500K  001C-250K 031C-12K
            can_init_config.dwBtr[1] = 0x1c;   //BTR1  041C-100K

            break;
        }
        case 500:
        {
            can_init_config.dwBtr[0] = 0x00;
            can_init_config.dwBtr[1] = 0x1c;

            break;
        }
        default:
            break;
    }
    can_init_config.dwBtr[2] = 0;
    can_init_config.dwBtr[3] = 0;

    if(CAN_RESULT_OK != CAN_ChannelStart(can_device_handle_, can_parameters.can_channel_index, &can_init_config))
    {
        ROS_ERROR("start CAN %d error!", can_parameters.can_channel_index);
        return -1;
    }

    ROS_INFO("start CAN %d success!", can_parameters.can_channel_index );
    return 0;
}

int RadarCan::canClose()
{
    for(size_t i = 0; i < can_parameters_.size(); ++i)
    {
        if(can_parameters_[i].can_status == 0)
        {
            CAN_ChannelStop(can_device_handle_, can_parameters_[i].can_channel_index);
            ROS_INFO("close can %d ok!", can_parameters_[i].can_channel_index);
        }
    }
    if(can_device_handle_ > 0)
    {
        CAN_DeviceClose(can_device_handle_);
        ROS_INFO("close device ok!");
    }
}
