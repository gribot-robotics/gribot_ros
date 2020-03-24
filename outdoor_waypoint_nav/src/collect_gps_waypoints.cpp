#include <ros/ros.h>
#include <ros/package.h>
#include <utility>
#include <fstream>
#include <iostream>
#include <sensor_msgs/NavSatFix.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/Joy.h>
#include <ros/duration.h>
#include <ros/time.h>
#include <math.h>
#include "std_msgs/String.h"

bool collect_request = false;
bool continue_collection = true;
double lati_point=0, longi_point=0, lati_last=0, longi_last=0;
double min_coord_change = 10 * pow(10,-6);
std::string end_button_sym, collect_button_sym;
// int end_button_num = 0, collect_button_num = 0;
std::string collect_key_num = "3", end_key_num = "4";

// void joy_CB(const sensor_msgs::Joy joy_msg)
// {
// 	if(joy_msg.buttons[collect_button_num]==1)
// 	{
// 		collect_request = true;
// 	}
// 	else
// 	{
// 		collect_request = false;
// 	}

// 	if(joy_msg.buttons[end_button_num]==1)
// 	{
// 		continue_collection = false;
// 	}
// }

void key_CB( std_msgs::String key_msg )
{
	// ROS_INFO_STREAM( key_msg.data );

	if (key_msg.data != "None" && key_msg.data != "")
	{
		int key_ascii = std::stoi( key_msg.data );
		char ascii = static_cast<char>( key_ascii );
		std::string key_str( 1, ascii );

		if ( key_str == collect_key_num )
		{
			collect_request = true;
		}
		else
		{
			collect_request = false;
		}

		if( key_str == end_key_num )
		{
			continue_collection = false;
		}
	}

}

void filtered_gps_CB(const sensor_msgs::NavSatFix gps_msg)
{
		lati_point = gps_msg.latitude;
		longi_point = gps_msg.longitude;
}

int main(int argc, char** argv)
{
	//Initialize variables
		int numWaypoints = 0;
		std::string path_local;

    // Initialize node and time
		ros::init(argc, argv, "collect_gps_waypoints"); //initiate node called collect_gps_waypoints
		ros::NodeHandle n;
		ros::Time::init();
		ros::Time time_last;
		ros::Time time_current;
		ros::Duration duration_min(1);

	// Get button numbers to collect waypoints and end collection
		ros::param::get("/outdoor_waypoint_nav/collect_key_num", collect_key_num);
		ros::param::get("/outdoor_waypoint_nav/end_key_num", end_key_num);

    //Initiate subscribers
		// ros::Subscriber sub_joy = n.subscribe("/joy_teleop/joy", 100, joy_CB);
		ros::Subscriber sub_key = n.subscribe("/key", 100, key_CB);
		// TODO: Check the topic
		ros::Subscriber sub_gps = n.subscribe("/outdoor_waypoint_nav/gps/filtered", 100, filtered_gps_CB);
		ROS_INFO("Initiated collect_gps_waypoints node");

	// Initiate publisher to send end of node message
		ros::Publisher pubCollectionNodeEnded = n.advertise<std_msgs::Bool>("/outdoor_waypoint_nav/collection_status",100);

    //Read file path and create/open file
    	ros::param::get("/outdoor_waypoint_nav/coordinates_file", path_local);
		std::string path_abs =  ros::package::getPath("outdoor_waypoint_nav") + path_local;	
		std::ofstream coordFile (path_abs.c_str());
		ROS_INFO("Saving coordinates to: %s", path_abs.c_str());
		
	// Give instructions:
		// ros::param::get("/outdoor_waypoint_nav/collect_button_sym", collect_button_sym);
		// ros::param::get("/outdoor_waypoint_nav/end_button_sym", end_button_sym);
		std::cout << std::endl;
		std::cout << "Press " << collect_key_num.c_str() << " button to collect and store waypoint." << std::endl;
		std::cout << "Press " << end_key_num.c_str() << " button to end waypoint collection." << std::endl;
		std::cout << std::endl;

	if(coordFile.is_open())
	{
		while(continue_collection && ros::ok())
		{
			ros::spinOnce();

			if(collect_request == true)
			{
				numWaypoints++;
				ROS_INFO("You have collected another waypoint!");
				ROS_INFO("Waypoint number: %i", numWaypoints);
				ROS_INFO( "Latitude: %f", lati_point );
				ROS_INFO( "Longitude: %f", longi_point );
				//write waypoint
				ROS_INFO("Press %s button to collect and store another waypoint.", collect_key_num.c_str());
				ROS_INFO("Press %s button to end waypoint collection.", end_key_num.c_str());

				std::cout << std::endl;
				
				coordFile << std::fixed << std::setprecision(8) << lati_point << " " << longi_point << std::endl;
				collect_request = false;
			}
		}
	
		coordFile.close();
		ROS_INFO("End request registered.");
	}
	else
	{
		ROS_ERROR("Unable to open file.");
		ROS_INFO("Exiting..");
	}

	ROS_INFO("Closed waypoint file, you have collected %d waypoints.", numWaypoints);
	ROS_INFO("Ending node...");

	// Notify joy_launch_control that calibration is complete
    std_msgs::Bool node_ended;
    node_ended.data = true;
    pubCollectionNodeEnded.publish(node_ended);

	ros::shutdown();
	return 0;
}