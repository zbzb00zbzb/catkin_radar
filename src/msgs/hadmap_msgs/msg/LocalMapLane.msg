# lane id
int32 id
# residual length
float32 residual_len

float32 stopline_distance
geometry_msgs/Point stopline

# central planning points
LocalMapPoint[] center
# left boundary
LocalMapPoint[] left
# right boundary
LocalMapPoint[] right


