# PLC Expected direction
uint8 TRUCK_NONE_CMD        = 0
uint8 TRUCK_STOP            = 1
uint8 TRUCK_MOVE_FORWARD    = 2
uint8 TRUCK_MOVE_BACKWARD   = 3

Header header
uint8 expected_direction
int32 expected_distances

int32 send_packet_id
