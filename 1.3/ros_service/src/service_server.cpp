#include "ros/ros.h"
#include "ros_service/service.h"
#include <iostream>
#include <sstream>


using namespace std;

bool service_callback( ros_service::service::Request &req, ros_service::service::Response &res) {


	res.out = "Received Here";
	ROS_INFO( "From Client [%s], Server says [%s]", req.in.c_str(), res.out.c_str());
	
	return true;
}




int main(int argc, char **argv) {
	ros::init(argc, argv, "service_server");
	ros::NodeHandle n;
	ros::ServiceServer service = n.advertiseService("service", service_callback);
	ROS_INFO("Ready to receive from client.");
	ros::spin();

	return 0;
}
