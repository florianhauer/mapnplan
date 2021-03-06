#include "ros/ros.h"
#include <tf/transform_listener.h>
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/PointCloud2.h"
#include "laser_geometry/laser_geometry.h"

laser_geometry::LaserProjection projector_;
ros::Publisher cloud_pub;

void scanCallback (const sensor_msgs::LaserScan::ConstPtr& scan_in)
{
	/*tf::TransformListener listener_;
  if(!listener_.waitForTransform(
        scan_in->header.frame_id,
        "/base_link",
        scan_in->header.stamp + ros::Duration().fromSec(scan_in->ranges.size()*scan_in->time_increment),
        ros::Duration(1.0))){
     return;
  }

  sensor_msgs::PointCloud2 cloud;
  projector_.transformLaserScanToPointCloud("/base_link",*scan_in,
          cloud,listener_);

  // Do something with cloud.
	cloud_pub.publish(cloud);*/
	sensor_msgs::PointCloud2 cloud;
  projector_.projectLaser(*scan_in, cloud);
	cloud_pub.publish(cloud);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "laserToPointCloud");
  ros::NodeHandle n;
  ros::Subscriber subWaypoint = n.subscribe("base_scan", 1000, scanCallback);
	cloud_pub = n.advertise<sensor_msgs::PointCloud2>("cloud_in", 1000);
  ros::spin();
  return 0;
}
