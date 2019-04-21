#ifndef SITE_H
#define SITE_H
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;
const double doubleMax = std::numeric_limits<double>::max();
const double EPSINON = 1e-5;

struct Site {
  Site() {
    x = 0;
    y = 0;
    angle = 0;
    xg = 0;
    yg = 0;
    velocity = 0;
    a = 0;
    t = 0;
    curvature = 0;
  }
  Site(const Site &s) {
    x = s.x;
    y = s.y;
    angle = s.angle;
    xg = s.xg;
    yg = s.yg;
    velocity = s.velocity;
    a = s.a;
    t = s.t;
    curvature = s.curvature;
  }
  Site(double xx, double yy) {
    x = xx;
    y = yy;
    angle = 0;
    xg = 0;
    yg = 0;
    velocity = 0;
    a = 0;
    t = 0;
    curvature = 0;
  }
  Site(double xx, double yy, double aa) {
    x = xx;
    y = yy;
    angle = aa;
    xg = 0;
    yg = 0;
    velocity = 0;
    a = 0;
    t = 0;
    curvature = 0;
  }
  ~Site() = default;

  double x;
  double y;
  double angle;
  double xg;
  double yg;
  double velocity;
  double a;
  double t;
  double curvature;

  void operator=(const Site &s) {
    x = s.x;
    y = s.y;
    angle = s.angle;
    xg = s.xg;
    yg = s.yg;
    velocity = s.velocity;
    a = s.a;
    t = s.t;
    curvature = s.curvature;
  }
  Site &operator+=(const Site &s) {
    x += s.x;
    y += s.y;
    xg += s.xg;
    yg += s.yg;
    return *this;
  }
  Site &operator-=(const Site &s) {
    x -= s.x;
    y -= s.y;
    xg -= s.xg;
    yg -= s.yg;
    return *this;
  }
  bool operator==(const Site &s) const {
    double precision = std::hypot((x - s.x), (y - s.y));
    return (precision < 1e-5) && (std::fabs(angle - s.angle) < 1e-5);
  }
  Site operator+(const Site &s) const { return Site(x + s.x, y + s.y); }
  Site operator-(const Site &s) const { return Site(x - s.x, y - s.y); }
  Site operator*(const double d) const { return Site(x * d, y * d); }
  Site operator/(const double d) const { return Site(x / d, y / d); }

  void set_g(double xx, double yy) {
    xg = xx;
    yg = yy;
  }

  void set_g(double xx, double yy, double aa) {
    xg = xx;
    yg = yy;
    angle = aa;
  }

  double inerangle() const { return std::atan2(y, x) * 180 / M_PI; }
  double mold() const { return std::hypot(x, y); }
  Site direction() const { return Site(x / this->mold(), y / this->mold()); }

  struct compare {
    bool operator()(const Site &s1, const Site &s2) const {
      if (std::fabs(s1.x - s2.x) < 1e-5)
        return s1.y < s2.y;
      else
        return s1.x < s2.x;
    }
  };

  struct hash_equal {
    bool operator()(const Site &ls, const Site &rs) const {
      double precision = std::hypot((ls.x - rs.x), (ls.y - rs.y));
      return (precision < 1e-5);
    }
  };

  struct hash_key {
    std::size_t operator()(const Site &s) const {
      std::hash<double> hash_fun;
      return size_t(hash_fun(s.x + s.y));
    }
  };
};

template <typename T>
class hyPoint {
 public:
  double operator()(const T &str) const { return hypot(str.x, str.y); }
};

struct MyPoint {
  MyPoint() : x(0), y(0), angle(0) {}
  MyPoint(double xi, double yi, double anglei) : x(xi), y(yi), angle(anglei) {}
  double x;
  double y;
  double angle;
  template <typename T, typename U>
  double operator()(const T &pt, const U &num) const {
    return hypot(pt.x - this->x, pt.y - this->y) + num;
  }
};

using SiteVec = vector<Site>;

#endif