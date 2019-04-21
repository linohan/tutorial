#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#include <iostream>
class Singleton {
 public:
  static Singleton* GetInstance() {
    static Singleton instance;
    return &instance;
  }
  static int& GetNum() { return GetInstance()->num; }

 private:
  //把构造函数设为私有,防止创建新的实例
  Singleton(){};
  ~Singleton(){};
  //把复制构造函数和=操作符也设为私有,防止被复制
  Singleton(const Singleton&){};
  Singleton& operator=(const Singleton&){};
  int num = 0;
};
#endif
