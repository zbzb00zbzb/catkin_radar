int32 POSITION_TYPE_NONE = 0
int32 POSITION_TYPE_FIXEDPOS = 1
int32 POSITION_TYPE_FIXEDHEIGHT = 2
int32 POSITION_TYPE_DOPPLER_VELOCITY = 8
int32 POSITION_TYPE_SINGLE = 16
int32 POSITION_TYPE_PSRDIFF = 17
int32 POSITION_TYPE_SBAS = 18
#int32 POSITION_TYPE_WAAS = 18
int32 POSITION_TYPE_PROPAGATED = 19
int32 POSITION_TYPE_OMNISTAR = 20
int32 POSITION_TYPE_L1_FLOAT = 32
int32 POSITION_TYPE_IONOFREE_FLOAT = 33
int32 POSITION_TYPE_NARROW_FLOAT = 34
int32 POSITION_TYPE_L1_INT = 48
int32 POSITION_TYPE_WIDE_INT = 49
int32 POSITION_TYPE_NARROW_INT = 50
int32 POSITION_TYPE_OMNISTAR_HP = 64
int32 POSITION_TYPE_OMNISTAR_XP = 65
#int32 POSITION_TYPE_PPP_CONVERGING = 68
#int32 POSITION_TYPE_PPP = 69
#int32 POSITION_TYPE_OPERATIONAL = 70
#int32 POSITION_TYPE_WARNING = 71
#int32 POSITION_TYPE_OUT_OF_BOUNDS = 72

Header header

# position
float64 latitude
float64 longitude
float64 altitude

float64 utm_east
float64 utm_north

float32 latitude_std
float32 longitude_std
float32 altitude_std

# velocity
float64 north_velocity
float64 east_velocity
float64 up_velocity

float32 north_velocity_std
float32 east_velocity_std
float32 up_velocity_std

# attitude
float64 roll
float64 pitch
float64 yaw

float64 x
float64 y
float64 z
float64 w

float32 roll_std
float32 pitch_std
float32 yaw_std

#angular velocity
float64 roll_rate
float64 pitch_rate
float64 yaw_rate

#acceleration
float64 ax
float64 ay
float64 az

#INS550D status
#initialization status
uint8 init_position
uint8 init_velocity
uint8 init_pitchroll
uint8 init_yaw

#gps status
int32 gps_status
int32 gps_satellitenum

#wheel speed status
int32 wheelspeed_status

#device status
float64 temperature
