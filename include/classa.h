#ifndef CLASSA
#define CLASSA
#include <time.h>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <set>
#include <tuple>
#include <vector>
#include "singleton.h"
#include "site.h"
#include "toolbox.h"

using namespace std;
typedef cv::Vec<uchar, 3> Vec3b;
class ClassA {
 public:
  ClassA();
  ~ClassA();
  static void Run(double &input_);
  void TestSingleton();
  void testDefaultParams(int a = 10, int b = 20, int c = 30);
  float decimal_process(float &data_to_process, int n);
  double grid_process(double &data_to_process, double t, int n);
  void TestOpenCV();
  void GetLocalTime();
  bool DeadRockoner(Site dr1, Site dr0, double length, double density,
                    double k0, double k1, double offset, SiteVec &update_sites);
  bool DeadRockoner2(Site dr1, Site dr0, double length, double density,
                    double k0, double k1, double offset, SiteVec &update_sites);
  bool RunDeadRockoner(int argc, char const *argv[]);
  bool UnitestDeadRockoner();

 private:
  int count;
};

struct PointGCCS {
  double xg;
  double yg;
  double angle;
};

#endif
