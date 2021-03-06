# Chapter 1 웹어셈블리 소개

웹 개발자에게 성능은 언제나 중요하다.

- 3초 내에 웹페이지가 로드되지 않으면, 이용자의 40%는 이탈
- 쇼핑 등의 웹사이트의 성능이 좋지 않다면, 방문자의 79%는 재사용을 안함



*기술에 발전에 따라 웹도 많은 발전을 했지만, 아직까지 느린 자바스크립트만을 사용함*



## 1.1 웹어셈블리란?

WebAssembly는 최신 웹 브라우저에서 실행할 수 있는 새로운 유형의 코드이며 새로운 기능과 성능 면에서 큰 이점을 제공합니다. 직접 코드를 작성하는 것이 아니라 C, C ++, RUST 등의 저급 소스 언어를 효과적으로 컴파일하도록 고안되었습니다.

이는 웹 플랫폼에 큰 영향을 미칩니다. 이전에 불가능했던 웹에서 실행되는 클라이언트 응용 프로그램을 사용하여 웹에서 여러 언어로 작성된 코드를 네이티브에 가까운 속도로 실행하는 길을 제공합니다.

게다가 WebAssembly 코드를 사용하여 이를 활용하는 방법을 알 필요조차 없습니다. WebAssembly 모듈을 웹 (또는 Node.js) 앱으로 가져와 JavaScript를 통해 사용할 수 있도록 할 수 있습니다. JavaScript 프레임 워크는 WebAssembly를 사용하여 대규모 성능 이점과 새로운 기능을 제공하면서도 웹 개발자가 쉽게 기능을 사용할 수 있도록 할 수 있습니다.



파이어폭스 제작사인 모질라 재단은 **asm.js**라는 자바스크립트 서브셋을 발표했습니다.



### 1.1.1 웹어셈블리의 전신 asm.js




##### asm.js의 장점

- 직접 작성하는 대신, C/C++로 로직을 작성한 뒤 자바스크립트로 변환[트랜스필링(transpilling)] 한다. (장점 보단 방식)
- 계산량이 많은 코드를 더 빨리 실행한다. (비용이 큰 자바스크립트 대신 저비용 언어 사용)
- type-hint를 사용해 코드가 더 빨리 실행된다.
  - 변수 타입추론 없이 바로 실행 가능

##### asm.js의 단점

- type-hint 덕분에 코드가 아주 커질 수 있다.
- asm.js도 자바스크립트 파일이므로, 스마트폰에서 자원 낭비가 심하다.
- 개발자가 앱 유지보수를 하기가 힘들다. (기능을 추가하려면 자바스크립트 언어 자체를 수정해야 함)
- 자바스크립트는 원래 컴파일러 타깃으로 만든 프로그래밍 언어가 아니다.



### 1.1.2 asm.js부터 MVP 5까지

*asm.js의 단점을 보안하기 위해 나타난 시제품이 MVP(Minimum Viable Product)*

2017년 구글 마이크로소프트 등 자사의 브라우저를 MVP 사용 가능하게 업데이트 함



## 1.2 어떤 문제를 해결할 수 있는가?



### 1.2.1 성능 개선

웹어셈블리는 코드를 내려받아 실행하는 시간을 최대한 줄이자는 목표를 가지고 개발됨.

자바스크립트는 인터프리터 프로그래밍 언어로 알려져있다. 코드로 작성된 명령어를 읽자마자 기계어로 바꾸어 실행한다. 인터프리터 언어는 ([인터프리터 언어 vs 컴파일러 언어](https://velog.io/@jaeyunn_15/OS-Compiler-vs-Interpreter))미리 코드를 컴파일할 필요가 없으므로 더 빨리 실행되지만, 매번 코드를 실행할 때마다 명령어를 기계어로 변환해야 한다. 루프문이 있다면 매번 루프 안에 있는 코드를 한줄한줄 해석해야 한다.



앱은 발전하고, 웹 또한 네이티브 앱처럼 화려해지고 있다. 그에 따른 자바스크립트 코드의 길이가 거대해 지고 있다. 



브라우저 제작사는 코드 호출 즉시 실행되는 인터프리터의 장점을 살리고 실행속도가 더 빠른 컴파일 코드의 장점을 살릴 수 있는 중간 지점을 찾음. 그 결과 자바스크립트를 실행하는 도중에 엔진이 계속 코드를 모니터링하는 적시(Just-In-Time : JIT) 컴파일 개념이 구체화 됨. 어떤 코드가 여러 차례 사용되는 것으로 밝혀지면 엔진이 해당 코드를 기계어로 컴파일하는 아이디어.



### 1.2.2 자바스크립트보다 시동 속도가 빠르다

웹어셈블리로 컴파일한 코드는 텍스트 포맷이 아닌 바이너리 포맷의 바이트코드이기 때문에 파일 크기가 작고 전송 및 다운로드 속도가 빠르다.

바이너리 파일은 모듈을 단일 패스(single pass)로 검증 가능한 방향으로 설계됐으며, 파일 역시 여러 섹션을 병렬 컴파일할 수 있는 구조다.

브라우저 제작사는 JIT 컴파일 기술로 자바스크립트 성능을 비약적으로 향상시켰지만, 자바스크립트 엔진이 자바스크립트를 기계어로 컴파일하려면 코드를 여러 차례 모니터링해야 한다. 하지만 웹어셈블리 코드는 정적 정형(statically typed), 즉 변수형이 미리 결정되므로 따로 모니터링 안해도 되기 때문에 월등하게 성능이 좋다.

브라우저 제작사는 성능을 더 향상시키기 위해 웹어셈블리 파일을 내려받는 도중에 코드를 기계어로 컴파일하는 스트리밍 컴파일 기술을 도입해 다운로드하자마자 인스턴스화할 수 있고 시동 시간이 상당 단축됨.



### 1.2.3 브라우저에서 자바스크립트 이외의 언어를 사용할 수 있다

기존은 자바스크립트 이외의 언어를 웹에서 사용하려면 코드를 자바스크립트로 변환해야 했다.

자바스크립트는 원래 컴파일러 타깃으로 설계된 언어가 아니다.

웹어셈블리는 처음부터 컴파일러 타깃으로 설계되었다. 그렇기 때문에 굳이 자바스크립트로 트랜스파일할 필요가 없다.

웹어셈블리는 자바스크립트 언어에 국한되지 않기 때문에 자유롭게 기술을 개선할 수 있다.



### 1.2.4 코드를 재활용할 수 있다

데스크톱이나 서버 그리고 브라우저에서도 재사용 가능하다.





## 1.3 어떻게 작동하는가?



자바스크립트는 실행되면서 기계어로 컴파일 된다.

- 웹사이트에 포함된 자바스크립트는 코드 실행과 동시에 해석이 이루어 진다.
- 자바스크립트 변수는 동적이라 add 함수의 변수형은 정확히 알 수 없다.
  - a, b가 정수인지 부동소수인지 문자열인지.....
- 변수형을 알기위해 코드를 모니터링한다. (자바스크립트 엔진이 이런일을 함)




C++코드를 웹어셈블리로 변환한 다음 다시 브라우저에서 기계어로 변환한다.

- 웹어셈블리는 개발자가 바이너리 포맷으로 미리 컴파일을 한다.
- 변수형을 미리 알기 때문에 코드를 모니터링할 필요 없이 바이너리를 기계어로 컴파일할 수 있다.



### 1.3.1 컴파일러의 작동 원리

*개발자는 인간의 언어에 더 가까운 언어로 코딩하지만 컴푸터 프로세서는 기계어만 알아듣는다.*





- 일반적으로 컴파일러 프론트엔드에서 중간 표현형 Intermediate Representation로 변환된다.
- 컴파일러 백엔드는 이렇게 생성된 IR 코드를 최적화한 후, 원하는 기계어로 변환한다.





*프로그램이므로 컴파일한 웹어셈블리 모듈을 프로세서마다 따로 배포하는 일 또한 정말 고역이다.*

그렇기 때문에 IR 코드를 특별한 바이너리 바이트코드로 바꾸어 확장자가 .wasm인 파일에 저장하는 특별한 컴파일러가 실행된다.

wasm 파일에 있는 바이트코드는 웹어셈블리를 지원하는 브라우저가 이해할 수 있는 가상명령어(vitual instruction)의 집합일 뿐 아직 기계어가 아니다.

웹어셈블리를 지원하는 브라우저는 Wasm 파일을 로드하고 문제가 없는 파일인지 검증한 후에 해당 파일에 있는 바이트코드를 브라우저가 실행 중인 디바이스의 기계어로 컴파일한다.





### 1.3.2 로딩, 컴파일, 모듈 인스턴스화

브라우저에서 Wasm 파일을 내려받고 컴파일하려면 자바스크립트 함수를 호출해야 한다.

지금은 아니지만 앞으로 웹어셈블리 모듈이 ES6 모듈과 직접 상호작용 할 수 있게 되면, 전용 HTML 태그(<script type="module">)로 웹어셈블리 모듈을 로드할 수 있을 것이다.



웹어셈블리 모듈에 있는 바이너리 바이트코드를 컴파일하려면 먼저 모듈 구조, 할 수 없는 작업, 접근 불가한 메모리 접근 시도 등 검증 과정을 거쳐야 한다. Wasm은 검증, 기계어 컴파일, 인스턴스화 프로세스를 최대한 빨리 진행하기 위해 단일 패스로 검증될 수 있도록 고도로 구조화된 파일.



웹어셈블리 바이트코드가 브라우저에서 기계어로 컴파일된 다음에 모듈을 웹워커나 다른 브라우저 창에 전달할 수 있다. 9장에서 다룸.



컴파일을 마친 Wasm 파일은 사용하기 전에 인스턴스화해야 한다. 



**인스턴스화**란 필요한 임포트 객체를 모두 수신하고, 모듈을 구성하는 요소들을 초기화하고, 스타트 함수 호출 뒤 모듈 인스턴스를 실행 환경에 반환하는 과정.



## 1.4 웹어셈블리 모듈의 구조

웹 어셈블리는 네 가지 자료형을 지원한다.

- 32비트 정수 Integer
- 64비트 정수
- 32비트 부동소수 float
- 64비트 부동소수



Boolean 값은 32비트 정수(0은 false, 나머지 true)이다. 문자열을 비롯한 기타 자료형은 모듈 선형 메모리(linear memory)에 나타낸다.

웹어셈블리 프로그램의 핵심 단위는 모듈이다.

모듈은 코드의 바이너리 버전과 브라우저에서 컴파일된 버전 둘 다 가리키는 용어다.

어셈블리 모듈을 사람이 직접 속으로 작성할 일은 없지만, 모듈 구조와 내부 동작 원리를 잘 알고 있어야 한다.



Wasm 파일은 Preamble부터 시작한다.





### 1.4.1 Preamble

Preamble에는 웹어셈블리 모듈을 ES6 모듈과 구별짓는 매직 넘버(0x00 0x61 0x73 0x6D, 즉 \0asm)가 들어있다.

웹어셈블리 바이너리 포맷 버전(0x01 0x00 0x00 0x00, 즉 1)은 매직 넘버 바로 다음에 이어진다.

현재 바이너리 포맷 버전은 한 가지밖에 없다. 웹어셈블리 목표 중 하나는 기능이 새로 추가되더라도 버전 넘버를 올리지 않고 전체 하위 호환성을 유지하는 것이다.

Preamble 이후의 섹션은 모두 필수가 아닌 선택(option)이다. 섹션은 표준과 커스텀 섹션이 있다.



### 1.4.2 표준 섹션

각 표준 세션은 꼭 한번만 넣을 수 있고 나오는 순서가 정해져 있다. 표준 섹션은 고유한 쓰임새가 있고 구조가 명확하며 모듈 인스턴스화 시점에 검증한다. 2장에 자세히 나온다.



### 1.4.3 커스텀 섹션

커스텀 섹션은 표준 섹션에 해당되지 않는 용도로 사용하기 위해 모듈 내부에 데이터를 넣는 것이다.

모듈 안 어디서나 위치에 상관없이 몇번이든 나올 수 있다.

동일한 이름을 재사용할 수도 있다.

표준 섹션과 달리, 커스텀 섹션은 정확하게 배치되지 않아도 에러가 나지 않는다.



## 1.5 웹어셈블리 텍스트 포맷

웹어셈블리는 웹의 개방성을 지향한다.

웹어셈블리는 바이너리 포맷에 상응되는 텍스트 포맷이 있다. ([S-표현식](https://ko.wikipedia.org/wiki/S-%ED%91%9C%ED%98%84%EC%8B%9D) 사용)

텍스트 포맷 덕분에 개발자는 브라우저에서 소스 보기를 하거나 디버깅을 할 수 있다.

S-표현식은 특수한 컴파일러를 이용하거나 손으로 직접 작성할 수 있고, 웹어셈블리 바이너리 포맷으로 컴파일 가능하다.

하나의 모듈에 있는 섹션은 모두 옵션이기 때문에 빈 모듈의 S-표현식은 `(module)`이 된다.



*11장에서 상세히 다룸*

## 1.6 웹어셈블리는 왜 안전한가?

- 자바스크립트 VM을 공유하는 최초의 언어이다.
  - 자바스크립트 VM은 런타임과 격리되어 오랫동안 보안 테스트를 거치면서 견고해져있다.
  - 자바스크립트로 접근할 수 없는 것은 어셈블리 모듈도 접근 못한다.
  - 동일 출저 정책(same origin policy) 등 보안 강화 정책을 똑같이 준수할 것.
- 데스크톱 앱과 달리, 웹어셈블리 모듈은 디바이스 메모리에 직접 접근할 수 없다.
  - 모듈 인스턴스화 시 런타임 환경이 모듈에게 [어레이버퍼](https://developer.mozilla.org/ko/docs/Web/JavaScript/Typed_arrays)를 전달한다.
  - 모듈은 이 어레이버퍼를 선형 메모리로 사용하고 웹어셈블리 프페임워크는 코드 대신 메모리에 접근해서 항목을 실행한다.



[웹어셈블리 보안 공식 문서](https://webassembly.org/docs/security/)



## 1.7 웹어셈블리 모듈을 작성할 수 있는 언어

[지원 언어 참조 사이트](https://github.com/appcypher/awesome-wasm-langs#rust)



## 1.8 웹어셈블리 모듈은 어떻게 활용 가능한가?

2017년 크롬, 엣지, 파이어폭스, 오페라, 사파리 등 주요 브라우저 제작사는 일제히 MVP 지원 버전 업데이트.

크롬, 안드로이드용 파이어폭스, 사파리 등 일부 모바일 웹 브라우저도 지원.

웹어셈블리는 이식성을 염두에 두고 설계됐기 때문에 브라우저가 아닌 환경에서도 사용가능 10장에서 나옴.

웹어셈블리는 자바스크립트를 대체하는 기술이 아니라, 보완하는 기술.

## 1.9 마치며

- 바이너리로 인코딩하기 때문에 파일 크기가 작고 그만큼 전송 혹은 다운로드 속도가 빠름.
- Wasm 파일 구조상 파싱 및 검증이 빠르고 파일 일부를 병렬로 컴파일할 수 있다.
- 컴파일 스트리밍 덕분에 웹어셈블리 모듈을 내려받는 동시에 컴파일도 가능하다. 다운로드가 끝나면 바로 인스턴스화할 수 있어서 로드 시간이 상당히 빠르다.
- 값비싼 자바스크립트 엔진 호출 대신 머신 레벨에서 호출되므로 연산량이 많은 코드는 속도 개선 효과를 톡톡히 볼 수 있다.
- 컴파일하기 전에 코드의 동작 상태를 모니터링할 필요가 없다. 즉, 매번 코드를 실행할 때마다 동일한 속도로 실행된다.
- 웹어셈블리는 자바스크립트 언어에 어떤 영향을 끼치지 않으므로 자바스크립트와 별개로 신속한 업데이트가 가능하다.
- 자바스크립트 이외의 언어로 작성된 코드도 브라우저에서 사용할 수 있다.
- 웹어셈블리 프레임워크를 브라우저 또는 브라우저 아닌 환경에서도 사용할 수 있게 구성하면 코드를 더 많이 재활용할 수 있다.


[네이버 D2 Javascript 동향](https://d2.naver.com/helloworld/8257914)
