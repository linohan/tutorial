#include <algorithm>
#include <bitset>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

/*****************************tuple****************************/
std::tuple<int, vector<int>, string> GenerateTuple(int i) {
  vector<int> v;
  for (int j = 0; j < 5; j++) {
    v.push_back(j - 3);
  }
  return make_tuple(i, v, "test");
}

bool TestTuple() {
  int i;
  tuple<int, vector<int>, string> T(i, {i - 1, i + 1}, "hello world");
  cout << tuple_size<decltype(T)>::value << endl;

  auto res = GenerateTuple(0);
  cout << get<0>(res) << endl;
  auto V = get<1>(res);
  for (auto it = V.begin(); it != V.end(); it++) {
    cout << *it << endl;
  }
  cout << get<2>(res) << endl;
}

bool TestStack(){
  stack<Site> stack_value;
  cout<<stack_value.empty()<<endl;
  Site s0;
  Site s1(1,1);
  Site s2(2,2);
  stack_value.push(s0);
  stack_value.push(s1);
  stack_value.push(s2);
  cout << stack_value.empty() << "," <<stack_value .size()<< endl;
  stack_value.pop();
  Site r = stack_value.top();
  cout << r.x<<","<<r.y << endl;
  cout << stack_value.empty() << "," << stack_value.size() << endl;
}

bool TestVector(){
  vector<int> v_pa;
  for (size_t i = 0; i < 5; i++) {
    v_pa.push_back(0);
  }
  // for (auto it : v_pa)，iterator
  // 是指向常值的指针，不可改变原值，使用&引用才能改变原值
  for (vector<int>::const_iterator it = v_pa.begin(); it != v_pa.end(); it++) {  
    cout<<*it;
  }

  for (auto it : v_pa) {
    cout << it << endl;
  }
vector<int> a;
  printf("%s\n", typeid(a).name());
}
/**************************************************************/