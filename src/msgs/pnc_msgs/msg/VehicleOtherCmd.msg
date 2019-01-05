
uint8 MODE_MANUAL = 100
uint8 MODE_AUTO = 101

Header header

uint8 turn_light_mode
uint8 turn_light            #0:left  1:right  2:both  3:invalid

uint8 light_mode
uint8 light                 #front light    0:close  1:near light   2:far light  3:invalid

uint8 wiper_mode
uint8 wiper                 #0:wiper close  1:run wiper  2:reserve  3:invalid

uint8 door_mode
uint8 door                  #0:no control  1:normal open  2:emergency open  3:reserve

uint8 trumpet_mode
uint8 trumpet               #0:no control  1:open

uint8 auto_driver_cmd
uint8 estop_cmd

