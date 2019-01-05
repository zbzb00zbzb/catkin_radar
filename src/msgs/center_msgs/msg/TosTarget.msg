# truck status
uint8 INNER_FORM_LOGIN            = 0
uint8 INNER_FORM_TRUCK_IDLE       = 1
uint8 INNER_FORM_TRUCK_EMPTY_TO_ORIGIN  = 2
uint8 INNER_FORM_TRUCK_EMPTY_AT_ORIGIN  = 3
uint8 INNER_FORM_TRUCK_LADEN_TO_DEST    = 4
uint8 INNER_FORM_TRUCK_LADEN_AT_DEST    = 5


Header header
string chid
string truck_pos
string transfer_zone
int32 container_type

int32 send_packet_id
