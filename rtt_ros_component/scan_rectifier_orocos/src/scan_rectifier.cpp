//rtt heahers

#include <rtt/TaskContext.hpp>
#include <rtt/Port.hpp>
#include <rtt/Component.hpp>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>

using namespace RTT;
using namespace std;

class ScanRectifier : public RTT::TaskContext
{
  private:
    InputPort<sensor_msgs::LaserScan> inport;
    OutputPort<sensor_msgs::LaserScan> outport;

    bool range_enabled;
    double min_range;
    double max_range;
    bool interference_enabled;
    int interference_obs;
    double interference_factor;

  public:
    ScanRectifier(const std::string &name) : TaskContext(name), range_enabled(true),
                                             min_range(0.01), max_range(30.0), interference_enabled(true),
                                             interference_obs(1), interference_factor(1.2)
    {
        this->addProperty("range_enabled", range_enabled);
        this->addProperty("min_range", min_range);
        this->addProperty("max_range", max_range);
        this->addProperty("interference_enabled", interference_enabled);
        this->addProperty("interference_obs", interference_obs);
        this->addProperty("interference_factor", interference_factor);
        this->ports()->addEventPort("sub_", inport);
        this->ports()->addPort("pub_", outport);
    }

  private:
    void updateHook()
    {
        sensor_msgs::LaserScan my_scan;
        sensor_msgs::LaserScan output_scan;
        if (NewData == inport.read(my_scan))
        {
            
            output_scan = my_scan;

            if (range_enabled)
            {
                for (int i = 0; i < my_scan.ranges.size(); i++)
                {
                    if (output_scan.ranges[i] > max_range)
                    {
                        output_scan.ranges[i] = std::numeric_limits<float>::infinity();
                    }
                    if (output_scan.ranges[i] < min_range)
                    {
                        output_scan.ranges[i] = std::numeric_limits<float>::infinity();
                    }
                }
            }

            if (interference_enabled)
            {
                for (int i = interference_obs; i < my_scan.ranges.size() - interference_obs; i++)
                {
                    if (output_scan.ranges[i] * interference_factor < output_scan.ranges[i - 1] && output_scan.ranges[i] * interference_factor < output_scan.ranges[i + 1])
                    {
                        output_scan.ranges[i] = std::numeric_limits<float>::infinity();
                    }
                }
            }
        }
        outport.write(output_scan);
    }
};

ORO_CREATE_COMPONENT(ScanRectifier)