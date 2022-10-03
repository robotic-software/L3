//
#include "ros/ros.h" //include ros header file
#include "std_msgs/Int32.h"  //header file of the message to publish
#include <iostream>
#include <ros_topic_custom/demo.h>

int main(int argc, char **argv) {

	//
	ros::init(argc, argv,"ros_topic_publisher");
	ros::NodeHandle nh;
	//Publish an integer on topic called number
	ros::Publisher topic_pub =
	nh.advertise<ros_topic_custom::demo>("/number_custom", 10);
	
	ros::Rate rate(10); //Rate
	int count = 0;


	ros_topic_custom::demo cm;
	cm.name = "data_name";
	cm.data = 0;
	

	while (ros::ok() /* true */) {

		cm.data = count++;
		ROS_INFO("%d",cm.data); //printf
		topic_pub.publish(cm);
		rate.sleep();

	}
	return 0;
}
