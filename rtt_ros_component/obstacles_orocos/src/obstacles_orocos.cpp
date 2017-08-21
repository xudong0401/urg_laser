#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/String.h>
#include <rtt/TaskContext.hpp>
#include <rtt/Component.hpp>
#include <rtt/Port.hpp>

using namespace RTT;

class SubscribeAndPublish : public RTT::TaskContext
{

  private:
    InputPort<sensor_msgs::LaserScan> inport;
    OutputPort<std_msgs::String> outport;

    std_msgs::String ss1;
    std_msgs::String ss2;
    std_msgs::String test_order; //publish message
    float mix_ranges;
    float my_distance;
    float stop_distance;

  public:
    SubscribeAndPublish(const std::string &name) : TaskContext(name), 
                                                   stop_distance(4.00)
    {
        ss1.data = "stop";
        ss2.data = "run";
        this->ports()->addEventPort("sub_",inport).doc("Input Port that raises an event.");//输入
        this->ports()->addPort("pub_",outport).doc("Output Port, here write our data to.");//输出
    }

  private:
    void updateHook()
    {
        sensor_msgs::LaserScan my_scan;
        if (NewData == inport.read(my_scan))
        {
            static bool uSendedStopCmd = false;
            for (int i = 0; i < my_scan.ranges.size(); i++)
            {
                mix_ranges = mix_ranges + my_scan.ranges[i];
            }
            my_distance = mix_ranges / 5;
            

            if (my_distance <= stop_distance) //stop
            {
                test_order = ss1;

                if (uSendedStopCmd == true)
                {
                }
                else
                {
                    //ROS_INFO("test_order is : %s", test_order.data.c_str());
                    //pub_.publish(test_order);
                    outport.write(test_order);//hard real-time
                    uSendedStopCmd = true;
                }
            }
            else //run
            {
                test_order = ss2;
                uSendedStopCmd = false;
            }

            mix_ranges = 0;
        }
    }
};


ORO_CREATE_COMPONENT(SubscribeAndPublish)