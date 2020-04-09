#include <eigen_conversions/eigen_msg.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Eigen/Dense"
#include "ros/ros.h"
#include "std_msgs/String.h"

#include "ekf/FusionEKF.h"
#include "ekf/measurement_package.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Rate loop_rate(10);
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  vector<MeasurementPackage> measurement_pack_list;
  string in_file_name_ = "/home/badal/car/src/ekf/Data/obj_pose-laser-radar-synthetic-input.txt";
  ifstream in_file(in_file_name_.c_str(), std::ifstream::in);

  if (!in_file.is_open())
  {
    cout << "cannot open the file " << in_file_name_ << endl;
  }
  string line;
  while (ros::ok())
  {
    while (getline(in_file, line))
    {
      std_msgs::String msg;
      std::stringstream ss;
      ss << "hello world ";
      msg.data = ss.str();
      ROS_INFO("%s", line);
      MeasurementPackage meas_package;
      istringstream iss(line);
      string sensor_type_;
      iss >> sensor_type_;
      int64_t timestamp;
      if (sensor_type_.compare("L") == 0)
      {
        meas_package.sensor_type_ = MeasurementPackage::LASER;
        meas_package.raw_measurements_ = VectorXd(2);
        float x;
        float y;
        iss >> x;
        iss >> y;
        meas_package.raw_measurements_ << x, y;
        iss >> timestamp;
        meas_package.time_stamp_ = timestamp;
        measurement_pack_list.push_back(meas_package);
      }
      else if (sensor_type_.compare("R") == 0)
      {
        meas_package.sensor_type_ = MeasurementPackage::RADAR;
        meas_package.raw_measurements_ = VectorXd(3);
        float x;
        float y;
        float z;
        iss >> x;
        iss >> y;
        iss >> z;
        meas_package.raw_measurements_ << x, y, z;
        iss >> timestamp;
        meas_package.time_stamp_ = timestamp;
        measurement_pack_list.push_back(meas_package);
      }
    }
  }
}
