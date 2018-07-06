/*!
 * \brief Teleoperation node for Gribot
 *
 * The goal of this noe is to translate
 * teleoperation commands comming from a
 * joystick and send them to Gribot
 * in order to allow to pilot Gribot
 * with a joystick.
*/

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <iostream>

using namespace std;


/*! */

class TeleopJoy
{
   public:
      TeleopJoy();

   private:
      void callBack(const sensor_msgs::Joy::ConstPtr& joy);
      ros::NodeHandle n;
      ros::Publisher  pub;		// Publisher of cmd_vel 
      ros::Subscriber sub;		// Subscriber to joy sensor 
      int i_velLinear, i_velAngular;
};


/*! The constructor */

TeleopJoy::TeleopJoy()
{
   n.param("axis_linear", i_velLinear, i_velLinear);	// From parameter server 
   n.param("axix_angular", i_velAngular, i_velAngular); // From parameter server 
   pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1); // Published 
   sub = n.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopJoy::callBack, this); // Subscribed 
}


/*! Called each time a message is received */

void TeleopJoy::callBack(const sensor_msgs::Joy::ConstPtr& joy)
{
   geometry_msgs::Twist vel;			// Used to publish data 
   vel.angular.z = -2*joy->axes[i_velAngular];  // Factor 2 required to increase angular speed, négative sign see below 
   vel.linear.x = -1*joy->axes[i_velLinear];    // Negative sign required to correct joytisk inversion
   pub.publish(vel);				// The topic is published 
}


int main(int argc, char **argv)
{

  ROS_INFO("Starting teleopjoy"); 
   ros::init(argc, argv, "teleopjoy");
   TeleopJoy teleop_gribot;
   ros::spin();
   return 0;
}
