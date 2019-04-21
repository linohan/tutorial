#ifndef CURVE_H
#define CURVE_H
#include <cmath>
#include <iostream>
#include <vector>
#include "site.h"
#include "toolbox.h"

using namespace std;
class Curve {
 public:
  Curve() { InputPoints(); }
  virtual bool GenerateCurve() {}
  virtual bool InputPoints() {
    points.push_back(Site(0, 1));
    points.push_back(Site(0, 2));
    points.push_back(Site(1, 3));
    points.push_back(Site(2, 4));
    points.push_back(Site(3, 6));
    points.push_back(Site(6, 1));
    points.push_back(Site(7, 1));
  }

 protected:
  WriteToFile wf;
  bool Write2File(SiteVec in_points, SiteVec new_points) {
    wf.Sitevec2File(in_points, "../data/input.csv");
    wf.Sitevec2File(new_points, "../data/result.csv");
    return true;
  }
  SiteVec points;
};

class BSpline : public Curve {
 public:
  BSpline() = default;
  ~BSpline() = default;

 public:
  bool GenerateCurveApproximation() {
    SiteVec newPnts;
    // points.push_back(Site(6, 1));

    int pntLen = points.size();
    // 闭合曲线
    if (points.front() == points.back()) {
      for (int n = 0; n < pntLen; n++) {
        if (n <= pntLen - 4) {
          for (double t = 0.0; t <= 1.0; t += 0.1) {
            double a1 = pow((1 - t), 3) / 6;
            double a2 = (3 * pow(t, 3) - 6 * pow(t, 2) + 4) / 6;
            double a3 = (-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) / 6;
            double a4 = pow(t, 3) / 6;

            double x = a1 * points[n].x + a2 * points[n + 1].x +
                       a3 * points[n + 2].x + a4 * points[n + 3].x;
            double y = a1 * points[n].y + a2 * points[n + 1].y +
                       a3 * points[n + 2].y + a4 * points[n + 3].y;
            Site site(x, y);
            newPnts.push_back(site);
          }
        } else if (n == pntLen - 3) {
          for (double t = 0.0; t <= 1.0; t += 0.1) {
            double a1 = pow((1 - t), 3) / 6;
            double a2 = (3 * pow(t, 3) - 6 * pow(t, 2) + 4) / 6;
            double a3 = (-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) / 6;
            double a4 = pow(t, 3) / 6;

            double x = a1 * points[n].x + a2 * points[n + 1].x +
                       a3 * points[n + 2].x + a4 * points[0].x;
            double y = a1 * points[n].y + a2 * points[n + 1].y +
                       a3 * points[n + 2].y + a4 * points[0].y;
            Site site(x, y);
            newPnts.push_back(site);
          }
        } else if (n == pntLen - 2) {
          for (double t = 0.0; t <= 1.0; t += 0.1) {
            double a1 = pow((1 - t), 3) / 6;
            double a2 = (3 * pow(t, 3) - 6 * pow(t, 2) + 4) / 6;
            double a3 = (-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) / 6;
            double a4 = pow(t, 3) / 6;

            double x = a1 * points[n].x + a2 * points[n + 1].x +
                       a3 * points[0].x + a4 * points[1].x;
            double y = a1 * points[n].y + a2 * points[n + 1].y +
                       a3 * points[0].y + a4 * points[1].y;
            Site site(x, y);
            newPnts.push_back(site);
          }
        } else if (n == pntLen - 1) {
          for (double t = 0.0; t <= 1.0; t += 0.1) {
            double a1 = pow((1 - t), 3) / 6;
            double a2 = (3 * pow(t, 3) - 6 * pow(t, 2) + 4) / 6;
            double a3 = (-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) / 6;
            double a4 = pow(t, 3) / 6;

            double x = a1 * points[n].x + a2 * points[0].x + a3 * points[1].x +
                       a4 * points[2].x;
            double y = a1 * points[n].y + a2 * points[0].y + a3 * points[1].y +
                       a4 * points[2].y;
            Site site(x, y);
            newPnts.push_back(site);
          }
        }
      }
      // 不闭合
    } else {
      newPnts.push_back(points.front());
      for (int n = 0; n < pntLen; n++) {
        if (n <= pntLen - 4) {
          for (double t = 0.0; t <= 1.0; t += 0.1) {
            double a1 = pow((1 - t), 3) / 6;
            double a2 = (3 * pow(t, 3) - 6 * pow(t, 2) + 4) / 6;
            double a3 = (-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) / 6;
            double a4 = pow(t, 3) / 6;

            double x = a1 * points[n].x + a2 * points[n + 1].x +
                       a3 * points[n + 2].x + a4 * points[n + 3].x;
            double y = a1 * points[n].y + a2 * points[n + 1].y +
                       a3 * points[n + 2].y + a4 * points[n + 3].y;
            Site site(x, y);
            newPnts.push_back(site);
          }
        }
      }
      newPnts.push_back(points.back());
    }
    Write2File(points, newPnts);
  }

  bool GenerateCurveInterpretation() {}
  };
#endif