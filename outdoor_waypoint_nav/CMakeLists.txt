cmake_minimum_required(VERSION 3.0.3)
project(outdoor_waypoint_nav)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  tf
  roslib
  roslaunch
)

catkin_package()
roslaunch_add_file_check(launch)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
add_executable(outdoor_waypoint_nav-gps_waypoint src/gps_waypoint.cpp)
#add_executable(gps_waypoint_continuous src/gps_waypoint_continuous.cpp)
add_executable(outdoor_waypoint_nav-gps_waypoint_continuous1 src/gps_waypoint_continuous1.cpp)
add_executable(outdoor_waypoint_nav-gps_waypoint_continuous2 src/gps_waypoint_continuous2.cpp)
add_executable(outdoor_waypoint_nav-gps_waypoint_mapping src/gps_waypoint_mapping.cpp)
add_executable(outdoor_waypoint_nav-collect_gps_waypoints src/collect_gps_waypoints.cpp)
add_executable(outdoor_waypoint_nav-plot_gps_waypoints src/plot_gps_waypoints.cpp)
add_executable(outdoor_waypoint_nav-calibrate_heading src/calibrate_heading.cpp)
add_executable(outdoor_waypoint_nav-safety_node src/safety_node.cpp)
add_executable(outdoor_waypoint_nav-switch_controllers src/switch_controllers.cpp)

target_link_libraries(outdoor_waypoint_nav-gps_waypoint ${catkin_LIBRARIES})
# target_link_libraries(gps_waypoint_continuous ${catkin_LIBRARIES})
target_link_libraries(outdoor_waypoint_nav-gps_waypoint_continuous1 ${catkin_LIBRARIES})
target_link_libraries(outdoor_waypoint_nav-gps_waypoint_continuous2 ${catkin_LIBRARIES})
target_link_libraries(outdoor_waypoint_nav-gps_waypoint_mapping ${catkin_LIBRARIES})
target_link_libraries(outdoor_waypoint_nav-collect_gps_waypoints ${catkin_LIBRARIES})
target_link_libraries(outdoor_waypoint_nav-plot_gps_waypoints ${catkin_LIBRARIES})
target_link_libraries(outdoor_waypoint_nav-calibrate_heading ${catkin_LIBRARIES})
target_link_libraries(outdoor_waypoint_nav-safety_node ${catkin_LIBRARIES})
target_link_libraries(outdoor_waypoint_nav-switch_controllers ${catkin_LIBRARIES})

install(DIRECTORY  launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)