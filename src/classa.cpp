#include "classa.h"
ClassA::ClassA() { count = 0; }
ClassA::~ClassA() {}  // cout<<"destructing ClassA"<<endl;}

void ClassA::Run(double& input_) {
  static double a = input_;
  // count ++;
  std::cout << "in class A:" << Singleton::GetNum() << std::endl;
  // input_ = 1;
  // cout<<"count: "<<count<<endl;
}

void ClassA::TestSingleton() {
  std::cout << "in class A:" << Singleton::GetNum() << std::endl;
}

void ClassA::testDefaultParams(int a, int b, int c) {
  cout << a << "," << b << "," << c << endl;
}

float ClassA::decimal_process(float& data_to_process, int n) {
  float t1;
  t1 = data_to_process - (int)data_to_process;
  t1 *= pow(10, n);
  if (fabs(t1 - (int)t1) > 0.5 - EPSINON) t1 += t1 / fabs(t1);
  t1 = (int)t1;
  t1 /= pow(10, n);
  t1 += (int)data_to_process;
  data_to_process = t1;
  return t1;
}

double ClassA::grid_process(double& data_to_process, double t, int n) {
  int inv = t * pow(10, n + 1);
  int i_a = (int)(data_to_process * pow(10, n + 1));
  int i_b = i_a / inv;
  if (fabs(i_a % inv) > (inv / 2 - 1e-5)) {
    i_b += i_b / fabs(i_b);
  }
  data_to_process = double(i_b * inv) / pow(10, n + 1);
  return data_to_process;
}

void ClassA::TestOpenCV() {
  int X = 1, _ = 0;
  vector<vector<int>> MAZE = {{1, 0, 1}, {0, 0, 0}};
  cv::Mat image(MAZE.size(), MAZE[0].size(), CV_8UC3,
                cv::Scalar(255, 255, 255));
  // cv::normalize(image, image, 0, 255, cv::NORM_MINMAX);
  for (int i = 0; i < image.rows; i++) {
    for (int j = 0; j < image.cols; j++) {
      if (MAZE[i][j] == 1) {
        image.at<Vec3b>(i, j)[0] = 0;
        image.at<Vec3b>(i, j)[1] = 0;
        image.at<Vec3b>(i, j)[2] = 0;
      }
    }
  }
  // cout<<image<<endl;
  cv::namedWindow("image", 0);
  cv::imshow("image", image);
  const time_t t = time(NULL);
  struct tm* current_time = localtime(&t);
  string path = "/home/idriver/" + num2str(1900 + current_time->tm_year) + "_" +
                num2str(current_time->tm_mon + 1) + "_" +
                num2str(current_time->tm_mday) + "_" +
                num2str(current_time->tm_hour) + "_" +
                num2str(current_time->tm_min) + "_" +
                num2str(current_time->tm_sec) + "_" + "test.jpeg";
  cv::imwrite(path, image);
  cv::waitKey(0);
}

// #include <time.h>
void ClassA::GetLocalTime() {
  const time_t t = time(NULL);
  struct tm* current_time = localtime(&t);

  printf(
      "current year is %d;current month is %d;current date of month is %d\r\n",
      1900 + current_time->tm_year,
      1 + current_time->tm_mon /*此month的范围为0-11*/, current_time->tm_mday);
  printf("time part %d:%d:%d \r\n", current_time->tm_hour, current_time->tm_min,
         current_time->tm_sec);
}

bool ClassA::DeadRockoner(Site dr1, Site dr0, double length, double density,
                          double k0, double k1, double offset,
                          SiteVec& update_sites) {
  // offset: + for left translation,- for right translation
  Site ddr(dr1 - dr0), update_site;
  update_sites.clear();
  double cos_t = sqrt(1.0 / (k0 * k0 + 1.0));
  double sin_t = sqrt(k0 * k0 / (k0 * k0 + 1.0));
  k1 += offset * (k0 * sin_t + cos_t);
  double dtheta = (dr1.angle - dr0.angle) * M_PI / 180.0;
  double ctheta = cos(dtheta), stheta = sin(dtheta);
  double s = 0.0, x_in = 0.0, y_in = 0.0, denorm = 0.0;
  if (fabs(denorm = ctheta + k0 * stheta) > 1e-3)
    x_in = (ctheta * ddr.x + (ddr.y - k1) * stheta) / denorm;
  else {
    cout << "DR angle error, div/0 !!!" << endl;
    return false;
  }
  while (s < length) {
    y_in = k0 * x_in + k1;
    update_site.x = (x_in - ddr.x) * ctheta + (y_in - ddr.y) * stheta;
    update_site.y = (y_in - ddr.y) * ctheta - (x_in - ddr.x) * stheta;
    if (!update_sites.empty()) s += (update_site - update_sites.back()).mold();
    if (update_sites.size() == 2)
      cout << update_sites[0].x << "," << update_sites[0].y << ","
           << (update_sites[0].angle =
                   (update_sites[1] - update_sites[0]).inerangle())
           << endl;
    update_sites.push_back(update_site);
    x_in += density;
  }
  return true;
}

bool ClassA::DeadRockoner2(Site dr1, Site dr0, double length, double density,
                           double k0_in, double k1_in, double offset,
                           SiteVec& update_sites) {
  // offset: + for left translation,- for right translation
  Site ddr(dr1 - dr0), update_site;
  update_sites.clear();
  double cos_t = sqrt(1.0 / (k0_in * k0_in + 1.0));
  double sin_t = sqrt(k0_in * k0_in / (k0_in * k0_in + 1.0));
  k1_in += offset * (k0_in * sin_t + cos_t);

  double dtheta_r = (dr1.angle - dr0.angle) * M_PI / 180.0;
  if (fabs(dtheta_r) > 40.0 * M_PI / 180.0) {
    cout << "DR angle too large(>40') !!!" << endl;
    return false;
  }
  
  double theta = atan(k0_in) - dtheta_r;
  double k0 = tan(theta);
  double ctheta = cos(dtheta_r), stheta = sin(dtheta_r);
  double s = 0.0, x_in = 0.0, y_in = 0.0, denorm = 0.0;
  if (fabs(denorm = ctheta + k0 * stheta) > 1e-3)
    x_in = (ctheta * ddr.x + (ddr.y - k1_in) * stheta) / denorm;
  else {
    cout << "DR angle error(45'), div/0 !!!" << endl;
    return false;
  }
  y_in = k0_in * x_in + k1_in;
  double k1 = (y_in-ddr.y)/ctheta; 

  x_in = 0.0, y_in=0.0;
  while (s < length) {
    update_site.x = x_in;
    update_site.y = k0 * x_in + k1;
    if (!update_sites.empty()) s += (update_site - update_sites.back()).mold();
    if (update_sites.size() == 2)
      cout << update_sites[0].x << "," << update_sites[0].y << ","
           << (update_sites[0].angle =
                   (update_sites[1] - update_sites[0]).inerangle())
           << endl;
    update_sites.push_back(update_site);
    x_in += density;
  }
  return true;
}

bool ClassA::RunDeadRockoner(int argc, char const* argv[]) {
  if (argc < 6) {
    cout << "Input error" << endl;
    return -1;
  } else {
    Site dr0(0, 0, 0), dr1(atof(argv[3]), atof(argv[4]), atof(argv[5]));
    SiteVec update_sites;
    DeadRockoner2(dr1, dr0, 30.0, 0.05, atof(argv[1]), atof(argv[2]), 0.7,
                 update_sites);
    WriteToFile wf;
    string file_path = "../data/result.csv";
    wf.Sitevec2File(update_sites, file_path);
    // Plot pt;
    // pt.PlotVec(200, 200, update_sites);
  }
  cout << "done" << endl;
}

bool ClassA::UnitestDeadRockoner() {
  ReadFile rf;
  vector<vector<double>> test_data;
  string input_path = "../data/test_data.csv";
  rf.ReadCSV(input_path, test_data);
  cout << "test_data.size(): " << test_data.size() << endl;
  for (auto it : test_data) {
    Site dr0(0, 0, 0), dr1(it[2], it[3], it[4]);
    SiteVec update_sites;
    bool result =
        DeadRockoner2(dr1, dr0, 30.0, 0.05, it[0], it[1], 0.7, update_sites);
    if (!result) continue;
    Site st(it[5], it[6]);
    if ((update_sites[0] - st).mold() > 0.1 ||
        fabs(update_sites[0].angle - it[7]) > 0.1) {
      cout << "\033[1m test failed:\033[0m" << it[0] << "," << it[1] << ","
           << it[2] << "," << it[3] << "," << it[4] << "," << it[5] << ","
           << it[6] << "," << it[7] << endl;
    }
  }
}
