#include <ros_node/ros_node_node.h>
//#include <string>
#include <vector>
#include <fstream>  //文件流库函数
using namespace std;
using namespace Ros_node;
ros_node::ros_node()
{
    nh_private_ = ros::NodeHandle("~");
    outfile.open("/home/cjn/making_laser_data_sets/src/ros_node/test.dat", ios::app);
    if(!outfile.is_open ())
            cout << "Open file failure" << endl;
    laserscan_sub_ = nh.subscribe("/scan", 50, &ros_node::laserscan_get, this);
    work_execute_ = boost::thread(boost::bind(&ros_node::execute, this));
}
ros_node::~ros_node()
{
    work_execute_.join();
}
void ros_node::execute(void)
{
    ros::Rate loop_rate(50);
    while(ros::ok())
    {
//        cout << "hello,world!" << endl;
        loop_rate.sleep();
    }
}
void ros_node::laserscan_get(const sensor_msgs::LaserScan& laser_data)
{
    ++num;
    outfile << num << " ";
    for(int j = 0; j < laser_data.ranges.size(); ++j)
    {
        if(std::isfinite(laser_data.ranges[j]) && laser_data.ranges[j] >= 0)
        {
            float angle = laser_data.angle_min + j*laser_data.angle_increment;
            float X= laser_data.ranges[j]*cos(angle);
            float Y= laser_data.ranges[j]*sin(angle);
            outfile << X << " " << Y << " " << 0 << " ";
        }
    }
    outfile << endl;
    cout << "laserscan.size()" << laser_data.ranges.size() << endl;
    if(num > 1000)
      outfile.close();
//    cout << "scan data receive!" << endl;
}
int main (int argc, char **argv)
{
    ros::init(argc, argv, "ros_node_node");

    boost::shared_ptr<ros_node> work_interface_ (new ros_node);
    ros::spin();
    return 0;
}


















