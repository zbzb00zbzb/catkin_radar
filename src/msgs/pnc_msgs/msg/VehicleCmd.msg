uint8 MODE_MANUAL = 100
uint8 MODE_AUTO = 101

uint8 OFF = 150              # For horn, left_light and right_light
uint8 ON = 151               # For horn, left_light and right_light

Header header

uint8 steering_mode
float64 steering_angle     # -1.0 ~ 1.0, positive number on the right side
float64 steering_speed     # 0.0 ~ 1.0

uint8 throttle_mode
float64 throttle           # 0.0 ~ 1.0
uint8 brake_mode
float64 brake              # 0.0 ~ 1.0

float64 acceleration_request   # m/s2
uint8 acceleration_mode

pnc_msgs/Gear gear
uint8 gear_mode
uint8 horn
uint8 left_light
uint8 right_light

