/*
Joystick teleop node for Gribot robot

Copyright (C) 2018  Guy Corbaz

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

This node transforms tele operating commands comming from a joystick
into cmd_vel command
*/

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <iostream>

/*!
 * Handling tele operation commands
 */
class TeleopJoy
{
public:
  TeleopJoy();

private:
  void callBack(const sensor_msgs::Joy::ConstPtr& joy);
  ros::NodeHandle n_;
  ros::Publisher pub_;   // Publisher of cmd_vel
  ros::Subscriber sub_;  // Subscriber to joy sensor
  int i_velLinear_;
  int i_velAngular_;
};

/*!
 * Constructor
 */
TeleopJoy::TeleopJoy()
{
  n_.param("axis_linear", i_velLinear_, i_velLinear_);                           // From parameter server
  n_.param("axix_angular", i_velAngular_, i_velAngular_);                        // From parameter server
  pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);                      // Published
  sub_ = n_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopJoy::callBack, this);  // Subscribed
}

/*!
 * Called each time a message is received
 * @param joy the received message
 */
void TeleopJoy::callBack(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist vel;                      // Used to publish data
  vel.angular.z = 2 * joy->axes[i_velAngular_];  // Factor 2 required to increase angular speed
  vel.linear.x = joy->axes[i_velLinear_];
  pub_.publish(vel);  // The topic is published
}

/*!
 * Node initialization
 */
int main(int argc, char** argv)
{
  ROS_INFO("Starting teleopjoy");
  ros::init(argc, argv, "teleopjoy");
  TeleopJoy teleop_gribot;
  ros::spin();

  // We should never reach this, except if roscore stop.
  ROS_WARN("Stopping teleopjoy");
  return 0;
}
