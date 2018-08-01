/*
Transform broadcaster node for Gribot robot

Copyright (C) 2018  Guy Corbaz

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

// @todo study ft broadcaster
// @todo implement broadcaster
int main(int argc, char** argv)
{
   ros::init(argc, argv, "tf_publisher");
   ros::NodeHandle n;

   ros::Rate r(100);

   tf::TransformBroadcaster broadcaster;


   ROS_INFO("Starting tf_publisher");


   while(n.ok())
   {
   }

   ROS_WARN("tf_publisher stopped")
   exit(0);
}

