uint8 VIRTUAL_WALL_TYPE_UNKNOWN = 0
uint8 VIRTUAL_WALL_TYPE_STOPLINE = 1
uint8 VIRTUAL_WALL_TYPE_OBSTACLE = 2
uint8 VIRTUAL_WALL_TYPE_OBSTACLE_VIRTUAL = 3
uint8 VIRTUAL_WALL_TYPE_OCCUPANCY_GRID = 4
uint8 VIRTUAL_WALL_TYPE_STOPLINE_TAG = 5
uint8 VIRTUAL_WALL_TYPE_STOPLINE_PLC = 6

uint8   virtual_wall_type
uint32  virtual_wall_id
float64 follow_second
float64 follow_distance
float64 follow_speed
float64 follow_acceleration     # Optional

