#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <actionlib/server/simple_action_server.h>
#include "ros_action/demoAction.h"
#include <iostream>
#include <sstream>

class action_class  {

	private:
  	ros::NodeHandle nh_;
  	// NodeHandle instance must be created before this line. Otherwise strange error may occur.
  	actionlib::SimpleActionServer<ros_action::demoAction> as; 
  	// create messages that are used to published feedback/result
		ros_action::demoFeedback feedback;
		ros_action::demoResult result;

  	std::string action_name;
  	int goal;
  	int progress;

	public:
		action_class(std::string name) :
  	  as(nh_, name, boost::bind(&action_class::executeCB, this, _1), false),
  	  action_name(name) {
				as.registerPreemptCallback(boost::bind(&action_class::preemptCB, this));
				as.start();
  		}
	
			void preemptCB(){
				ROS_WARN("%s got preempted!", action_name.c_str());
				result.final_count = progress;
				as.setPreempted(result,"I got Preempted"); 
  		}
  
			void executeCB(const ros_action::demoGoalConstPtr &goal) {
				if(!as.isActive() || as.isPreemptRequested()) return;
				ros::Rate rate(1);
			
				ROS_INFO("%s is processing the goal %d", action_name.c_str(), goal->count);
			
				for(progress = 1 ; progress <= goal->count; progress++){
					//Check for ros
					if (!ros::ok()) {
						result.final_count = progress;
						as.setAborted(result,"I failed !");
						ROS_INFO("%s Shutting down",action_name.c_str());
						break;
					}
		
					if(!as.isActive() || as.isPreemptRequested()){
						return;
					}	

					if(goal->count <= progress) {
						ROS_INFO("%s Succeeded at getting to goal %d", action_name.c_str(), goal->count);
						result.final_count = progress;
						as.setSucceeded(result);
					}
					else {
						ROS_INFO("Setting to goal %d / %d",feedback.current_number,goal->count);
						feedback.current_number = progress;
						as.publishFeedback(feedback);
					}
					rate.sleep();
				}	
  		}
};

int main(int argc, char** argv)
{

  ros::init(argc, argv, "demo_action");
  ROS_INFO("Starting Demo Action Server");
  action_class demo_action_obj("demo_action");
  ros::spin();
  return 0;
}
