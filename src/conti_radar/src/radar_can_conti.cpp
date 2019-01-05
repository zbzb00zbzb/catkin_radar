//
// Created by zxkj on 18-8-6.
//
#include "radar_can_conti.h"
#include <math.h>


RadarCan_Conti::RadarCan_Conti()
{
    //channel0,500K,no extern,no remote,normal mode,double filter,acccode,accmode,can status
    CanParameters can_init_parameter_;
    can_init_parameter_.can_channel_index = 0; //0:channel0, 1:channel1
    can_init_parameter_.can_baudrate = 500;    //set baudrate 500K
    can_init_parameter_.can_is_extern = 0;     //0:standard frame, 1:extern frame
    can_init_parameter_.can_is_remote = 0;     //0:data frame, 1:remote frame
    can_init_parameter_.can_work_mode = 0;     //0:normal, 1:listening only
    can_init_parameter_.can_filter_mode = 0;   //0:no use, 1:double filter, 2:single filter
    can_init_parameter_.can_acc_code = 0x000080C7;  //not use
    can_init_parameter_.can_acc_mask = 0xFFFF7F00;  //not use
    can_init_parameter_.can_status = -1;    //

    can_parameters_.push_back(can_init_parameter_);//can0
}

bool RadarCan_Conti::checkInfo()
{
    bool flag = true;
    return flag;
}

void RadarCan_Conti::setup()
{
    node_handle_.param("/conti_radar/recv_info_freq", recv_info_freq_, 1000);
    node_handle_.param("/conti_radar/max_missing_times", max_missing_times_, 100);

    node_handle_.param("/conti_radar/long_offset_mid", long_offset_mid_, 0.0);//3.6
    node_handle_.param("/conti_radar/lat_offset_mid", lat_offset_mid_, 0.0);//0.23
    node_handle_.param("/conti_radar/angular_deviation_id", angular_deviation_mid_, 0.0);

    node_handle_.param("/conti_radar/long_offset_left", long_offset_left_, 6.0);
    node_handle_.param("/conti_radar/lat_offset_left", lat_offset_left_, -1.12);
    node_handle_.param("/conti_radar/angular_deviation_left", angular_deviation_left_, 165.0);

    node_handle_.param("/conti_radar/long_offset_right", long_offset_right_, 6.0);
    node_handle_.param("/conti_radar/lat_offset_right", lat_offset_right_, 1.12);
    node_handle_.param("/conti_radar/angular_deviation_right", angular_deviation_right_, 15.0);

    node_handle_.param("/conti_radar/check_msg_freq", check_msg_freq_, 10);
    node_handle_.param("/conti_radar/send_req_vehicle_msg_freq", send_req_vehicle_msg_freq_, 50);


    angular_deviation_mid_ = angular_deviation_mid_ / 180 * M_PI;
    angular_deviation_left_ = angular_deviation_left_ / 180 * M_PI;
    angular_deviation_right_ = angular_deviation_right_ / 180 * M_PI;

    object_mid_num_ = -1;
    object_left_num_ = -1;
    object_right_num_ = -1;

    general_info_arr_mid_.clear();
    quality_info_arr_mid_.clear();
    extended_info_arr_mid_.clear();

    general_info_arr_left_.clear();
    quality_info_arr_left_.clear();
    extended_info_arr_left_.clear();

    general_info_arr_right_.clear();
    quality_info_arr_right_.clear();
    extended_info_arr_right_.clear();
}


void RadarCan_Conti::leftMessagePub()
{
//     if(object_left_num_ == -1)//if not reassign the object_num_ in OBJECT_LIST_STATUS branch
//     {
//         general_info_arr_left_.clear();
//         quality_info_arr_left_.clear();
//         extended_info_arr_left_.clear();

// //        ROS_ERROR("error num of left object");
//     }
//     else if(object_left_num_ >= 0)
//     {
//         if(object_left_num_ == general_info_arr_left_.size() &&
//            object_left_num_ == quality_info_arr_left_.size() &&
//            object_left_num_ == extended_info_arr_left_.size())  //in a period recv all the CAN frame
//         {
//             conti_radar_msgs::Object object_;
//             conti_radar_msgs::Objects objects_msgs_;

//             for(size_t i = 0; i < general_info_arr_left_.size(); ++i)
//             {
//                 object_.id = general_info_arr_left_[i].object_id_;

//                 double object_box_center_x = general_info_arr_left_[i].object_dist_long_;
//                 double object_box_center_y = general_info_arr_left_[i].object_dist_lat_;

//                 object_.object_box_center.x = object_box_center_x * cos(angular_deviation_left_) - object_box_center_y * sin(angular_deviation_left_) + long_offset_left_;
//                 object_.object_box_center.y = object_box_center_x * sin(angular_deviation_left_) + object_box_center_y * cos(angular_deviation_left_) + lat_offset_left_;
// //                double temp = object_.object_box_center.y;//for lux object
// //                object_.object_box_center.y = -object_.object_box_center.x;//for lux object
// //                object_.object_box_center.x = temp;

//                 object_.relative_velocity.x = general_info_arr_left_[i].object_vre_long_ * cos(angular_deviation_left_) - general_info_arr_left_[i].object_vre_lat_ * sin(angular_deviation_left_);
//                 object_.relative_velocity.y = general_info_arr_left_[i].object_vre_long_ * sin(angular_deviation_left_) + general_info_arr_left_[i].object_vre_lat_ * cos(angular_deviation_left_);
// //                temp = object_.relative_velocity.y;//for lux object
// //                object_.relative_velocity.y = -object_.relative_velocity.x;//for lux object
// //                object_.relative_velocity.x = temp;

//                 for(size_t j = 0; j < quality_info_arr_left_.size(); ++j)
//                 {
//                     if(object_.id == quality_info_arr_left_[j].object_id_)
//                     {
//                         //if need any other quality info message can manage here
//                     }
//                 }
//                 for(size_t k = 0; k < extended_info_arr_left_.size(); ++k)
//                 {
//                     if(object_.id == extended_info_arr_left_[k].object_id_)
//                     {
//                         object_.object_box_size.x = extended_info_arr_left_[k].object_length_;
//                         object_.object_box_size.y = extended_info_arr_left_[k].object_width_;
//                         object_.classification = extended_info_arr_left_[k].object_class_;
//                         //object_.object_box_orientation = -extended_info_arr_left_[k].object_orientation_angel_ - 75.0;//rotate box orientation;

//                         object_.relative_acceleration.x = extended_info_arr_left_[k].object_arel_long_ * cos(angular_deviation_left_) - extended_info_arr_left_[k].object_arel_lat_ * sin(angular_deviation_left_);
//                         object_.relative_acceleration.y = extended_info_arr_left_[k].object_arel_long_ * sin(angular_deviation_left_) + extended_info_arr_left_[k].object_arel_lat_ * cos(angular_deviation_left_);
// //                        temp = object_.relative_acceleration.y;//for lux object
// //                        object_.relative_acceleration.y = -object_.relative_acceleration.x;//for lux object
// //                        object_.relative_acceleration.x = temp;
//                     }
//                 }
//                 objects_msgs_.objects.push_back(object_);
//             }

//             objects_msgs_.header.frame_id = "conti_radar_left";//conti_radar_left
//             objects_msgs_.header.stamp = ros::Time::now();
//             left_radar_info_pub_.publish(objects_msgs_);

//             general_info_arr_left_.clear();
//             quality_info_arr_left_.clear();
//             extended_info_arr_left_.clear();

//             object_left_num_ = -1;
//         }
//     }
}


void RadarCan_Conti::midMessagePub()
{
//    ROS_INFO("general: %d",general_info_arr_mid_.size());
//    ROS_INFO("quality: %d",quality_info_arr_mid_.size());
//    ROS_INFO("extended: %d",extended_info_arr_mid_.size());

    if(object_mid_num_ == -1)//if not reassign the object_num_ in OBJECT_LIST_STATUS branch
    {
        general_info_arr_mid_.clear();
        quality_info_arr_mid_.clear();
        extended_info_arr_mid_.clear();
//        ROS_ERROR("error num of mid object");
    }
    else if(object_mid_num_ >= 0)
    {
        if(object_mid_num_ == general_info_arr_mid_.size() &&
           object_mid_num_ == quality_info_arr_mid_.size() &&
           object_mid_num_ == extended_info_arr_mid_.size())  //in a period recv all the CAN frame
        {
            conti_radar_msgs::conti_Object object_;
            conti_radar_msgs::conti_Objects objects_msgs_;

            for(size_t i = 0; i < general_info_arr_mid_.size(); ++i)
            {
                object_.ID = general_info_arr_mid_[i].object_id_ + 200;
                object_.Object_DistLong = general_info_arr_mid_[i].object_dist_long_;
                object_.Object_DistLat = general_info_arr_mid_[i].object_dist_lat_;
                object_.Object_VrelLong = general_info_arr_mid_[i].object_vre_long_;
                object_.Object_VrelLat = general_info_arr_mid_[i].object_vre_lat_;
                object_.Object_DynProp = general_info_arr_mid_[i].object_dyn_prop_;
                object_.Object_RCS = general_info_arr_mid_[i].object_rcs_;
                
                for(size_t j = 0; j < quality_info_arr_mid_.size(); ++j)
                {
                    if(object_.ID == quality_info_arr_mid_[j].object_id_ + 200)
                    {
                        object_.Obj_ProbOfExist = quality_info_arr_mid_[j].object_prob_of_exist_;
                    }
                }
                for(size_t k = 0; k < extended_info_arr_mid_.size(); ++k)
                {
                    if(object_.ID == extended_info_arr_mid_[k].object_id_ + 200)
                    {
                        object_.Object_OrientationAngel = extended_info_arr_mid_[k].object_orientation_angel_;
                        object_.Object_Length = extended_info_arr_mid_[k].object_length_;
                        object_.Object_Width = extended_info_arr_mid_[k].object_width_;
                    }
                }
                objects_msgs_.objects.push_back(object_);
            }
            objects_msgs_.header.frame_id = "conti_radar_mid";//conti_radar_mid
            objects_msgs_.header.stamp = ros::Time::now();
            mid_radar_info_pub_.publish(objects_msgs_);

            general_info_arr_mid_.clear();
            quality_info_arr_mid_.clear();
            extended_info_arr_mid_.clear();

            object_mid_num_ = -1;
        }
    }
}


void RadarCan_Conti::rightMessagePub()
{
//     if(object_right_num_ == -1)//if not reassign the object_num_ in OBJECT_LIST_STATUS branch
//     {

//         general_info_arr_right_.clear();
//         quality_info_arr_right_.clear();
//         extended_info_arr_right_.clear();

// //        ROS_ERROR("error num of right object");
//     }
//     else if(object_right_num_ >= 0)
//     {
//         if(object_right_num_ == general_info_arr_right_.size() &&
//            object_right_num_ == quality_info_arr_right_.size() &&
//            object_right_num_ == extended_info_arr_right_.size())  //in a period recv all the CAN frame
//         {
//             conti_radar_msgs::Object object_;
//             conti_radar_msgs::Objects objects_msgs_;

//             for(size_t i = 0; i < general_info_arr_right_.size(); ++i)
//             {
//                 object_.id = general_info_arr_right_[i].object_id_ + 400;

//                 double object_box_center_x = general_info_arr_right_[i].object_dist_long_;
//                 double object_box_center_y = general_info_arr_right_[i].object_dist_lat_;

//                 object_.object_box_center.x = object_box_center_x * cos(angular_deviation_right_) + object_box_center_y * sin(angular_deviation_right_) + long_offset_right_;
//                 object_.object_box_center.y = -(object_box_center_x * sin(angular_deviation_right_) - object_box_center_y * cos(angular_deviation_right_)) + lat_offset_right_;
// //                double temp = object_.object_box_center.y;//for lux object
// //                object_.object_box_center.y = -object_.object_box_center.x;//for lux object
// //                object_.object_box_center.x = temp;

//                 object_.relative_velocity.x = general_info_arr_right_[i].object_vre_long_ * cos(angular_deviation_right_) + general_info_arr_right_[i].object_vre_lat_ * sin(angular_deviation_right_);
//                 object_.relative_velocity.y = -(general_info_arr_right_[i].object_vre_long_ * sin(angular_deviation_right_) - general_info_arr_right_[i].object_vre_lat_ * cos(angular_deviation_right_));
// //                temp = object_.relative_velocity.y;//for lux object
// //                object_.relative_velocity.y = -object_.relative_velocity.x;//for lux object
// //                object_.relative_velocity.x = temp;

//                 for(size_t j = 0; j < quality_info_arr_right_.size(); ++j)
//                 {
//                     if(object_.id == quality_info_arr_right_[j].object_id_ + 400)
//                     {
//                         //if need any other quality info message can manage here
//                     }
//                 }
//                 for(size_t k = 0; k < extended_info_arr_right_.size(); ++k)
//                 {
//                     if(object_.id == extended_info_arr_right_[k].object_id_ + 400)
//                     {
//                         object_.object_box_size.x = extended_info_arr_right_[k].object_length_;
//                         object_.object_box_size.y = extended_info_arr_right_[k].object_width_;
//                         object_.classification = extended_info_arr_right_[k].object_class_;
//                         //object_.object_box_orientation = extended_info_arr_right_[k].object_orientation_angel_ + 75;//rotate box orientation;
//                         object_.relative_acceleration.x = extended_info_arr_right_[k].object_arel_long_ * cos(angular_deviation_right_) + extended_info_arr_right_[k].object_arel_lat_ * sin(angular_deviation_right_);
//                         object_.relative_acceleration.y = -(extended_info_arr_right_[k].object_arel_long_ * sin(angular_deviation_right_) - extended_info_arr_right_[k].object_arel_lat_ * cos(angular_deviation_right_));
// //                        temp = object_.relative_acceleration.y;//for lux object
// //                        object_.relative_acceleration.y = -object_.relative_acceleration.x;//for lux object
// //                        object_.relative_acceleration.x = temp;
//                     }
//                 }
//                 objects_msgs_.objects.push_back(object_);
//             }

//             objects_msgs_.header.frame_id = "conti_radar_right";//conti_radar_right
//             objects_msgs_.header.stamp = ros::Time::now();
//             right_radar_info_pub_.publish(objects_msgs_);

//             general_info_arr_right_.clear();
//             quality_info_arr_right_.clear();
//             extended_info_arr_right_.clear();

//             object_right_num_ = -1;
//         }
//     }
}


void RadarCan_Conti::transformCanToInfo(std::vector<CAN_DataFrame>& can_frames, int len)
{
    for(int i = 0; i < len; i++)
    {
        int current_id = can_frames[i].uID;
        switch (current_id)
        {
//            case RADAR_STATE_MID:
//            {
//                radar_state_.unPackBytes(can_frames[i]);
//                ROS_ERROR("getMaxDistanceCfg:%d",radar_state_.getMaxDistanceCfg());
//                ROS_ERROR("getErrorState:%d",radar_state_.getErrorState());
//                ROS_ERROR("getSensorID:%d",radar_state_.getSensorID());
//                ROS_ERROR("getSortIndex:%d",radar_state_.getSortIndex());
//                ROS_ERROR("getRadarPower:%d",radar_state_.getRadarPower());
//                ROS_ERROR("getOutputType:%d",radar_state_.getOutputType());
//                ROS_ERROR("getSendQuality:%d",radar_state_.getSendQuality());
//                ROS_ERROR("getSendExtInfo:%d",radar_state_.getSendExtInfo());
//                ROS_ERROR("getMotionRxState:%d",radar_state_.getMotionRxState());
//                ROS_ERROR("getRCS_Threshold:%d",radar_state_.getRCS_Threshold());
//            }
            case OBJECT_LIST_STATUS_MID://)0x60A
            {
                object_list_status_.unPackBytes(can_frames[i]);
                object_mid_num_= object_list_status_.getNumOfObj();
                general_info_arr_mid_.clear();
                quality_info_arr_mid_.clear();
                extended_info_arr_mid_.clear();

                ROS_INFO("I CAN detect %d objects in mid radar",object_mid_num_);

            }
                break;
            case OBJECT_GENERAL_INFO_MID:
            {
                object_general_info_.unPackBytes(can_frames[i]);
                GeneralInfo general_info_;
                general_info_ = object_general_info_.getGeneralInfo();
                general_info_arr_mid_.emplace_back(general_info_);
            }
                break;
            case OBJECT_QUALITY_INFO_MID:
            {
                object_quality_info_.unPackBytes(can_frames[i]);
                QualityInfo quality_info_;
                quality_info_ = object_quality_info_.getQualityInfo();
                quality_info_arr_mid_.emplace_back(quality_info_);
            }
                break;
            case OBJECT_EXTENDED_INFO_MID:
            {
                object_extended_info_.unPackBytes(can_frames[i]);
                ExtendedInfo extended_info_;
                extended_info_ = object_extended_info_.getExtendedInfo();
                extended_info_arr_mid_.emplace_back(extended_info_);
            }
                break;
            case OBJECT_LIST_STATUS_LEFT:
            {
                object_list_status_.unPackBytes(can_frames[i]);
                object_left_num_= object_list_status_.getNumOfObj();
                general_info_arr_left_.clear();
                quality_info_arr_left_.clear();
                extended_info_arr_left_.clear();

                ROS_INFO("I CAN detect %d objects in left radar",object_left_num_);
            }
                break;
            case OBJECT_GENERAL_INFO_LEFT:
            {
                object_general_info_.unPackBytes(can_frames[i]);
                GeneralInfo general_info_;
                general_info_ = object_general_info_.getGeneralInfo();
                general_info_arr_left_.emplace_back(general_info_);
            }
                break;
            case OBJECT_QUALITY_INFO_LEFT:
            {
                object_quality_info_.unPackBytes(can_frames[i]);
                QualityInfo quality_info_;
                quality_info_ = object_quality_info_.getQualityInfo();
                quality_info_arr_left_.emplace_back(quality_info_);
            }
                break;
            case OBJECT_EXTENDED_INFO_LEFT:
            {
                object_extended_info_.unPackBytes(can_frames[i]);
                ExtendedInfo extended_info_;
                extended_info_ = object_extended_info_.getExtendedInfo();
                extended_info_arr_left_.emplace_back(extended_info_);
            }
                break;
            case OBJECT_LIST_STATUS_RIGHT:
            {
                object_list_status_.unPackBytes(can_frames[i]);
                object_right_num_= object_list_status_.getNumOfObj();
                general_info_arr_right_.clear();
                quality_info_arr_right_.clear();
                extended_info_arr_right_.clear();

                ROS_INFO("I CAN detect %d objects in right radar",object_right_num_);
            }
                break;
            case OBJECT_GENERAL_INFO_RIGHT:
            {
                object_general_info_.unPackBytes(can_frames[i]);
                GeneralInfo general_info_;
                general_info_ = object_general_info_.getGeneralInfo();
                general_info_arr_right_.emplace_back(general_info_);
            }
                break;
            case OBJECT_QUALITY_INFO_RIGHT:
            {
                object_quality_info_.unPackBytes(can_frames[i]);
                QualityInfo quality_info_;
                quality_info_ = object_quality_info_.getQualityInfo();
                quality_info_arr_right_.emplace_back(quality_info_);
            }
                break;
            case OBJECT_EXTENDED_INFO_RIGHT:
            {
                object_extended_info_.unPackBytes(can_frames[i]);
                ExtendedInfo extended_info_;
                extended_info_ = object_extended_info_.getExtendedInfo();
                extended_info_arr_right_.emplace_back(extended_info_);
            }
                break;
            default:
                continue;
        }
        midMessagePub();   // 在里面判断这一组是否凑齐。凑齐了就发送。
        leftMessagePub();
        rightMessagePub();
    }

}




