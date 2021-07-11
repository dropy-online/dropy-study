#include <cstdlib>

#ifdef __EMSCRIPTEN__
  #include <dlfcn.h> // include dlopen
  #include <emscripten.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*FindPrimes)(int,int);

void CalculatePrimes(
  const char* file_name // 로딩이 완료된 파일 명
) {
  // 2. 파일 핸들러 가져오기
  void* handle = dlopen(
    file_name,
    RTLD_NOW // 모드를 나타내는 정수 (RLTD: 파일이 로드된 시점)
  );
  if (handle == NULL) return;

  // 3. 함수 포인터 가져오기
  FindPrimes find_primes = (FindPrimes)dlsym(
    handle, // 파일 핸들러
    "FindPrimes" // 참조하려는 함수명
  );
  if (find_primes == NULL) return;

  // 4. 사이드 모듈 실행
  find_primes(3, 100000);

  // 4. 사이드 모듈 닫기
  dlclose(handle);
}

int main() {
  // 1. wget 으로 파일 시스템의 wasm 모듈을 메모리로 가져온다
  emscripten_async_wget(
    "./calculate_primes.wasm", // 파일 경로
    "calculate_primes.wasm", // emscripten 파일시스템의 파일명 (동일하게 설정)
    CalculatePrimes, // 다운로드 완료 및 성공시 callback
    NULL // 다운로드 중 에러 발생시 callback
  );

  return 0;
}

#ifdef __cplusplus
}
#endif
