uint8 LATERAL_MANEUVER_KEEP_IN_LANE = 0
uint8 LATERAL_MANEUVER_BYPASS_IN_LANE = 1
uint8 LATERAL_MANEUVER_CHANGE_TO_LEFT = 2
uint8 LATERAL_MANEUVER_CHANGE_TO_RIGHT = 3

uint8 SPEED_MANEUVER_FREE = 0
uint8 SPEED_MANEUVER_FOLLOW = 1
uint8 SPEED_MANEUVER_STOP = 2
uint8 SPEED_MANEUVER_ESTOP = 3



Header header

uint8 lateral_maneuver
uint8 speed_maneuver
float64 speed_limit
int32 target_lane_id


########## For SPEED_MANEUVER_FOLLOW ###################

VirtualWall[] virtual_wall

########## For LATERAL_MANEUVER_CHANGE_TO_* ############
float64 gap_speed_front
float64 gap_speed_back
float64 gap_distance_front
float64 gap_distance_back
