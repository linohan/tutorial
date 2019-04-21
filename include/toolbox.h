#ifndef TOOLBOX_H
#define TOOLBOX_H
#include <cmath>
#include <fstream>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <vector>
#include "site.h"

using namespace std;
using namespace cv;
class Plot {
 public:
  Plot() {}
  ~Plot() {}
  void PlotVec(int height, int weight, SiteVec site_to_show) {
    cv::namedWindow("image", 0);
    cv::Mat image(height, weight, CV_8UC3, cv::Scalar(255, 255, 255));
    for (auto it = site_to_show.begin(); it != site_to_show.end(); it++) {
      cv::Point center(it->x, -it->y + height);
      double radius = 0.05;
      circle(image, center, radius, Scalar(0, 0, 255), -1);
    }
    // cout<<image<<endl;
    cv::imshow("image", image);
    cv::waitKey(0);
  }
};

class WriteToFile {
 public:
  void Sitevec2File(const SiteVec &sites_to_save,
                    const std::string &output_path) {
    std::ofstream output_file;
    // string output_path = "../data/test.csv";
    // std::ofstream output_file(output_path + "/" + "out_data");
    output_file.open(output_path.c_str(), std::ios::trunc);
    for (auto p : sites_to_save) {
      output_file << p.x << "," << p.y << "," << p.angle << std::endl;
    }
    output_file.close();
  }
};

class ReadFile {
 public:
  bool ReadCSV(const std::string &input_path,
               vector<vector<double>> &value_list) {
    std::ifstream infile(input_path);
    // string input_path = "/home/idriver/test.csv";
    // printf("Open data : %s\n", data_path.c_str());
    // infile.open();
    if (!infile) {
      std::cout << "can not open the file!" << std::endl;
      return false;
    }
    std::string temp_line;
    while (getline(infile, temp_line)) {
      std::stringstream s_line(temp_line);
      std::string temp_value;
      vector<double> temp_v;
      while (getline(s_line, temp_value, ',')) {
        std::stringstream s_value;
        double temp;
        s_value << temp_value;
        s_value >> temp;
        temp_v.push_back(temp);
      }
      value_list.push_back(temp_v);
    }
    infile.close();
    return true;
  }
};

static string num2str(double i) {
  stringstream ss;
  ss << i;
  return ss.str();
}

static double str2num(string s) {
  double num;
  stringstream ss(s);
  ss >> num;
  return num;
}

#endif