#ifndef TESTER_H
#define TESTER_H

#include <string>
using namespace std;

void test(string, void(*)());

class Assert{
  friend void test(string, void (*)());

public:
  template <class T1, class T2>
  static void isEqual(T1, T2);

  template <class T1, class T2>
  static void isNotEqual(T1, T2);

  static void isTrue(bool);
  static void isFalse(bool);

private:
  static string isPass();
  static bool pass;
};

template <class T1, class T2>
void Assert::isEqual(T1 t1, T2 t2){
  if(pass)
    pass = t1 == t2 ? pass : false;
}

template <class T1, class T2>
void Assert::isNotEqual(T1 t1, T2 t2){
  if(pass)
    pass = !(t1 == t2) ? pass : false;
}

#endif
