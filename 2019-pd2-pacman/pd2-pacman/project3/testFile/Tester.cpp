#include "Tester.h"
#include <iostream>
#include <string>

using namespace std;

bool Assert::pass;

void Assert::isTrue(bool statement){
  if(pass)
    pass = statement ? pass : false;
}

void Assert::isFalse(bool statement){
  if(pass)
    pass = !statement ? pass : false;
}

string Assert::isPass(){
  return pass ? "PASS" : "FAIL";
}

void test(string testName, void (*func)()){
  Assert::pass = true;
  func();

  cout << testName << ": " << Assert::isPass() << endl;
}
