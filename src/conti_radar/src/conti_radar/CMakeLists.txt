add_library(conti_radar_lib
        object_extended_info_60d.cpp
        object_quality_info_60c.cpp
        object_general_info_60b.cpp
        object_list_status_60a.cpp
        radar_state_201.cpp
)

install(TARGETS conti_radar_lib
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})