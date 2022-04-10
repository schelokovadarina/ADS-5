// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int priority(char w) {
  switch (w) {
  case '(':
    return 0;
  case ')':
    return 1;
  case '+':
    return 2;
  case '-':
    return 2;
  case '*':
    return 3;
  case '/':
    return 3;
  default:
    return 10;
  }
}
int calculate(char x, int a, int b) {
  switch (x) {
  case '*':
    return a * b;
  case '/':
    return a / b;
  case '-':
    return a - b;
  case '+':
    return a + b;
  default:
    return 10;
  }
}
std::string infx2pstfx(std::string inf) {
  std::string str;
  char space = ' ';
  for (int i = 0; i < inf.size(); i++) {
    if (priority(inf[i]) == 4) {
      str.push_back(inf[i]);
      str.push_back(space);
    } else {
      if (priority(inf[i]) == 0) {
        stackA.push(inf[i]);
      } else if (stackA.isEmpty()) {
        stackA.push(inf[i]);
      } else if ((priority(inf[i]) > priority(stackA.get()))) {
        stackA.push(inf[i]);
      } else if (priority(inf[i]) == 1) {
        while (priority(stackA.get()) != 0) {
          str.push_back(stackA.get());
          str.push_back(space);
          stackA.pop();
        }
        stackA.pop();
      } else {
        while (!stackA.isEmpty() &&
          (priority(inf[i]) <= priority(stackA.get()))) {
          str.push_back(stackA.get());
          str.push_back(space);
          stackA.pop();
        }
        stackA.push(inf[i]);
      }
    }
  }
  while (!stackA.isEmpty()) {
    str.push_back(stackA.get());
    str.push_back(space);
    stackA.pop();
  }
  for (int i = 0; i < str.size(); i++) {
    if (str[str.size() - 1] == ' ')
      str.erase(str.size() - 1);
  }
  return str;
}

int eval(std::string pref) {
  int i = 0;
  int a, b = 0;
  int result = 0;
  while (i < pref.length()) {
    if (priority(pref[i]) == 10) {
      if (pref[i] != ' ') {
        stackB.push(pref[i] - '0');
      }
    } else if (priority(pref[i]) < 4) {
      a = stackB.get();
      stackB.pop();
      b = stackB.get();
      stackB.pop();
      stackB.push(calculate(pref[i], b, a));
    }
    i++;
  }
  result = stackB.get();
  return result;
}
#endif  // INCLUDE_ALG_H_
