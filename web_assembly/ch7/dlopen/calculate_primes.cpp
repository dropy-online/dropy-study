#include <cstdlib>
#include <cstdio>
#include <emscripten.h>

#ifdef __cplusplus
extern "C" {
#endif

int IsPrime(int value) {
  if (value == 2) return 1;
  if (value <= 1 || value % 2 == 0) return 0;
  for (int i = 3; (i * i) <= value; i += 2) {
    if (value % i == 0) return 0;
  }

  return 1; 
}

// 컴파일 시 export 함수 목록에 자동으로 추가할 수 있다.
EMSCRIPTEN_KEEPALIVE
void FindPrimes(int start, int end) {
  printf("Prime numbers between %d and %d:\n", start, end);

  for (int i = start; i <= end; i += 2) {
    if (IsPrime(i)) {
      printf("%d ", i);
    }
  }
  printf("\n");
}

int main() {
  FindPrimes(3, 100000);

  return 0; 
}

#ifdef __cplusplus
}
#endif
