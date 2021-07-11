# 7. 동적 링킹 : 기초

둘 이상의 모듈을 **런타임 시점**에 합하는 과정이다.  

## 7.1. 동적 링킹의 장단점

- 장점
    - 변경된 모듈만 컴파일 함으로써 빌드시간 단축이 가능하다
    - 필요한 모듈만 먼저 내려받음으로써 성능을 끌어올리기 쉽다
    - 브라우저는 모듈 단위로 캐시해두기 때문에, 다른 웹페이지 성능에도 긍정적인 영향을 줄 수 있다
- 단점
    - 빌드 설정이 복잡해진다
    - 다수의 모듈을 링크시키기 때문에, 인스턴스화 할 때 처리 작업량이 많다
    - 브라우저에서 다양한 성능 향상 정책을 사용하지만, 모듈 내부의 함수 호출보다 링크된 모듈끼리의 함수 호출이 빠르기는 어렵다.

## 7.2. 동적 링킹 방법

- 작성한 C/C++ 코드를 `dlopen` 함수를 이용해 수동 링크
- 링크할 ws 모듈들을 JS 파일의 `dynamicLibraries` 배열에 지정하면 자동으로 링킹
- JS Web API 를 활용해서 수동으로 `import`, `export`

### 특이사항

- 사이드 모듈에서 메인 모듈의 기능을 모두 사용 가능하다
- `main()` 함수를 가지고 있는 것과 메인모듈이 되는 것은 무관하다

### 동적링킹: `dlopen`

- `ch7/dlopen` 참고

```sh
emcc calculate_primes.cpp -s SIDE_MODULE=2 -O1 -o calculate_primes.wasm
emcc main.cpp -s MAIN_MODULE=1 -o main.html
```

### 동적링킹: `dynamicLibraries`

- 각 사이드 모듈에 있는 동일한 이름의 함수를 사용할 수 없는 단점이 있다.
- `ch7/dynamicLibraries` 참고

```sh
emcc main.cpp -s MAIN_MODULE=1 --pre-js ./pre.js -o main.html
```

### 동적링킹: Javascript API

- `ch7/jsApi` 참고

```sh
emcc is_prime.cpp -s SIDE_MODULE=2 -Os -o is_prime.wasm
emcc find_primes.cpp -s SIDE_MODULE=2 -Os -o find_primes.wasm
```
