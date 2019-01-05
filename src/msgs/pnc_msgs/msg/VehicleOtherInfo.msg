uint8 MODE_MANUAL = 70
uint8 MODE_AUTO = 71
uint8 MODE_INTERVENED = 72

Header header

uint8 turn_light_status
uint8 door_status
uint8 wiper_status
uint8 trumpet_status
uint8 light_status
uint8 dump_energy_status

uint8 auto_driver_status            #0:auto_driver          1:human intervention 2:udp lost 3:can lost
uint16 vehicle_error_status         #contain eight status, each status takes 2 bits          vehicle_error/steering_error/gear_error/throttle_error/brake_error/
uint16 transfer_to_upper_cmd        #contain eight cmds, each cmd takes 2 bits          TBD

uint8 counter  #0~15 cycle counter

#just for sinotruk_bus
uint8 v2x_link_status
uint8 v2x_light_left_time
uint8 v2x_light_status
float64 v2x_distance_to_stop



