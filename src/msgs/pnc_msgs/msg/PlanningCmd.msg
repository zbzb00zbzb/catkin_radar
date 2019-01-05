uint8 MODE_AUTO = 0
uint8 MODE_LATERAL_CLOSED_LOOP = 1
uint8 MODE_SPEED_CLOSED_LOOP = 2
uint8 MODE_OPEN_LOOP = 3

uint8 STATE_KEEP_LANE = 0
uint8 STATE_CHANGE_LANE_P1 = 1
uint8 STATE_CHANGE_LANE_P2 = 2
uint8 STATE_STOP = 3
uint8 STATE_END = 4


Header header

uint8 mode
pnc_msgs/WayPoint[] way_points
pnc_msgs/VehicleCmd open_loop_cmd
float64 speed
uint8 state

########## STOP AT DEST ################################
bool stop_at_dest