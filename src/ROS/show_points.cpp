#include "visualization/show_points.h"

using namespace std;

ShowPoints::ShowPoints() {
  ros::NodeHandle nh;
  marker_points_pub_ =
      nh.advertise<visualization_msgs::MarkerArray>("pathplan_show_points", 1);
}

ShowPoints::~ShowPoints() {}

void ShowPoints::RunShowPoints(string str_namespace,
    const std::vector<geometry_msgs::Point32>& points_to_show, 
    char color, double sizex, double sizey, double color_a) {
  if(points_to_show.empty()) return;
  visualization_msgs::MarkerArray markers;
  CreateMarkers(markers, points_to_show, color, sizex, sizey, color_a, str_namespace);
  Publish(markers);
  return;
}

void ShowPoints::CreateMarkers(
    visualization_msgs::MarkerArray& markers_to_show,
    const std::vector<geometry_msgs::Point32>& points_to_show, const char& color,
    const double& sizex, const double& sizey, const double& color_a,const string& str_namespace) {
  tf::Quaternion q;
  tf::Transform transform;
  visualization_msgs::Marker marker;
  int id = 0;
  for (auto it_point = points_to_show.begin(); it_point != points_to_show.end();
       ++it_point) {
    marker.header.frame_id = "/base_link";
    marker.header.stamp = ros::Time::now();
    marker.ns = str_namespace;
    marker.id = id;
    id++;
    marker.type = visualization_msgs::Marker::CUBE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = it_point->x;
    marker.pose.position.y = it_point->y;
    marker.pose.position.z = 0.0;

    //setRPY(double roll, double pitch, double yaw) (rad)
    q.setRPY(0, 0, it_point->z);
    transform.setRotation(q);
    marker.pose.orientation.x = q[0];
    marker.pose.orientation.y = q[1];
    marker.pose.orientation.z = q[2];
    marker.pose.orientation.w = q[3];

    marker.scale.x = sizex;
    marker.scale.y = sizey;
    marker.scale.z = 0.01;
    switch (color) {
      case 'r':
        marker.color.r = 1.0f;
        marker.color.g = 0.0f;
        marker.color.b = 0.0f;
        break;
      case 'g':
        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        break;         
      case 'b':
        marker.color.r = 0.0f;
        marker.color.g = 0.0f;
        marker.color.b = 1.0f;
        break;      
      case 'p':
        marker.color.r = 0.5f;
        marker.color.g = 0.0f;
        marker.color.b = 0.5f;
        break;
      case 'w':
        marker.color.r = 1.0f;
        marker.color.g = 1.0f;
        marker.color.b = 1.0f;
        break;
      case 'y':
        marker.color.r = 0.5f;
        marker.color.g = 0.5f;
        marker.color.b = 0.0f;
        break;                       
      default:
        marker.color.r = 0.0f;
        marker.color.g = 0.0f;
        marker.color.b = 1.0f;
        break;
    }
    marker.color.a = color_a;

    marker.lifetime = ros::Duration(2.0);
    markers_to_show.markers.push_back(marker);
  }
  return;
}

void ShowPoints::Publish(const visualization_msgs::MarkerArray& markers_to_show) {
  marker_points_pub_.publish(markers_to_show);
  return;
}
