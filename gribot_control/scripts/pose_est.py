#!/usr/bin/env python
import rospy
import numpy as np
import math
import csv
import matplotlib.pyplot as plt
import sys
from std_msgs.msg import Int64
from nav_msgs.msg import Odometry
import message_filters

_left_ticks = 0
_right_ticks = 0

_prev_left_ticks = 0
_prev_right_ticks = 0

_base_width = 0
_ticks_per_meter = 0

# The callback processing the pairs of numbers that arrived at approximately the same time
def callback_encoders(left_ticks, right_ticks):

    global _left_ticks
    global _right_ticks

    _left_ticks = left_ticks.data
    _right_ticks = right_ticks.data

    rospy.loginfo(rospy.get_caller_id() + "left encoder %s", _left_ticks)
    rospy.loginfo(rospy.get_caller_id() + "right encoder %s", _right_ticks)

def odom():

    rospy.init_node('pose_estimation', anonymous=True)

    pub_odom = rospy.Publisher('odom', String, queue_size=10)
    left_ticks_sub = message_filters.Subscriber('encoders/left_wheel', Int64)
    right_ticks_sub = message_filters.Subscriber('encoders/right_wheel', Int64)

    ts = message_filters.ApproximateTimeSynchronizer([left_ticks_sub, right_ticks_sub], 10, 0.1, allow_headerless=True)
    ts.registerCallback(callback_encoders)

    rospy.set_param("base_width", 0.25)
    rospy.set_param("ticks_per_meter", 100)
    rospy.set_param("fixed_frecuency", 40)

    global _base_width
    global _ticks_per_meter

    # Get parameters base_width, ticks_per_meter, fixed_frecuency
    _base_width = rospy.get_param("base_width")
    _ticks_per_meter = rospy.get_param("ticks_per_meter")
    fixed_frecuency = rospy.get_param("fixed_frecuency")

    rate = rospy.Rate(fixed_frecuency) # hz

    while not rospy.is_shutdown():
        compute_odom()
        rate.sleep()

def compute_odom():

    # //extract the wheel velocities from the tick signals count
    # The data range of the encoder is [0 - 16777216]
    # Value wrapping between the min and max in the case of overflow / underflow.
    delta_tick_left = _left_ticks - _prev_left_ticks;
    delta_tick_right = _right_ticks - _prev_right_ticks;

    # distance_left_wheel (resp. distance_right_wheel) denotes the distance traveled by the left (resp. right) wheel as reported by its encoder since the last update
    distance_right_wheel = delta_tick_left / ticks_per_meter
    distance_left_wheel = delta_tick_right / ticks_per_meter

    # The heading increment in radians is given by (this approximation is only valid when both
    # distance_right_wheel and distance_left_wheel are small):
    heading_increment = (distance_right_wheel - distance_left_wheel) / _base_width

    x_increment = cos(heading_increment) * (distance_left_wheel + distance_right_wheel) / 2
    y_increment = -sin(heading_increment) * (distance_left_wheel + distance_right_wheel) / 2

    x_fixed_increment = cos(heading_increment) * x_increment - sin(heading_increment) * y_increment

    y_fixed_increment = sin(heading_increment) * x_increment + cos(heading_increment) * y_increment

    current_time = rospy.Time.now()
    double DistancePerCount = (3.14159265 * 0.13) / 2626;
    double lengthBetweenTwoWheels = 0.25;

    # //extract the wheel velocities from the tick signals count
    # The data range of the encoder is [0 - 16777216], with the value wrapping between the min and max in the case of overflow / underflow.
    delta_tick_left = _left_ticks - _prev_left_ticks;
    delta_tick_right = _right_ticks - _prev_right_ticks;

    omega_left = (delta_tick_left * DistancePerCount) / (current_time - last_time).toSec();
    omega_right = (delta_tick_right * DistancePerCount) / (current_time - last_time).toSec();

    v_left = omega_left * 0.065; # //radius
    v_right = omega_right * 0.065;

    vx = ((v_right + v_left) / 2)*10;
    vy = 0;
    vth = ((v_right - v_left) / lengthBetweenTwoWheels)*10;

    double dt = (current_time - last_time).toSec();
    double delta_x = (vx * cos(th)) * dt;
    double delta_y = (vx * sin(th)) * dt;
    double delta_th = vth * dt;

    x += delta_x;
    y += delta_y;
    th += delta_th;

    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    # //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    # //Odometry message
    odom_msg = Odometry()
    odom.header.stamp = current_time
    odom_msg.header.frame_id = "odom"

    # //set the position
    odom_msg.pose.pose.position.x = x                                                                              
    odom_msg.pose.pose.position.y = y
    odom_msg.pose.pose.position.z = 0.0
    odom_msg.pose.pose.orientation = odom_quat

     # //set the velocity
    odom_msg.child_frame_id = "base_link"
    odom_msg.twist.twist.linear.x = vx
    odom_msg.twist.twist.linear.y = vy
    odom_msg.twist.twist.angular.z = vth

    # //publish the message
    pub_odom.publish(odom_msg)
    _prev_left_ticks = _left_ticks
    _prev_right_ticks = _right_ticks

    last_time = current_time

if __name__ == '__main__':
    odom()