#include <iostream>
#include <emscripten.h>

bool checkPrime(int value) {
  if (value == 2) {
    return true;
  }
  if (value <= 1 || value % 2 == 0) {
    return false;
  }

  // 에라토스테네스의 접근법
  for (int i = 3; (i * i) <= value; i += 2) {
    if (value % i == 0) {
      return false;
    }
  }

  return true;
}

int main() {
  int start = 3;
  int end = 100000;

  std::cout << "Prime numbers between " << start << " and " << end << std::endl;

  // 홀수만 체크
  for (int i = start; i <= end; i += 2) {
    if (checkPrime(i)) {
      std::cout << i << ", ";
    }
  }

  std::cout << std::endl;

  return 0;
}
