#include <emscripten.h>

extern int IsPrime(int value);
extern void LogPrime(int prime);

EMSCRIPTEN_KEEPALIVE
void FindPrimes(int start, int end) {
  for (int i = start; i <= end; i += 2) {
    if (IsPrime(i)) LogPrime(i);
  }
}