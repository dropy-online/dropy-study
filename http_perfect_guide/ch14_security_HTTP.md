# 14장 보안 HTTP
## HTTPS 
- HTTPS는 HTTP를 안전하게 만드는 방식 중에 가장 인기 있는 방식
    - 모든 주류 브라우저와 서버에서 지원

### 동작 방식
- HTTPS를 사용할 때, 모든 HTTP 요청과 응답 데이터는 네트워크로 보내지기 전에 **암호화**된다. 
- HTTPS는 HTTP(애플리케이션 계층)의 하부에 **전송 레벨 암호 보안 계층**을 제공함으로써 동작한다.
    - 이 보안 계층은 SSL 또는 TLS를 이용하여 구현됨 (둘은 매우 비슷)
        - 안전 소켓 계층(Secure Sockets Layer, SSL)
        - 전송 계층 보안(Transport Layer Security, TLS)
### 특징
- 보안 HTTP를 사용하기 위해 웹 클라이언트와 서버가 프로토콜을 처리하는 로직을 크게 변경할 필요 없음
    - 복잡한 인코딩/디코딩 작업은 대부분 SSL 라이브러리 내부에서 처리됨

## 디지털 암호
### 기초
- 암호
- 키
- 대칭키 암호 체계
    - 인코딩과 디코딩에 같은 키를 사용하는 알고리즘
- 비대칭 암호 체계
    - 인코딩과 디코딩에 다른 키를 사용하는 알고리즘
- 공개키 암호법
    - 사전에 비밀키를 나눠갖지 않은 사용자들이 안전하게 통신할 수 있도록 한다.
    - 이 방식에는 공개키와 비밀키가 존재함
    - 일반적으로, 공개키 암호 방식은 비밀키 암호 방식보다 계산이 복잡하다는 단점이 있기 때문에, 효율을 위해서 **비밀키 암호(=대칭 암호)**와 함께 사용됨
- 디지털 서명
- 디지털 인증서

### 암호화를 사용함으로써 얻는 장점
- 정보 도청 방지
- 메시지 변조 방지
- 특정 메시지나 트랜잭션의 저자임을 증명하는 수단

### 암호
- 메시지를 인코딩하는 어떤 특정한 방법과 나중에 그 비밀 메시지를 디코딩하는 방법
- 인코딩되기 전의 원본 메시지 = 텍스트 or 평문
- 암호화가 적용되어 코딩된 메시지 = 암호문

### 디지털 암호
- 디지털 키 값
    - 인코딩과 디코딩 알고리즘에 대한 입력값
    - 매우 큰 키를 지원하는 것이 가능해져서, 단일 암호 알고리즘으로 키의 값마다 다른 수조 개의 가상 암호 알고리즘을 만들어낼 수 있게 됨
    - 키가 길수록 인코딩의 많은 조합이 가능해져, 무작위로 추측한 키에 의한 크래킹이 어려워진다.
- 코딩 알고리즘(암호 알고리즘)
    - 데이터를 받아서 알고리즘과 키의 값에 근거하여 인코딩하거나 디코딩하는 함수

## 대칭키 암호법
- 발송자와 수신자 모두 통신을 위해 **비밀키**를 똑같이 공유한다.
- 발송자는 공유된 비밀키를 이용해 메시지를 암호화하고, 그 결과인 암호문을 수신자에게 발송한다.
- 수신자는 암호문을 받은 뒤 공유된 비밀키를 사용하여, 원래의 평문을 복원하기 위해 해독 함수를 적용한다.

### 잘 알려진 대칭키 암호 알고리즘
- DES
- Triple-DES
- RC2
- RC4

### 키 길이와 열거 공격(Enumeration Attack)
- 키
    - 가능한 키 값의 개수 = 키가 몇 비트인가? + 얼마나 많은 키가 유효한가?
    - 대칭키 암호에서는 보통 모든 키 값이 유효
        - 예) 8비트 키 -> 256가지 키 값이 가능
- 키 길이
    - 사용자가 암호를 자주 바꾸지 않는 이상, 40비트 키는 적극적인 공격자로부터 안전하지 않다. (관련 추가 자료 p.363 참고)
    - Triple-DES키와 비슷한 크기인 **128비트** DES 키는 무차별 대입으로는 실질적으로 깨뜨릴 수 없다고 알려져 있다.
- 열거 공격
    - 무차별로 모든 키 값을 대입해보는 공격

### 단점
- 발송자와 수신자가 둘 다 공유키를 가져야 한다.
- 비밀 키를 생성하고, 이를 기억할 방법이 필요하다.
    - 만약, N개의 노드가 있고, 각 노드가 상대 N-1과 암호화된 데이터를 주고 받을 때, 대략 총 N^2 개의 비밀키가 필요하며, 이를 기억/관리해야 한다.

## 공개키 암호법
- 두 개의 비대칭 키를 사용한다.
    - 호스트의 메시지를 **인코딩하기 위한 키**
        인코딩 키는 모두를 위해 공개되어 있다.
    - 호스트의 메시지를 **디코딩하기 위한 키**
        - 호스트만이 개인 디코딩 키를 알고 있다.
- 특정 호스트(A)에게 보내는 메시지를 같은 키로 인코딩 할 수 있고, 호스트(A)를 제외한 누구도 그 메시지를 디코딩 할 수 없다.
    - 이러한 특징 덕분에 **기억/관리해야 하는 대칭 키의 쌍이 폭팔적으로 증가(N^2개)하는 것을 방지할 수 있음**

사진2 (p365)
<img src="https://github.com/always-awake/TIL/blob/master/images/14-1.png" />

- 공개키 암호법은 아래 3가지에 대한 정보가 알려졌더라도 비밀키를 계산할 수 없도록 확신시켜 주어야 한다.
    - 공개키
    - 가로채서 얻은 암호문 일부(네트워크 스누핑을 통해 획득한)
    - **메시지**와 그것을 암호화한 암호문(인코더에 임의의 텍스트를 넣고 실행해서 획득)

### RSA
- 아래 4가지에 대한 정보가 알려졌더라도 암호를 크래킹하여 개인 키를 찾아내는 것은 굉장히 어렵다.
    - 공개키
    - 평문의 일부
    - 암호문(공개키로 인코딩된)
    - RSA 구현 소스 코드

### 혼성 암호 체계
- 등장 배경
    - 대칭키 암호법 단점
        - 두 노드가 안전하게 의사소통 하려면 서로의 개인 키를 기억/관리하고 있어야 한다.
        - 데이터 통신 전에 개인 키를 안전한 방법으로 서로 교환해야 한다.
    - 공개키 암호법(비대칭키 암호법)
        - 계산이 느린 경향이 있음
- 혼성 암호 체계
    - a. 노드들 사이의 안전한 의사소통 채널을 수립할 때 = 공개 키 암호법 사용
    - b. 안전한 채널을 통해 임시의 무작위 대칭 키를 생성하고 교환함
    - c. 데이터를 인코딩/디코딩 할 때는 빠른 대칭키를 사용 = 대칭 키 암호법 사용

사진 3(혼성 암호 체계 사진)

## 디지털 서명
- 메시지에 붙어 있는 특별한 **암호 체크섬**

### 장점
- 메시지를 작성한 저자가 누군지 알려준다.
    - 저자는 자신의 개인키를 갖고 있기 때문에, 오직 저자만이 이 체크섬을 계산할 수 있다.
- 메시지 위조를 방지한다.
    - 공격자가 송신 중인 메시지를 수정했따면, 체크섬은 더 이상 그 메시지와 맞지 않게 된다.
    - 체크섬은 저자의 비밀 개인 키와 관련되어 있기 때문에, 위조된 메시지에 대한 올바른 체크섬을 날조해낼 수 없다.

<img src="https://github.com/always-awake/TIL/blob/master/images/14-2.png" />

## 디지털 인증서 
- 신뢰할 수 있는 기관으로부터 보증 받은 사용자나 회사에 대한 정보를 담고 있다.
- 디지털 인증서에 대한 전 세계적인 단일 표준은 없음

### 인증서 내부
- 디지털 인증서에 담기는 기본 정보
    - 대상의 이름(사람, 서버, 조직 등)
    - 유효 기간
    - 인증서 발급자(누가 이 인증서를 보증하는가)
    - 인증서 발급자의 디지털 서명
- 디지털 인증서에 담기는 추가 정보
    - 사용된 서명 알고리즘에 대한 서술적인 정보
    - 대상의 공개키

사진5(p.370)
<img src="https://github.com/always-awake/TIL/blob/master/images/14-3.png" />

### X.509 v3 인증서
- 오늘날 사용되는 대부분의 인증서는 X.509라 불리는 표준화된 서식에 따라 디지털 인증서에 담기는 정보를 저장하고 있다.
- X.509 인증서의 일부 필드들
    - 서명 알고리즘 ID
        - 서명을 위해 사용된 암호 알고리즘
    - 대상의 공개 키 정보
        - 인증 대상의 공개 키
        - 공개키에 사용된 알고리즘
        - 추가 매개변수
    - **인증 기관 서명**
        - X.509 인증서의 모든 필드에 대한 인증기관의 디지털 서명
        - 명시된 서명 알고리즘을 사용한다.
    - 자세한 필드는 p.370에 있는 표 14-2 확인하기

### 서버 인증을 위해 인증서 사용하기
- a. 최신 브라우저는 자동으로 접속한 서버에서 디지털 인증서를 가져온다.
    - 만약 서버가 인증서를 갖고 있지 않다면, 보안 커넥션은 실패
- b. 브라우저가 인증서를 받으면, 서명 기관을 검사한다. (= 인증서의 무결성 검증)
    - 브라우저는 공공이 신뢰할만한 여러 서명기관의 인증서가 이미 설치되어 있음
    - 인증서 내 공개키를 이용해 인증서의 무결성을 검증함

사진6(p.372)
<img src="https://github.com/always-awake/TIL/blob/master/images/14-4.png" />


## HTTPS 세부사항
- HTTPS는 HTTP 프로토콜에 대칭, 비대칭 인증서 기반 암호 기법의 강력한 집합을 결합한 것이다.

### HTTPS 개요
- HTTPS는 그냥 **보안 전송 계층**을 통해 전송되는 HTTP
- HTTPS는 HTTP 메시지를 TCP로 보내기 전에 먼저 그것들을 암호화하는 보안 계층으로 보낸다.
- HTTPS 보안 계층은 **SSL과 TLS**(SSL의 현대적 대체품)로 구현

### HTTPS 스킴
- http 스킴
    - a. 클라이언트는 서버에 80번(기본값) 포트로 연결
    - b. 평범한 HTTP 명령 전송
- https 스킴
    - a. 클라이언트는 서버에 443번(기본값) 포트로 연결
    - b. 핸드 셰이크
        - 바이너리 포맷으로 된 몇몇 SSL 보안 매개변수 교환
    - c. 암호화된 HTTP 명령 전송

#### 참고
- SSL 트래픽은 바이너리 프로토콜
    - SMTP, HTTP/1.1 같은 일반 텍스트 프로토콜과 달리 사람이 아닌 컴퓨터에서 읽을 수 있는 프로토콜
    - 간결함의 이점을 갖으며, 이는 전송 및 해석 속도에 영향을 줌
- SSL 트래픽은 보통 443 포트를 통해 전달됨

### 보안 전송 셋업
- HTTP
    - a. 클라이언트는 웹 서버의 80번 포트로 TCP 커넥션 수립
    - b. 생성된 TCP 커넥션을 통해 요청 HTTP 요청 메시지를 보내고, HTTP 응답 베시지를 받음
    - c. TCP 커넥션을 닫힘
- HTTPS
    - a. 클라이언트는 먼저 웹 서버의 443포트(보안 HTTP의 기본 포트)로 TCP 커넥션 수립
    - b. **SSL 핸드셰이크** (아래에 자세히 설명됨)
    - c. 클라이언트는 요청 메시지를 보안 계층으로 전송
    - d. 이 요청 메시지는 TCP로 보내지기 전에 암호화
    - e. 서버는 응답 메시지를 보안 계층으로 전송
    - f. 이 응답 메시지는 TCP로 보내지기 전에 암호화
    - g. SSL 담힘 통지
    - h. TCP 커넥션 닫힘

### SSL 핸드셰이크
- 암호화된 HTTP 메시지를 보내기 전에 클라이언트와 서버는 SSL 핸드셰이크 수행
- 과정
    - a. 클라이언트: 암호 후보 리스트를 전송, 서버의 인증서를 요구
    - b. 서버: 선택된 암호와 자신의 인증서 전송
    - c. 클라이언트: 비밀정보 전송
    - d. 클라이언트 & 서버: 키 생성
    - e. 클라이언트 & 서버: 서로에게 암호화를 시작한다고 전달

### 서버 인증서
- SSL은 상호 인증 지원
- 오늘날, 클라이언트 인증서는 웹 브라우징에선 흔히 쓰이지 않음
    - 조직의 인트라넷 같은 경우는 직원드링 정보에 접근하는 것을 제어하기 위한 목적으로 클라이언트 인증서를 사용하기도 한다.
- 보안 HTTPS 트랜잭션은 항상 **서버 인증서**를 요구한다.
    - 서버를 얼마나 신뢰할 수 있는지 평가
    - 서버 인증서는 X.509 v3에서 파생된 인증서

### 사이트 인증서 검사
- 최신 웹 브라우저들 대부분은 인증서에 대해 간단하게 기본적인 검사를 하고, 그 결과를 더 철저한 검사를 할 수 있는 방법과 함께 사용자에게 알려준다.
- 인증서 검사 과정
    - a. 날짜 검사: 브라우저는 인증서가 여전히 유효함을 확인한다.
    - b. 서명자 신뢰도 검사
        - 브라우저는 신뢰할 만한 서명 기관의 목록을 포함한 채로 배포된다.
        - 신뢰할 만한 CA가 간접적으로 서명한 인증서를 받아들이는 것을 선택할 수 있다.
    - c. 인증서의 무결성 검사
        - 서명기관의 공개키(브라우저가 이미 갖고 있는 인증서 내에 있는 공개키)를 서명에 적용하여 그의 체크섬과 비교(p.372 참고)
    - d. 사이트 신원 검사
        - 브라우저는 인증서의 도메인 이름이 대화 중인 서버의 도메인 이름과 비교하여 맞는지 검사함
        - 검사 결과, 호스트명과 인증서의 신원이 맞지 않다면, 사용자에게 알리거나 잘못된 인증서 에러와 함꼐 커넥션을 끊는다.
    
## 진짜 HTTPS 클라이언트
- 직접 해보기!

## 프락시를 통한 보안 트래픽 터널링
- 웹 프락시 서버
    - 클라이언트를 대신하여 웹 서버에 접근
    - 방화벽 라우터가 HTTP 트래픽의 교환을 허락한 유일한 장치
    - 바이러스 검사나 기타 콘텐츠 제어 수행

### HTTPS와 프락시 함께 사용할 때 발생하는 문제점
- 클라이언트가 암호화된 데이터(서버의 공개키 이용)를 서버로 보낼 때, 프락시는 더 이상 HTTP 헤더를 읽을 수 없음
    - 즉, 프락시는 요청을 어디로 보내야 하는지 알 수 없음
### 해결 방법 - HTTPS SSL 터널링 프로토콜
- 동작 방식
    - a. 클라이언트는 HTTP의 CONNECT 메서드를 이용하여, 프락시에게 희망하는 호스트와 포트번호로 연결을 요청한다.
    - b. 프락시는 요청을 평가하여 그것이 유효하고, 사용자가 그러한 커넥션을 요청할 수 있도록 허가를 받았는지 확인한다.
    - c. 요청 처리가 완료되면, 클라이언트와 서버 사이에는 데이터가 직접적으로 오갈 수 있는 **터널**이 생긴다.
    - d. 커넥션을 수립하기 위한 핸드셰이크가 성공했다면, SSL 데이터 전송이 시작된다.
