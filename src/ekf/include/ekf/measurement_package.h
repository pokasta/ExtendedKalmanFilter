#ifndef MEASUREMENT_PACKAGE_H_
#define MEASUREMENT_PACKAGE_H_

#include "Eigen/Dense"

class MeasurementPackage
{
public:
  int64_t time_stamp_;
  enum SensorType
  {
    LASER,
    RADAR
  } sensor_type_;
  Eigen::VectorXd raw_measurements_;
};
#endif