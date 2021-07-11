---
marp: true
enableHtml: true
---

# wasm 모듈에서 함수 포인터로 js와 통신하기

---

## 모듈에서 js함수를 호출

<img width="1000px" src="img/1.png" >

---

## js함수를 모듈에 전달

모듈과 자바스크립트 함수 독립적으로 작성 가능하므로 유연

<img width="1000px" src="img/2.png" >

---

### c++ 함수 시그니처 정의

```c++
void test(int n){
    printf("Number : %d\n", n);
}

// 함수 포인터 생성
void (*Func)(int);

int main(){
  // 함수 포인터에 특정 함수 주소 저장
  Func = test;
  // 호출
  (*Func)(77);
  Func(77);
}
```

---

```c++
// 함수 포인터 데피니션 생성
typeof void (*Func)(int);

int main(){
  // 새로운 함수 포인터 변수를 생성
  Func myFunc;
  // 함수 포인터에 특정 함수 주소 저장
  myFunc = test;
  // 호출
  myFunc(77);
}
```

- 매번 포인터를 매개변수로 넘기는 것보다 코드가 단순해진다.
- 포인터를 수정할일이 있을때 typeof 데피니션만 수정하면 된다.

---

### validate.cpp

```c++
// 5장의 외부 함수 선언
  extern void UpdateHostAboutError(const char* error_message);

// 함수 포인터 데피니션 생성
  typedef void(*OnSuccess)(void);
  typedef void(*OnError)(const char*);

// 이에따른 수정사항 확인
```

---

### 컴파일

```shell
emcc validate.cpp -s RESERVED_FUNCTION_POINTERS=4 -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall','UTF8ToString','addFunction','removeFunction']" -o validate.js
```

- `RESERVED_FUNCTION_POINTERS` 함수포인터 매개변수 4개 - backing array에 4개의 원소 공간 확보.
  - 모듈에 자바스크립트 함수를 동적으로 지정하는 방법
  - 엠스크립튼 자체적으로 **backing array**를 관리, 모듈에 해당 시그니처 함수가 제공되는지 확인한다.
- 엠스크립튼 헬퍼함수 `addFunction, removeFunction` 접근 필요

---

### js (editproduct.js)

```js
function validateName(name) {
  return new Promise(function (resolve, reject) {
    const pointers = { onSuccess: null, onError: null };
    // 함수 포인터 생성
    createPointers(resolve, reject, pointers);

    Module.ccall(
      "ValidateName",
      null, //return type of void
      ["string", "number", "number", "number"],
      [name, MAXIMUM_NAME_LENGTH, pointers.onSuccess, pointers.onError]
    );
  });
}
```

---

#### addFunction

- backing array에 js 함수 추가
- ccall함수에 전달할 함수 포인터(인덱스) 반환
- arguments
  - 0: js함수
  - 1: 함수 반환값, 인자값 자료형을 문자열로.
    - v: void
    - i: 32bit integer
    - 등등

#### removeFunction

- 인덱스 받아서 backing array에서 삭제

---

```js
// 검증 함수 호출할때마다 콜백 포인터를 생성/삭제 해야하므로 이 과정을 헬퍼함수로 만들기.
function createPointers(resolve, reject, returnPointers) {
  const onSuccess = Module.addFunction(function () {
    // backing array에서 콜백 2개 삭제
    freePointers(onSuccess, onError);
    resolve();
  }, "v");

  const onError = Module.addFunction(function (errorMessage) {
    // backing array에서 콜백 2개 삭제
    freePointers(onSuccess, onError);
    // 모듈 메모리에서 에러메세지 읽어서 reject
    reject(Module.UTF8ToString(errorMessage));
  }, "vi");

  // 객체에 함수 인덱스 담아준다.
  returnPointers.onSuccess = onSuccess;
  returnPointers.onError = onError;
}

function freePointers(onSuccess, onError) {
  Module.removeFunction(onSuccess);
  Module.removeFunction(onError);
}
```

---

## 엠스크립튼 연결 js 없이 해보기

#### c++에서 함수포인터 발견 시 실제 동작

- 함수 포인터를 가리키는 레퍼런스는 모듈 Table 섹션에 있음
  - 모듈 Table 섹션: 모듈 메모리에 raw byte로 저장불가한 항목(함수 등)의 레퍼런스 배열, `WebAssembly.Table` 로 접근
- 웹어셈블리 프레임워크가 인덱스를 보고 모듈 Table 섹션에서 함수 가져와서 실행

---

### c++

사이드모듈 추가, 나머지는 앞과 동일

---

### 컴파일

```shell
emcc side_module_system_functions.cpp validate.cpp -s SIDE_MODULE=2 -O1 -o validate.wasm
```

---

### js

- backing array 대신 전역변수 활용

코드 보기

---

### wasm to wat

- [emscript의 -g 옵션](https://github.com/emscripten-core/emscripten/issues/9984) 잘못된 방법

- wasm-dis 유틸리티 사용
  - prequisite: https://formulae.brew.sh/formula/binaryen
