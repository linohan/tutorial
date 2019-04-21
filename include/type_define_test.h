#include <iostream>
#include <vector>
#include "site.h"
using namespace std;

/***********************test1**********************/
#define testDefine(ai, bi)          \
  double ca = cos(ai * M_PI / 180); \
  double sa = sin(ai * M_PI / 180); \
  double cb = cos(bi * M_PI / 180); \
  double sb = sin(bi * M_PI / 180);

/***********************test2**********************/
#define STATESOK (0)

/***********************test3**********************/
int test_TD1(int a, MyPoint b, double* c) {
  *c = 1.0;
  return a + 1;
}

int test_TD2(int a, MyPoint b, double* c) {
  *c = 2.0;
  return a + 2;
}

int test_TD3(int a, MyPoint b, double* c) {
  *c = 3.0;
  return a + 3;
}

typedef int (*test_TD)(int, MyPoint, double*);
vector<test_TD> testTD_word = {test_TD1, test_TD2, test_TD3};

bool TestTD() {
  for (int i = 0; i < 3; i++) {
    int num = 1;
    double p;
    MyPoint pt;
    int result = testTD_word[i](num,pt,&p); 
    cout<< "c:" << p << ", a:" << result << endl;
  }
}
/************************************************************/