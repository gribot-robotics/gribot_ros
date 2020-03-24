#!/bin/bash -i

clear
sudo echo "Searching for devices..."
source ~/ros_gribot/devel/setup.bash
echo $ROS_PACKAGE_PATH

# Scan for the laser and the piksi multi

#Find Wolverine path
# export WOLVERINE_PORT="/dev/`ls -l /dev/ttyUSB0 | cut --delimiter=/ -f3 | cut --delimiter=\  -f1`"
# if [ "$WOLVERINE_PORT" = "/dev/" ]; then
# 	echo "ERROR: Wolverine Robot not found"
# else
# 	export WOLVERINE_ENABLED="true"
# 	echo "Wolverine:"
# 	echo "    Port = $WOLVERINE_PORT"
# fi

#Ask to enable autonomous navigation
# echo
# yes="false"
# while [ "$yes" = "false" ]; do
# 	read -e -p "Enable autonomous navigation? (y|n): " answer
# 	case $answer in
# 		[Yy]* )
# export WOLVERINE_NAV_ENABLED="true"
# yes="true";;
# [Nn]* )
# export WOLVERINE_NAV_ENABLED="false"
# yes="true";;
# * )
# echo "Please answer yes or no.";;
# esac
# done

# If using a USB to input the waypoints.
# if [ "$WOLVERINE_NAV_ENABLED" = "true" ]; then
#     echo "Autonomous Navigation:"
#     export WOLVERINE_COORDS_PATH=`sudo find /!(proc|sys|dev) -name Wolverine_Coords_New.kml | grep "media"` #Changed the KML File -
#     if [ "$WOLVERINE_COORDS_PATH" = "" ]; then
#         echo "    ERROR: Could not find Wolverine Coordinates file. Using Default coordinates."
#     else
#         echo "    Wolverine Coordinates file: $WOLVERINE_COORDS_PATH"
#         #cat $WOLVERINE_COORDS_PATH | grep ',' | cut --delimiter=, -f1-2 | tr -d ' ' | tr "," "\t" | proj +proj=utm +zone=10 | tr "\t" "," > Wolverine_Coords_New.txt # Changed the command
#         export WOLVERINE_COORDS_PATH=$PWD"/Block309_path1.txt"
#     fi
# fi
# export WOLVERINE_COORDS_PATH=$PWD"/auto_nav_testing.txt"
# echo "    Wolverine Coordinates file: $WOLVERINE_COORDS_PATH"

## This is new command to read the new KML format that I got from using GoogleMaps. -
## cat Wolverine_Coords_New.kml | grep ',' | cut --delimiter=, -f1-2 | tr -d ' ' | tr ',' '\t'

#Ask if the session should be bagged
echo
yes="false"
while [ "$yes" = "false" ]; do
	read -e -p "Should this session be saved? (y|n): " answer
	case $answer in
		[Yy]* )
export WOLVERINE_BAG_ENABLED="true"
yes="true";;
[Nn]* )
export WOLVERINE_BAG_ENABLED="false"
yes="true";;
* )
echo "Please answer yes or no.";;
esac
done

## Time variables for directory and bag name -  ##
DATE=`date +%Y-%m-%d`
TIME=`date +%H-%M-%S`

if [ $WOLVERINE_BAG_ENABLED = "true" ]; then

	## Asks user for directory. Default will create a directory with today's date as name. -
	## If user inputs their own directory it must be an existing directory. -
	read -e -p $'\nPlease enter bag directory if different from default. Else ENTER to continue:\n(default = /home/user/Desktop/MM-DD-YYYY/)\n>' WOLVERINE_BAG_DIRECTORY_NEW
	## Asks user to name the bag file. Default will name the file with a timestamp. -
	read -e -p $'\nPlease enter name for bag file if different from default. Else ENTER to continue:\n(default = HOUR-MINUTE-SECOND.bag) \n>' BAG_NAME
	## Logic for creating Date directory if needed and naming the bag file as necessary.
	## WOLVERINE_BAG_DIR gets exported at end using the other vairables
	if [ -z "$WOLVERINE_BAG_DIRECTORY_NEW" ]; then
		mkdir -p /media/$USER/14f82e84-12fa-4b04-9d1a-d0e55a5c1931/$DATE
		if [ -z "$BAG_NAME" ]; then
			export WOLVERINE_BAG_DIR=/media/$USER/14f82e84-12fa-4b04-9d1a-d0e55a5c1931/$DATE/$TIME.bag
		else
			export WOLVERINE_BAG_DIR=/media/$USER/14f82e84-12fa-4b04-9d1a-d0e55a5c1931/$DATE/$BAG_NAME.bag
		fi
	else
		if [ -z "$BAG_NAME" ]; then
			export WOLVERINE_BAG_DIR=$WOLVERINE_BAG_DIRECTORY_NEW$TIME.bag
		else
			export WOLVERINE_BAG_DIR=$WOLVERINE_BAG_DIRECTORY_NEW$BAG_NAME.bag
		fi
	fi

	printf "\nBag path: $WOLVERINE_BAG_DIR\n"
	# echo
	# yes="false"
	# while [ "$yes" = "false" ]; do
	# 	read -p "Save laser output? Note this could take a lot of space. (y|n)" answer
	# 	case $answer in
	# 		[Yy]* )
	# 			export WOLVERINE_BAG_LASER="true"
	# 			yes="true";;
	# 		[Nn]* )
	# 			export WOLVERINE_BAG_LASER="false"
	# 			yes="true";;
	# 		* )
	# 			echo "Please answer yes or no.";;
	# 	esac
	# done
fi

# if [[ $WOLVERINE_TOPCON1_ENABLED = "true" ]]; then
# 	if [[ $WOLVERINE_TOPCON2_ENABLED = "true" ]]; then
	# export WOLVERINE_TOPCON_DUAL_ENABLED="true"
# 	fi
# fi

#Ask if the motors has to be tune
# echo
# yes="false"
# while [ "$yes" = "false" ]; do
# 	read -e -p "Do you want to tune the motors PID? (y|n): " answer
# 	case $answer in
# 		[Yy]* )
# 			python3 ~/Dropbox/ros/ros_wolverine/src/odrive_ros/src/odrive_ros/tune.py
# 			yes="true";;
# 		[Nn]* )
# 			yes="true";;
# 		* )
# 			echo "Please answer yes or no.";;
# 	esac
# done

# python3 calibration_script.py
# TODO: python3 motor_calibration.py

#Launch with the proper parameters
roslaunch outdoor_waypoint_nav gribot_start.launch
