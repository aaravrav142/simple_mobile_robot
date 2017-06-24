//
// Created by shipei on 6/23/17.
//

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <RobotCommander.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "circle_move"); //name this node
    ros::NodeHandle nh;
    ros::Publisher twist_publisher = nh.advertise<geometry_msgs::Twist>("path_vel", 10);
    double diameter = 3;
    double speed = 1.0;
    if (argc >= 1) {
        diameter = atof(argv[1]);
    } else {
        std::cout << "Wrong number of parameters!" << std::endl
                  << "Usage: rosrun simple_mobile_robot circle_move [diameter]" << std::endl
                  << "      [diameter] is the diameter of the circular path in meter, if you want the robot to move counter clockwise, specify a negative number" << std::endl
                  << "Example: rosrun simple_mobile_robot circle_move 5 # run a clockwise circular path of diameter = 5" << std::endl;
        return 0;
    }
    nh.param("MAX_SPEED", speed, speed); // get speed from param server
    double radius = (diameter / 2) * 1.05; // a small compensation
    geometry_msgs::Twist twist;
    twist.linear.x = speed;
    twist.angular.z = speed / radius; // w = v/r
    ROS_INFO("start circular move");
    while (ros::ok()) {
        twist_publisher.publish(twist);
        ros::Duration(0.05).sleep();
    }
    return 0;
};
