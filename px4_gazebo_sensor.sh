#!/bin/bash
# must be run with root previleges. You can do it with "sudo -i"

## list of worlds

# list of world :
# baylands.world     hitl_standard_vtol.world  sonoma_raceway.world      windy.world
# boat.world         iris_irlock.world         typhoon_h480.world        yosemite.world
# empty.world        ksql_airport.world        uuv_bluerov2_heavy.world
# hippocampus.world  mcmillan_airfield.world   uuv_hippocampus.world
# hitl_iris.world    ocean.world               warehouse.world
world="baylands"
vehicle="iris_rplidar"

cd ~/src/Firmware
DONT_RUN=1 make px4_sitl gazebo_${vehicle}__${world}
source ~/catkin_ws/devel/setup.bash
source Tools/setup_gazebo.bash $(pwd) $(pwd)/build/px4_sitl_default
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:$(pwd)
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:$(pwd)/Tools/sitl_gazebo
roslaunch px4_quad_slam_simulation px4_sensor.launch fcu_url:="udp://:14540@127.0.0.1:14557"