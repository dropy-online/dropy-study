---
marp: true
enableHtml: true
---

# 웹 어셈블리 모듈에서 자바스크립트 호출하기

---

## 4장에서 한것

<img width="1000px" src="img/1.png" >

---

### c++

ValidateValueProvided 함수에서 오류 메세지를 담을 버퍼를 매개변수로 받는다. strcpy로 메세지를 버퍼에 복사한다.

```cpp
  int ValidateValueProvided(const char* value, const char* error_message, char* return_error_message)
  {
    if ((value == NULL) || (value[0] == '\0'))
    {
      strcpy(return_error_message, error_message);
      return 0;
    }
    return 1;
  }
```

---

### js (editproduct.js)

모듈과 상호작용하는 js에서 오류 메세지를 담을 버퍼를 생성하고 wasm 모듈 호출시 매개변수로 넘겨준다.

```js
function onClickSave() {
  let errorMessage = "";
  const errorMessagePointer = Module._malloc(256);

  if (!validateName(name, errorMessagePointer) ||
      !validateCategory(categoryId, errorMessagePointer)) {
    errorMessage = Module.UTF8ToString(errorMessagePointer);
  }

  Module._free(errorMessagePointer);
  ...
}
```

---

## 5장 - 버퍼없이 wasm 모듈에서 바로 자바스크립트 호출하기

<img width="1000px" src="img/2.png" >

---

C++ 수정

- `char* return_error_message` 매개변수 삭제
- `strcpy` 대신 extern 함수 `UpdateHostAboutError` 호출

---

`UpdateHostAboutError` 구현은 어디서? (커스텀 js 추가 방식)

<img width="700px" src="img/3.png" >

---

엠스크립튼 내장함수 `mergeInto`로 나의 js를 엠스크립튼 js에 포함시키기

```js
mergeInto(LibraryManager.library, {
  UpdateHostAboutError: function (errorMessagePointer) {
    setErrorMessage(Module.UTF8ToString(errorMessagePointer));
  },
});
```

- 첫번째 인자: 프로퍼티를 추가할 객체, LibraryManager.library에 추가하면 엠스크립튼 js파일에 추가된다.
- 두번째 인자: 프로퍼티가 담긴 객체

---

컴파일 해보기

```
emcc validate.cpp --js-library mergeinto.js -o validate.js -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall','UTF8ToString']"
```

---

editproduct.js 수정

- 버퍼 만들고, 매개변수로 넘기고, 모듈 메모리에서 값 읽어오는 부분 삭제

---

## 엠스크립튼 연결 js 없이 해보기

모듈이 호출하는 코드가 메인 js의 일부로
<img src="img/5.png" >

---

컴파일하기

```
emcc side_module_system_functions.cpp validate.cpp -s SIDE_MODULE=2 -O1 -o validate.wasm
```

---

editproduct.js 수정

```js
function initializePage() {
  ...
  // 모듈 메모리 참조하는 레퍼런스를 전역변수에 할당
  moduleMemory = new WebAssembly.Memory({initial: 256});

 //모듈에 전달할 객체
  const importObject = {
    env: {
      __memory_base: 0,
      memory: moduleMemory,
      _UpdateHostAboutError: function(errorMessagePointer) {
        setErrorMessage(getStringFromMemory(errorMessagePointer));
      },
    }
  };

  // 모둘 인스턴스화
  WebAssembly.instantiateStreaming(fetch("validate.wasm"), importObject).then(result => {
    moduleExports = result.instance.exports;
    //인스턴스를 전역변수에 할당
  });
}
```

---

## 그외 js - wasm 상호작용 방법

### 앰스크립튼 매크로 (부록C)

- 디버깅용으로만 추천, js코드는 c++코드와 분리하는게 유리

---

emscripten_run_script 매크로

```cpp
emscripten_run_script("console.log('function')");
```

---

EM_JS 매크로

- c++에 자바스크립트 함수 선언가능
- 함수반환형, 함수이름, 함수 매개변수, 함수본문을 인자로 받는다.

  ```cpp
  //선언
  EM_JS(void, FunctionName, (), {
    console.log('function called');
  })

  //사용
  int main(){
    FunctionName('hello');
  }
  ```

---

EM_ASM 매크로

- c++에 인라인 자바스크립트 사용가능
  ```cpp
  int main(){
    EM_ASM(console.log('macro calling'));
  }
  ```
- 매개변수 및 반환 타입에 따라 여러 종류 있음
  - EM*ASM*
  - EN_ASM_INT 등

---

### 함수포인터 (6장)

- c++에서 콜백함수 포인터를 매개변수로 받도록 함
- 모듈과 자바스크립트 함수 독립적으로 작성 가능하므로 유연
- 함수포인터 사용을 위한 js 추가됨
