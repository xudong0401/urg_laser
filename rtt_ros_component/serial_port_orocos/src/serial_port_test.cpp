//rtt heahers

#include <rtt/TaskContext.hpp>
#include <rtt/Port.hpp>
#include <rtt/Component.hpp>

#include <ros/ros.h>
#include <std_msgs/String.h>

#include "protocal.h"
#include "crc16.h"
#include "serial.h"
#include <iostream>

using namespace RTT;
using namespace std;

//const int MAX_LENGTH = 1024;

class SerialPortTest : public RTT::TaskContext
{
  private:
    InputPort<std_msgs::String> inport;
    //OutputPort<>
    int fd_mb_serial;

  public:
    SerialPortTest(const std::string &name) : TaskContext(name)
    {
        this->ports()->addEventPort("sub_", inport).doc("Input Port that raises an event.");
        if (open_devide() < 0)
        {
            exit(-1);
        }
    }

    ~SerialPortTest(){};

  private:
    void updateHook()
    {
        std_msgs::String in_string;
        if (NewData == inport.read(in_string))
        {
            unsigned int data_len = 7;
            unsigned char data[data_len];
            //int len;
            data[0] = 0xaa;
            data[1] = 0x55;
            data[2] = 0x01;
            data[3] = 0x00;
            data[4] = 0x04;
            data[5] = 0x02;
            data[6] = 0x11;

            if (write(fd_mb_serial, data, data_len)!=data_len){
                printf("write error");
                tcflush(fd_mb_serial,TCOFLUSH);
            }else{
                return;
            }
        }
    }

    int open_devide()
    {
        std::string device_mode = "serial";
        this->addProperty("device_mode", device_mode).doc("device mode");

        if (device_mode == "serial")
        {
            std::string tty_name_l = "/dev/ttyUSB0";
            //nh.param("tty_name_l", tty_name_l, std::string("/dev/ttyUSB0"));
            this->addProperty("tty_name_1", tty_name_l);

            fd_mb_serial = open_serial(tty_name_l, 115200, 8, 'N', 2);
            if (fd_mb_serial < 0)
            {
                return -1;
            }
        }
        else
        {
            printf("failure: device mode unknown\n");
            return -1;
        }

        return 0;
    }

    bool startHook()
    {
        if (!inport.connected())
        {
            return false;
        }
        else
            return true;
    }
};

ORO_CREATE_COMPONENT(SerialPortTest)