# 3. 웹 어셈블리 모듈 만들어보기

## 3.1. 엠스크립튼 툴킷

- C/C++ 코드를 asm.js 로 트랜스파일 하기 위한 목적으로 개발 되어 있습니다.
- 현재 웹 어셈블리 스펙이 성숙함에 따라서, 바이트 코드로 변환하는 역할을 하고 있습니다.
    - IR(Intermediate Representation) 역할을 .wasm 파일이 수행하고 있다고 생각 할 수 있습니다 ([참고](https://jarombek.com/blog/jan-7-2019-web-assembly#:~:text=An%20intermediate%20representation%20is%20code,representation%20for%20higher%2Dlevel%20languages.))
- LLVM 컴파일러중 CLang을 사용 합니다.

> LLVM 간단정리 (한번 찾아보는 것을 추천)  
> - IR 을 둠으로써, 컴파일러가 다양한 고수준 언어에 대응하기 쉽다.  
> - 컴파일러의 코드최적화와 기계어 변환 등을 담당해주기 때문에, 프론트엔드 컴파일러 부분만 개발해서 사용할 수 있다.
> - 이해에 도움이 되는 사진이 있어서 첨부 (나무위키 참조)

![llvm](./ch3/ch3_01.png)

## 3.2. 웹 어셈블리 모듈

몇가지 중점이 되는 특징을 정리하면 아래와 같습니다.

- 웹 어셈블리 바이너리 파일과 컴파일된 객체 모두를 모듈이라고 부릅니다.  
- Start 섹션(`main`함수)은 모든 모듈 `export` 를 호출하기 전에 가장 먼저 호출된다.
- 웹 어셈블리 모듈은 호스트로부터 `ArrayBuffer` 형태로 메모리를 받음. C/C++ 의 `Heap`과 같은 역할
    - 32bit int
    - 64bit int
    - 32bit float
    - 64bit float
    - boolean : 32bit int
    - string : linear memory
- 바이너리 포맷을 전송하기 때문에, 네트워크 속도의 이점이 있습니다.
- 단일 패스로 검증을 사용하기 때문에, 시동시간이 짧습니다.
- 코드가 제대로 동작하는지 체크하는 오버헤드가 발생해서, 네이티브 코드보다 성능이 약간 떨어질 수 있다.

## 3.3. 엠스크립튼 출력 옵션

1. HTML + JS + WASM
    - 프로덕션 환경에서는 잘 쓰지 않지만, 프로토타이핑 및 디버깅 하기 좋다.
2. JS + WASM
    - 표준 C 라이브러리가 들어 있고, 다양한 헬퍼함수가 들어있다.
    - 프로덕션 환경에서 쓰기 좋다.
3. WASM
    - 런타임 시 모듈을 동적 링킹하기 위해 사용
    - int, float 외의 데이터를 주고 받는 것은 주의해야 함.  
    모듈 내 ArrayBuffer는 인스턴스 생성시 할당되기 때문에, OS 상 문제가 발생하지는 않지만 추적하기 어려움
    
## 3.4. 엠스크립튼 C/C++ 코드를 컴파일하고 HTML 템플릿 활용

```bash
emcc calculate_primes.cpp -o calculate_primes.html
# http://localhost:3030/calculate_primes/calculate_primes.html
```

[코드](./ch3/calculate_primes) 참고

## 3.5. 엠스크립튼으로 자바스크립트 연결 코드 생성하기

```bash
emcc calculate_primes.cpp -o calculate_primes.js
# http://localhost:3030/calculate_primes/calculate_primes.html
```

[코드](./ch3/calculate_primes) 참고

## 3.6. 엠스크립튼으로 자바스크립트 연결 코드 생성하기

```bash
# 자세한 옵션들은 아래 URL 참고
# https://emscripten.org/docs/tools_reference/emcc.html
# https://github.com/emscripten-core/emscripten/blob/main/src/settings.js
# 사용한 옵션들만 간단히 소개하면,
#   - SIDE_MODULE=2 : 사이드 모듈로 생성 / dead코드 삭제 / 표준 clib 등은 미포함 / 자바스크립트 연결파일 미생성
#   - O1 : 최적화 플래그로 runtime exception 과, C++ exception catching 을 포함시키지 않는다.
#     - 여러 함수와 전역 변수들이 코드에 포함되지 않기 때문에. -O1 옵션을 사용하면 링크 시 모듈에러 발생할 수 있음.
#   - EXPORTED_FUNCTIONS=['_Increment'] : _Increment 함수를 자바스크립트에서 사용가능하도록 export 한다.
#     - ['_Increment', '_Decrement'] 와 같이 공백이 포함되면 컴파일 에러가 발생한다.
emcc ./increment.cpp -s SIDE_MODULE=2 -s EXPORTED_FUNCTIONS=['_Increment'] -O1 -o ./increment.wasm
# http://localhost:3030/increment/index.html
```

[코드](./ch3/increment) 참고
