#ifndef __ROS_H__
#define __ROS_H__

#include "ros/node_handle.h"
#include "Stm32Hardware.h"

namespace ros
{
	typedef ros::NodeHandle_<Stm32Hardware> NodeHandle;
}

#endif
