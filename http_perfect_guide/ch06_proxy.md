# 2부 6장 프락시



## PROXY 란?

최초에 프락시는 인터넷 속도를 빠르게 하기 위해서 등장했습니다.

다수의 프락시가 인터넷을 이용해 이전에 방문했던 사이트를 방문하면, 캐싱을 해 두어 빠르게 열기 위한 용도로 사용했습니다.

하지만 요즘에는 인터넷 속도가 빨라지면서 비밀스럽게 사용하거나, 해킹을 방지하기 위한 보안용으로 사용하기 위해 사용합니다.

프락시는 중간에 아이피만 바꾸어서 서버에게 전달을 해줍니다.

나쁜 예로...🥰



## 6.1 웹 중개자

웹 프락시 서버는 클라이언트의 입장에서 트랜잭션을 수행하는 중개인이다.

HTTP 프락시 서버는 웹 서버이기도 하고 웹 클라이언트이기도 하다.

따라서 직접 프락시를 구축한다면 클라이언트와 서버 양쪽의 규칙을 모두 주의 깊게 따라야 한다.

### 6.1.1 개인 프락시와 공용 프락시

프락시 서버는 하나의 클라이언트가 독점적으로 사용할 수도 있고, 여러 클라이언트가 공유할 수도 있다.

하나의 클라이언트만을 위한 프락시를 개인 프락시, 여러 클라이언트를 위한 프락시를 공용 프락시라 한다.

#### 공용 프락시

대부분의 프락시는 공용이며 공유된 프락시다. 중앙 집중형 프락시를 관리하는게 더 비용효율이 높고 쉽다.

캐시 프락시 서버와 같은 몇몇 프락시 애플리케이션은 프락시를 이용하는 사용자가 많을수록 유리하다.

왜냐하면 여러 사용자들의 공통된 요청에서 이득을 취할 수 있기 때문이다.

#### 개인 프락시

개인 전용 프락시는 흔하지 않지만 꾸준히 사용되고 있다.(클라이언트 컴퓨터에서 직접 실행되는 형태)

브라우저의 기능을 확장하거나 성능 개선, 광고 운영을 위해 작은 프락시를 사용자 컴퓨터에서 직접 실행한다.

### 6.1.2 프락시 vs 게이트웨이

프락시는 같은 프로토콜을 사용하는 둘 이상의 애플리케이션을 연결한다.

게이트웨이는 서로 다른 프로토콜을 사용하는 둘 이상을 연결한다.

게이트웨이는 서로 다른 프로토콜로 말하더라도 서로 간의 트랙잭션을 완료할 수 있도록 해주는 변환기처럼 작동한다.

실질적으로는 프락시도 서로 다른 HTTP 버전의 프로토콜 통신을 변환하기 때문에 차이점은 모호하다.



## 6.2 왜 프락시를 사용하는가?

보안을 개선하고, 성능을 높여주며, 비용을 절약한다.

모든 HTTP트래픽을 들여다보고 건드릴 수 있기 때문에, 프락시는 부가적인 가치를 주는 여러 유용한 웹 서비스를 구현하기 위해 트래픽을 감시하고 수정할 수 있다.

### 활용사례

#### 성인 컨텐츠 차단

교육 사이트 제공과 동시에 성인컨텐츠 강제 차단이 가능하다.

#### 문서 접근 제어자

프락시 서버는 많은 웹 서버들과 웹 리소스에 대한 단일한 접근 제어 전략을 구현하고 감사 추적을 하기 위해 사용 될 수 있다.

대기업 환경이나 분산된 관료 조직에서 유용하다.

(ex : 뉴스 페이지 같은 인터넷 컨텐츠 접근 권한, 서버 B에 접근하기 전에 먼저 비밀번호 요구 등)

#### 보안 방화벽

프락시 서버는 조직 안에 들어오거나 나가는 응용 레벨 프로토콜의 흐름을 네트워크의 한 지점에서 통제한다.

바이러스를 제거하는 웹이나 이메일 프락시가 사용 할 수 있는, 트랙픽을 세심히 살펴볼 수 있는 hook을 제공한다.

#### 웹 캐시

프락시 캐시는 인기 있는 문서의 로컬 사본을 관리하고 해당 문서에 대한 요청이 오면 빠르게 제공하여, 인터넷 커뮤니케이션을 줄인다.

#### 대리 프락시(Surrogate)

어떤 프락시들은 웹 서버인 것처럼 위장한다.

대리 프락시는 공용 컨텐츠에 대한 느린 웹 서버의 성능을 개선하기 위해 사용될 수 있다.

흔히 서버 가속기 혹은 리버스 프락시라 부른다.

컨텐츠 라우팅 기능과 결합되어 주문형 복제 컨텐츠의 분산 네트워크용도로도 사용된다.

#### 컨텐츠 라우터

프락시 서버는 인터넷 트래픽 조건과 종류에 특정 웹 서버로 유도하는 컨텐츠 라우터로 동작할 수 있다.

#### 트랜스코더

프락시 서버는 컨텐츠를 클라이언트에게 전달하기 전에 본문 포맷을 수정 할 수 있다.

이와 같은 표현 방식의 변환을 트랜스코딩이라 한다.

#### 익명화 프락시(Anonymizer)

HTTP 메세지에서 신원을 식별할 수 있는 특성들을 제거함으로써 개인 정보 보호와 익명성 보장에 기여한다.

(IP주소, From 헤더, Referer 헤더, 쿠키, URI 세션 아이디...)

## 6.3 프락시는 어디에 있는가?

### 6.3.1 프락시 서버 배치

#### 출구 프락시

로컬 네트워크의 출구에 위치한다. 회사 밖의 악의적인 해커들을 막는 방화벽 제공이나 인터넷 요금 절약, 트래픽 성능 개선을 위해 사용한다.

#### 접근 프락시

고객으로부터의 모든 요청을 종합적으로 처리 하기 위해 접근 지점에 위치한다.

#### 대리 프락시

프락시 서버는 대리 프락시(리버스 프락시)로 사용된다. 네트워크 웹서버의 바로 앞에 위치하여 모든 요청을 처리하고 웹서버에서 자원을 요청한다.

#### 네트워크 교환 프락시

캐시를 이용해 인터넷 교차로의 혼잡을 완화하고 트래픽 흐름을 감시하기 위해, 충분한 처리 능력을 갖춘 프락시가 네트워크 사이의 인터넷 피어링 교환 지점들에 놓일 수 있다.

### 3.2 프락시가 트래픽 처리를 하는 방법

- 클라이언트 수정 : 크롬을 비롯한 브라우저들은 수동 혹은 자동 프락시 설정을 지원한다. 클라이언트가 프락시를 사용하도록 설정되어 있다면, 클라이언트는 HTTP 요청을 바로 그리고 의도적으로 프락시로 보낸다.
- 네트워크 수정 : 클라이언트가 눈치 챌수 없도록 네트워크 인프라를 가로채서 웹 트래픽을 프락시로 가도록 하는 몇가지 기법이 있다. 이것을 인터셉트 프락시라 한다.
- DNS 이름공간 수정 : 웹서버 앞에 있는 대리 프락시는 웹 서버의 이름과 IP주소를 직접 사용한다. 그래서 모든 요청은 대리 프락시를 거쳐서 가게된다. 즉 DNS 이름 테이블을 수동 편집하거나, 적절한 프락시 서버를 계산해주는 특별한 동적 DNS 서버를 이용해서 조정 될 수있다.
- 웹 서버 수정 : HTTP 리다이렉션 명령을 클라이언트에게 돌려줌으로써 클라이언트의 요청을 프락시로 리다이렉트 하도록 설정 할수 있다.



## 6.4 클라이언트 프락시 설정

모든 브라우저는 프락시를 사용할 수 있도록 설정할 수 있다.

- 수동 설정 : 프락시를 사용하겠다고 명시적으로 설정한다.
- 브라우저 기본 설정 : 브라우저 벤더나 배포자는 브라우저를 소비자에게 전달 하기 전에 프락시를 미리 설정해 놓을 수 있다.
- 프락시 자동 설정(Proxy auto-configuration, PAC) : 자바스크립트 프락시 자동 설정 파일에 대한 URI 제공을 통해, 언제 써야 하는지, 어떤 프락시를 써야 하는지 실행할 수 있다.
- WPAD 프락시 : 자동설정 파일을 다운받을 수 있는 '설정 서버'를 자동으로 찾아주는 자동발견 프로토콜을 제공한다.

## 6.5 프락시 요청의 미묘한 특징들

### 5.1 프락시 URI는 서버 URI와 다르다

웹 서버와 웹 프락시 메시지의 문법은 서로 같지만, 한 가지 예외가 있다. 클라이언트가 프락시 대신 서버로 요청을 보내면 요청의 URI가 달라진다.
서버로 보낼때와 달리 프락시로 요청을 보낼 때, 요청줄은 완전한 URI를 갖는다
(서버는 스킴, 호스트, 포트번호 생략이 가능하다)

목적지 서버와 커넥션을 맺어야 하기 떄문에, 서버의 이름을 알 필요가 있었다.
프락시가 부상할 당시, 이미 너무 많은 서버가 배치되어 있었고 완전한 URI를 보낼 필요가 있었다.

### 5.2 가상 호스팅에서 일어나는 같은 문제

가상으로 호스팅 되는 웹 서버는 여러 웹 사이트가 같은 물리적 웹 서버를 공유한다.
따라서 웹 서버는 호스트의 정보를 요구하기 위해서 요청 메세지가 완전한 URI를 갖도록 함으로써 이 문제를 해결했다.
또한, 가상으로 호스팅 되는 웹 서버는 호스트와 포트에 대한 정보가 담겨 있는 Host 헤더를 요구한다.

### 5.3 인터셉트 프락시는 부분 URI를 받는다.

클라이언트는 자신이 프락시와 대화하고 있음을 항상 알고 있는 것은 아니다. 몇몇 프락시는 클라이언트에게는 보이지 않을 수 있기 때문이다.
두가지 경우 클라이언트는 자신이 웹 서버와 대화하고 있다고 생각하고 완전한 URI를 보내지 않을 것이다.

- 대리 프락시는 원 서버의 호스트 명과 아이피 주소를 사용해 원 서버를 대신하는 프락시 서버이다.
- 인터셉트 프락시는 네트워크 흐름에서 클라이언트에서 서버로 가는 트래픽을 가로채 캐시된 응답을 돌려주는 등의 일을 하는 프락시 서버다. 가로채는 기능이 있기 때문에 웹 서버로 보내는 URI를 얻게 될 것이다.

### 5.4 프락시는 프락시 요청과 서버 요청을 모두 다룰 수 있다.

다목적 프락시 서버는 완전 URI와 부분 URI를 모두 지원해야 한다.
완전 URI와 부분 URI를 사용하는 규칙은 다음과 같다.

- 완전한 URI가 주어졌다면, 프락시는 그것을 사용해야 한다.

- 부분 URI가 주어졌고 Host 헤더가 있다면, Host 헤더를 이용해 원 서버의 이름과 포트 번호를 알아내야 한다.

- 부분 URI가 주어졌으나 Host 헤더가 없다면, 다음의 방법으로 원 서버를 알아내야 한다.

  \- 대리 프락시라면, 프락시에 실제 서버의 주소와 포트 번호가 설정되어 있을 수 있다.

  - 이전에 어떤 인터셉트 프락시가 가로챘던 트래픽을 받았고, 그 인터셉트 프락시가 원 IP 주소와 포트번호를 사용할 수 있도록 해두었다면, 그 IP 주소와 포트번호를 사용할 수 있다.
  - 모두 실패했다면, 에러메시지를 반환해야 한다.(브라우저 업데이트등)

### 5.5 전송 중 URI 변경

프락시는 URI를 전달할 때 절대 경로를 고쳐 쓰는 것을 금지한다.

### 5.6 URI 클라이언트 자동확장과 호스트 명 분석

브라우저는 프락시 존재 여부에 따라 요청 URI를 다르게 분석한다.

- 일반적인 웹 사이트 이름의 가운데 부분만 입력했다면, 'www'를 붙이고 '.com'을 붙인다.
- 몇몇 브라우저는 해석할 수 없는 URI를 서드파티 사이트로 넘기기도 하는데, 오타 교정을 시도하고 사요자가 의도했을 URI를 제시한다.
- DNS는 호스트 명의 앞부분만 입력하면 자동으로 도메인을 검색하도록 설정 되어 있다. 'naver.com'에서 'mail'을 입력하면 자동으로 'mail.naver.com'을 찾아본다.

### 5.7 프락시 없는 URI 분석

브라우저는 유효한 호스트 명이 발견될 때까지 다양한 호스트 명의 가능성들을 검색한다.

- 단계1 : 사용자는 'naver'를 브라우저의 URI에 입력했다. 브라우저는 기본 스킴을 '[http://'로](http://xn--'-ky7m/), 기본 포트를 '80'으로, 기본 경로를 '/'로 간주한다.
- 단계2 : 브라우저는 호스트 'naver'를 찾아본다. 이것은 실패한다.
- 단계3 : 브라우저는 자동으로 확장한 후, DNS 에 'www.naver.com'의 주소 분해를 요청한다. 이것은 성공한다.
- 단계4 : 이제 브라우저는 www.naver.com 으로 연결하는데 성공한다.

### 5.8 명시적인 프락시를 사용할 때의 URI 분석

명시적인 프락시를 사용한다면, 브라우저의 확장들중 어느 것도 수행할 수 없다. 브라우저의 URI가 프락시를 그냥 지나쳐버리기 때문이다.

### 5.9 인터셉트 프락시를 이용한 URI 분석

호스트 명 분석은 보이지 않는 인터셉트 프락시와 함께일 때 약간 달라지는데, 왜냐하면 클라이언트의 입장에서 프락시는 존재하지 않는 것이기 때문이다.
DNS가 성공할 때까지 호스트 명을 자동확장하는 브라우저를 사용할 때, 동작은 프락시가 아닌 서버의 경우와 별 차이가 없다. 그러나 서버로의 커넥션이 만들어졌을 때는 분명한 차이가 발생한다.



## 6.6 메시지 추적

오늘날에는 웹 요청이 클라이언트에서 서버로 향하는 도중에 둘 이상의 프락시를 지나게 되는 것은 드문 일이 아니다.

### 6.1 Via 헤더

Via 헤더 필드는 메시지가 지나는 각 중간 노드(프락시나 게이트웨이)의 정보를 나열한다.
메시지가 또 다른 노드를 지날 때마다, 중간 노드는 Via 목록의 끝에 반드시 추가되어야 한다.

**Via 문법** : Via 헤더 필드는 쉼표로 구분된 경유지의 목록이다. 각 경유지는 개별 프락시 서버나 게이트웨이 홉을 나타내며 그들 중간 노드의 프로토콜과 주소에 대한 정보를 담고 있다.

- 프로토콜 이름 : HTTP, HTTPS, FTP...
- 프로토콜 버전 : '1.0', '1.1'...
- 노드 이름 : 호스트와 포트번호...
- 노드 코멘트
- Via 요청과 응답 경로

Via가 개인정보 보호와 보안에 미치는 영향 : 프락시 서버가 네트워크 방화벽의 일부인 경우 프락시는 호스트이 이름과 포트 및 정보를 전달해서는 안된다.

### 6.2 TRACE 메서드

HTTP/1.1 TRACE 메서드는 프락시의 연쇄를 따라가면서 어떤 프락시를 지나가고 요청 메시지를 수정하는 관찰/추적 할수 있다.
(디버깅에 매우 유용한다)

#### Max-Forwards

TRACE 메시지는 프락시들이 몇 개나 있든 신경 쓰지 않고 목적지 서버로의 모든 경로를 여행한다. 프락시늬 갯수를 제한하기 위해 Max-Forwards 헤더를 사용 할 수 있다. 테스트나, 무한루프 방지를 위해 사용된다.



## 6.7 프락시 인증

- 제한된 컨텐츠에 대한 요청이 프락시 서버에 도착했을 때, 프락시 서버는 407 상태 코드를 어떻게 그러한 자격을 제출할 수 있는지 설명해주는 Proxy-Authenticate 헤더 필드와 함께 반환 할 수 있다
- 407 응답을 받으면, 로컬 데이터베이스를 확인해서든 사용자에게 물어봐서든 요구되는 자격을 수집한다.
- 자격을 획득하면, 클라이언트는 요구되는 자격을 Proxy-Authorization 헤더 필드에 담아서 요청을 다시 보낸다.
- 자격이 유효하다면, 프락시는 원 요청을 연쇄를 따라 통과시킨다. 유효하지 않다면 407 응답을 보낸다.

## 6.8 프락시 상호운용성

### 8.1 지원하지 않는 헤더와 메서드 다루기

프락시는 이해 할 수 없는 헤더 필드는 반드시 그대로 전달해야 하며, 여러개 일 경우 순서도 반드시 유지해야한다.
지원하지 않는 메서드를 통과시킬 수 없는 프락시는 대부분의 네트워크에서 살아남지 못한다.
HTTP/1.1은 메서드를 확장하는 것을 허용하고 있다.

### 8.2 OPTIONS : 어떤 기능을 지원하는지 알아보기

OPTIONS 요청의 URI가 다음과 같이 별표(*)라면, 요청은 서버 전체의 능력에 대해 묻는 것이 된다.
만약 URI가 실제 리소스라면, OPTIONS 요청은 특정 리소스에 대해 가능한 기능들을 묻는 것이다.
성공한다면, 200 응답을 리소스에 대해 가능한 선택적인 기능 서술과 함께 보낸다.
HTTP/1.1은 Allow 헤더 하나만을 서버에 의해 어떤 메서드가 지워되는지 서술하게 한다.

### 8.3 Allow 헤더

Allow 엔티티 헤더 필드는, 요청 URI에 의해 식별되는 자원에 대해 지원되는 메서드를 모두 열거한다.
(ex] Allow : GET, HEAD, PUT)
모두 사용할 의무는 없으나, 응답에는 Allow 헤더를 포함시켜야 한다.



## Reference

[프록시란?](https://ko.wikipedia.org/wiki/%ED%94%84%EB%A1%9D%EC%8B%9C_%EC%84%9C%EB%B2%84)

[CDN이란?](https://en.wikipedia.org/wiki/Content_delivery_network)
