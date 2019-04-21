#ifndef __SHOWPOINTS_H__
#define __SHOWPOINTS_H__

#include <geometry_msgs/Point.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/Point32.h>
#include <ros/ros.h>
#include <string>
#include <tf/transform_broadcaster.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

using namespace std;

class ShowPoints {
 public:
  ShowPoints();
  ~ShowPoints();
  /**
   *@brief Optional colors : 'r'--red, 'g'--green, 'b'--blue, 
   * 'p'--,purple 'w'--white, 'y'--yellow, default: blue
   *@brief color_a: transparency [0-1]
   */ 
  void RunShowPoints(string str_namespace,
      const std::vector<geometry_msgs::Point32>& points_sim,
      char color = 'b', double sizex = 0.5, double sizey = 0.5, double color_a = 1.0);

 private:
  /***variable***/
  ros::Publisher marker_points_pub_;

  /***function***/
  void CreateMarkers(visualization_msgs::MarkerArray& markers_to_show,
                     const std::vector<geometry_msgs::Point32>& points_sim,
                     const char& color, const double& sizex,
                     const double& sizey, const double& color_a,const string& str_namespace);
  void Publish(const visualization_msgs::MarkerArray& markers_to_show);
};

#endif
