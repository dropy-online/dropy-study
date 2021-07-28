# Chapter 8 동적 링킹: 구현


## 웹어셈블리 모듈을 동적 링킹하는 세 가지 방법

- dlopen : C/C++ 코드를 수동으로 모듈에 링크하여 특정 함수를 가리키는 포인터를 얻는다.
- dynamicLibraries : 자바스크립트에서 엠스크립튼에게 링크할 모듈 목록을 전달하면 엠스크립튼이 모듈인스턴스화 시 해당 모듈에 자동으로 링크한다.
- 수동 링킹 : 웹어셈블리 자바스크립트 API로 A 모듈의 익스포트를 가져와 B 모듈의 임포트로 전달한다.

여기서는 두 번째 방식인 dynamicLibraries 방식으로 동적 링킹을 구현한다.

4~6장에서 작성했던 POS 애플리케이션에 주문하기 페이지를 추가하며 롱적 링킹을 배워본다.

![](https://i.imgur.com/6l51AzJ.jpg)

- 주문하기 페이지에 구현할 검증 로직도 상품수정 페이지와 별반 차이가 없다.
    - 두 페이지 모두 드롭다운 리스트에서 올바른 항목을 선택해야 한다.
    - 두 페이지 모두 필수값을 입력했는지 확인해야 한다.

같은 로직을 각 모듈에 따로 두는 건 중복이다. 공통 로직을 빼서 공유하는 구조가 좋다. **공통 모듈에 동적 링크하여 필요한 기능을 가져다 쓰는 것을 구현해본다.**


![](https://i.imgur.com/sgMxlwX.jpg)

웹사이트는 SPA로 개발하고 dynamicLibraries로 동적 링킹을 할 경우, 엠스크립튼 자바스크립트가 실행되기 전에 엠스크립튼으로 링크할 모든 사이드 모듈을 지정해야 한다. 보톤 엠스크립튼 자바스크립트는 Module이라는 전역 객체로 존재하는데, 브라우저가 자바스크립트 파일을 로드하는 시점에 이 객체가 초기화 되면서 우리가 지정한 사이드 모듈이 모두 메인 모듈에 링크 된다.

## 8.1 웹 어셈블리 모듈 생성하기

동적 링킹은 다수의 사이드 모듈을 하나의 메인 모듈에 링크하는 작업이다. 메인 모듈은 하나다.

![](https://i.imgur.com/URiunlT.png)

### 1. validate.cpp 파일을, 공통 로직이 담긴 파일(validate_core.cpp)과 상품수정 페이지에만 해당되는 로직이 있는 파일(validate_product.cpp)로 분리한다.


5장의 validate.cpp 를 두 파일로 나눕니다.
- 공통 로직 : validate_core.cpp
- 상품수정 : validate_product.cpp

#### validate_core.cpp 파일 수정

##### step 1 : 다른 모듈이 호출해서 사용할 수 있는 함수로 익스포트 해야 하므로 선언

```cpp
#ifdef __EMSCRIPTEN__
  EMSCRIPTEN_KEEPALIVE
#endif
```

[참고](https://developer.mozilla.org/ko/docs/WebAssembly/C_to_wasm)

##### step 2 : IsCategoryIdInArray 함수 공동화로 IsIdInArray로 변경

```cpp
int IsIdInArray(char* selected_id, int* valid_ids, int array_length)
  {
    // Loop through the array of valid ids that were passed in...
    int id = atoi(selected_id);
    for (int index = 0; index < array_length; index++)
    {
      // If the selected id is in the array then...
      if (valid_ids[index] == id)
      {
        // The user has a valid selection so exit now
        return 1;
      }
    }

    // We did not find the id in the array
    return 0;
  }
```

#### validate_product.cpp 파일 수정

##### step 1 : 공통모듈이 validate_core.cpp 에 있으므로 extern으로 선언해준다.

추가로 필요없는 ValidateValueProvided, IsCategoryIdInArray 두 함수를 제거.


##### step 2 : 다른 네이밍 수정

### 2. C++ 파일(validate_order.cpp)을 새로 만들어 주문하기 폼에만 해당되는 로직을 구현한다.

```cpp
#include <cstdlib>

#ifdef __EMSCRIPTEN__
  #include <emscripten.h>
#endif

#ifdef __cplusplus
extern "C" { // So that the C++ compiler doesn't rename our function names below
#endif

  // Functions that are part of validate_core.cpp:
  extern int ValidateValueProvided(const char* value, const char* error_message);
  extern int IsIdInArray(char* selected_id, int* valid_ids, int array_length);

  // Function that will be imported from JavaScript
  extern void UpdateHostAboutError(const char* error_message);

#ifdef __EMSCRIPTEN__
  EMSCRIPTEN_KEEPALIVE
#endif
  int ValidateProduct(char* product_id, int* valid_product_ids, int array_length) 
  {
    // Validation 1: A Product ID must be selected
    if (ValidateValueProvided(product_id, "A Product must be selected.") == 0) 
    {
      return 0;
    }

    // Validation 2: A list of valid Product IDs must be passed in
    if ((valid_product_ids == NULL) || (array_length == 0))
    {
      UpdateHostAboutError("There are no Products available.");
      return 0;
    }

    // Validation 3: The selected Product ID must match one of the IDs provided
    if (IsIdInArray(product_id, valid_product_ids, array_length) == 0)
    {
      UpdateHostAboutError("The selected Product is not valid.");
      return 0;
    }

    // Everything is ok (no issues with the product id)
    return 1;
  }

#ifdef __EMSCRIPTEN__
  EMSCRIPTEN_KEEPALIVE
#endif
  int ValidateQuantity(char* quantity)
  {
    // Validation 1: The quantity must be provided
    if (ValidateValueProvided(quantity, "A quantity must be provided.") == 0)
    {
      return 0;
    }

    // Validation 2: The quantity must be greater than zero
    if (atoi(quantity) <= 0)
    {
      UpdateHostAboutError("Please enter a valid quantity.");
      return 0;
    }

    // Everything is ok (no issues with the quantity)
    return 1;
  }

#ifdef __cplusplus
}
#endif

```


주문하기 폼에는 상품명을 선택하는 드롭다운 리스트와 수량 필드가 있다. 두 값은 모두 문자열 형태로 모듈에 전달되지만 실제로 상품 ID는 숫자다.

#### ValidateProduct 함수

매개변수
- 사용자가 선택한 상품 ID
- 올바른 상품 ID가 담긴 정수 배열을 가리키는 포인터
- 올바른 상품 ID가 담긴 정수 배열의 원소 개수

세 가지를 검증
- 사용자가 상품 ID를 입력했는가?
- 올바른 상품 ID가 담긴 정수 배열이 제공됐는가?
- 사용자가 선택한 상품 ID가 올바른 상품 ID가 담긴 정수 배열에 속한 원소인가?


```cpp
int ValidateProduct(char* product_id, int* valid_product_ids, int array_length) 
  {
    // Validation 1: A Product ID must be selected
    if (ValidateValueProvided(product_id, "A Product must be selected.") == 0) 
    {
      return 0;
    }

    // Validation 2: A list of valid Product IDs must be passed in
    if ((valid_product_ids == NULL) || (array_length == 0))
    {
      UpdateHostAboutError("There are no Products available.");
      return 0;
    }

    // Validation 3: The selected Product ID must match one of the IDs provided
    if (IsIdInArray(product_id, valid_product_ids, array_length) == 0)
    {
      UpdateHostAboutError("The selected Product is not valid.");
      return 0;
    }

    // Everything is ok (no issues with the product id)
    return 1;
  }
```

#### ValidateQuantity 함수

두 가지를 검증
- 사용자가 수량을 입력했는가?
- 입력된 수량이 1 이상인가?

```cpp
int ValidateQuantity(char* quantity)
  {
    // Validation 1: The quantity must be provided
    if (ValidateValueProvided(quantity, "A quantity must be provided.") == 0)
    {
      return 0;
    }

    // Validation 2: The quantity must be greater than zero
    if (atoi(quantity) <= 0)
    {
      UpdateHostAboutError("Please enter a valid quantity.");
      return 0;
    }

    // Everything is ok (no issues with the quantity)
    return 1;
  }
```

### 3. validate_order.cpp validate_product.cpp 두 파일을 엠스크립튼으로 컴파일하여 웹어셈블리 사이드 모듈을 생성한다.

엠스크립튼으로 동적 링킹을 할 때에 메인 모듈은 하나만 가능하며, 표준 C 라이브러리 함수 및 엠스크립튼 자바스크립트 파일은 메인 모듈의 일부로 포함됨. 사이드 모듈에는 이런게 포함 안되어있기 때문에 메인 모듈에 링크해서 갖다쓰면 된다.

이 예제는 메인모듈 validate_core.cpp / 사이드 모듈 validate_product.cpp, validate_order.cpp) 로 구성된다.

`emcc validate_product.cpp -s SIDE_MODULE=2 -O1 -o validate_product.wasm`

`emcc validate_order.cpp -s SIDE_MODULE=2 -O1 -o validate_order.wasm`


### 4. 검증 오류 시 호출할 자바스크립트 함수를 mergeinto.js 파일에 작성한다. 이 함수 코드는 메인 모듈 컴파일 시 엠스크립튼 자바스크립트 파일에 포함된다.




### 5. validate_core.cpp 파일을 엠스크립튼으로 컴파일하여 웹어셈블리 메인 모듈을 생성한다.


- 명령줄에 -s MODULARIZE=1 플래그를 추가하면 엠스크립튼 자바스크립트의 Module 객체가 함수 안에 래핑된다.
- 사이드 모듈에서 표준 C 라이브러리 함수 중 '_strlen','_atoi'을 사용해야 한다.
- 자바스크립트는 엠스크립튼 헬퍼 함수 ccall','stringToUTF8','UTF8ToString' 가 필요하다.


`emcc validate_core.cpp --js-library mergeinto.js -s MAIN_MODULE=2 -s MODULARIZE=1 -s EXPORTED_FUNCTIONS="['_strlen','_atoi']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall','stringToUTF8','UTF8ToString']" -o validate_core.js`

<br>

**웹 어셈블리 모듈을 생성한 다음에는 웹페이지를 수정한다.**



## 8.2 웹페이지 수정하기

- html 및 함수는 코드 참조


![](https://i.imgur.com/es4TpqL.png)

6. 웹페이지에 네비게이션 바를 새로 만들고 주문하기 폼 컴트롤을 삽입한다. 사용자가 클릭한 네비게이션 링크에 해당하는 컨트롤 세트가 화면에 표시되도록 자바스크립트를 수정한다.
7. 페이지에 맞는 사이드 모듈이 공통 모듈에 링크되도록 자바스크립트를 수정한다. 주문하기 폼을 검증하는 자바스크립트 역시 추가한다.


동적 링킹 index.js

```javascript
// Helper to adjust the controls to show the proper view
function switchForm(showEditProduct) {
  // Just in case there was an error message displayed from the previous form, clear the message
  setErrorMessage("");
  setActiveNavLink(showEditProduct);
  setFormTitle(showEditProduct);

  if (showEditProduct) {
    // Only create the Emscripten Module object for the Edit Product form the once...
    if (productModule === null) {
      productModule = new Module({ dynamicLibraries: ['validate_product.wasm'] });
    }
 
    // Show the Edit Product controls
    showElement("productForm", true);
    showElement("orderForm", false);
  } else {
    // Only create the Emscripten Module object for the Order form the once...
    if (orderModule === null) {
      orderModule = new Module({ dynamicLibraries: ['validate_order.wasm'] });
    }

    // Show the Order form's controls
    showElement("productForm", false);
    showElement("orderForm", true);
  }
}
```

MODULARIZE 플래그를 지정해 모듈을 컴파일했고 엠스크립튼 웹어셈블리 모듈을 자동으로 다운로드/인스턴스화하기 때문에 엠스크립튼 Module 객체 인스턴스는 직접 생성해야 한다.