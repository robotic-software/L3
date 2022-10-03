#include "ros/ros.h"
#include <iostream>
#include "ros_service/service.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char **argv) {

	ros::init(argc, argv, "service_client");
	ros::NodeHandle n;
	ros::Rate loop_rate(10);
	ros::ServiceClient client =
	n.serviceClient<ros_service::service>("service");
	while (ros::ok()) {
		ros_service::service srv;
		std::stringstream ss;
		ss << "Sending from Here";
		srv.request.in = ss.str();
		if (client.call(srv)) {
			cout << "From Client: ["<<	srv.request.in << "], Server says [" << srv.response.out << "]" << endl;
		}
		else {
			ROS_ERROR("Failed to call service");
			return 1;
		}
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
