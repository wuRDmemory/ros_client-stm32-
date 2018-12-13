#include "includes.h"
#include "std_msgs/String.h"

void msgCallBack(const std_msgs::String& msg);
std_msgs::String msg1;

//-------------ROS变量----------------
ros::NodeHandle nh;
ros::Subscriber<std_msgs::String> sub("stm_subscribe", msgCallBack);
ros::Publisher pub("stm_publish",&msg1);
int i=0;


void msgCallBack(const std_msgs::String& msg)
{   
    char hello[13];
    sprintf(hello, "%d", i++);    
    msg1.data = hello;
    pub.publish(&msg1);
    i++;
}

int main(void)
{   
    // 初始化阶段
    System_Init();
    delay_ms(1000);
    Bsp_Configuration();
    App_Init();
    // 正式进行ros连接
	nh.initNode();
	nh.advertise(pub);
    nh.subscribe(sub);
    char hello[13] = "hello world!";
    while(1)
    {
        // msg.data = hello;
        // pub.publish(&msg);
        nh.spinOnce();
        delay_ms(10);
    }
}

