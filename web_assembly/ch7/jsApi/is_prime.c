#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
int IsPrime(int value) {
  if (value == 2) return 1;
  if (value <= 1 || value % 2 == 0) return 0;
  for (int i = 3; (i * i) <= value; i += 2) {
    if (value % i == 0) return 0;
  }

  return 1; 
}
