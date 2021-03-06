#include "ros/ros.h"
#include "std_msgs/String.h"
#include "limelight_vision_node/Limelight_Control.h"

#include <thread>
#include <string>
#include <mutex>

ros::NodeHandle* node;

int main(int argc, char **argv)
{
	/**
	 * The ros::init() function needs to see argc and argv so that it can perform
	 * any ROS arguments and name remapping that were provided at the command line.
	 * For programmatic remappings you can use a different version of init() which takes
	 * remappings directly, but for most command-line programs, passing argc and argv is
	 * the easiest way to do it.  The third argument to init() is the name of the node.
	 *
	 * You must call one of the versions of ros::init() before using any other
	 * part of the ROS system.
	 */
	ros::init(argc, argv, "blank_limelight_node");

	ros::NodeHandle n;

	node = &n;

	while(ros::ok())
	{
		static ros::Publisher limelight_control_pub = node->advertise<limelight_vision_node::Limelight_Control>("/LimelightControl", 5);

		limelight_vision_node::Limelight limelight;
		limelight.name = "limelight";
		limelight.pipeline = 1;

		limelight_vision_node::Limelight_Control limelight_control;
		limelight_control.limelights.push_back(limelight);

		limelight_control_pub.publish(limelight_control);

		ros::spinOnce();
	}
	return 0;
}