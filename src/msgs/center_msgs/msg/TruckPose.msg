# truck register
uint8 TRUNK_UNREGISTER         = 0
uint8 TRUNK_REGISTER           = 1

Header header
string chid
geometry_msgs/Transform pose
int32 recv_packet_id
int32 send_packet_id
uint8 trunk_register
