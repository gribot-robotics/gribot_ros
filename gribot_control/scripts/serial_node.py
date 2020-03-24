#!/usr/bin/env python
import rospy
import math
import serial
from std_msgs.msg import Float32

ser_keya_1 = serial.Serial()
ser_keya_2 = serial.Serial()

speed_limit = 999

# Send serial commands to the Chinese motor controller
def callbackLWheel(data):
    global ser_keya_2
    v = map( data.data * 100, 0, 150, 0, 1000 )

    if v > speed_limit:
        v = speed_limit
    # elif v < 0:
    #     v = 0

    cmd = "!M {0}\r".format(v)

    ser_keya_2.write(cmd.encode())
    rospy.loginfo(cmd)

    # try:
    #     ser_keya_2.write(cmd.encode())
    # except Exception as e:
    #     # raise e
    #     ser_keya_2.reset_output_buffer()


# Send serial commands to the Chinese motor controller
def callbackRWheel(data):
    global ser_keya_1
    v = map( data.data * 100, 0, 150, 0, 1000 )

    if v > speed_limit:
        v = speed_limit

    cmd = "!M {0}\r".format(v)
    ser_keya_1.write(cmd.encode())
    rospy.loginfo(cmd)

def map( x, in_min, in_max, out_min, out_max ):
    return int(math.floor( ( x - in_min) * ( out_max - out_min ) / ( in_max - in_min ) + out_min ))
    
def listener():
    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('serial_node', anonymous=True)

    ser_keya_1.baudrate = 115200
    ser_keya_1.port = '/dev/ttyUSB1'
    ser_keya_1.timeout = 1
    ser_keya_1.write_timeout = 1

    ser_keya_2.baudrate = 115200
    # ser_keya_2.port = '/dev/ttyACM0'
    # ser_keya_2.port = '/dev/ttyACM1'
    ser_keya_2.port = '/dev/ttyUSB0'
    ser_keya_2.timeout = 1
    ser_keya_2.write_timeout = 1

    ser_keya_1.open()

    if ser_keya_1.is_open == False:
        print( "Error while opening the keya serial port" )
        return

    ser_keya_2.open()

    if ser_keya_2.is_open == False:
        print( "Error while opening the arduino serial port" )
        return

    rospy.Subscriber("lwheel_vtarget", Float32, callbackLWheel)
    rospy.Subscriber("rwheel_vtarget", Float32, callbackRWheel)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

    ser_keya_1.reset_output_buffer()
    ser_keya_1.close()

    ser_keya_2.reset_output_buffer()
    ser_keya_2.close()

if __name__ == '__main__':
    listener()