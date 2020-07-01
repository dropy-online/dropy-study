# HTTP 2.0

구글에서 페이지 로드 시간을 줄이기 위한 SPDY 프로토콜을 새로 만들면서부터 시작되었습니다.  
이를 주시하던 HTTP 프로토콜 그룹은 이에 대한 표준을 제작하고 `SPDY`를 출발점으로 채택합니다.  
그리고 기존의 TCP 커넥션을 제대로 활용하지 못하는 `HTTP 1.1`을 다음과 같이 개선하게됩니다.

## 개요 및 용어

기본적으로 **줄바꿈**을 통해 구분하여 일반텍스틀 활용하던 `HTTP 1.1` 과 달리 `HTTP 2.0` 은 바이너리 값으로 인코딩 된 프레임을 이용합니다. 이와 관련해서 용어를 나열하자면 다음과 같습니다.

- 스트림 : 커넥션 상의 데이터 흐름
- 메세지 : 논리적인 요청/응답 (즉, 프레임의 시퀀스)
- 프레임 : HTTP 2.0의 데이터 원자단위를 의미하며 프레임 헤더가 1개씩 들어감

![](https://kr.object.ncloudstorage.com/load0ne/http_perfect_guide/http2_1.png)


## 멀티 플렉싱

HTTP 1.1 의 비효율을 초래하는 큰 원인 중 하나를 HOL(head-of-line)을 들 수 있습니다.  이를 HTTP 2.0 은 마치 TCP 동작과 같이 메세지를 독립적인 스트림 단위로 쪼개서 다시 재조립 하는 절차를 통해 해결합니다.
즉, 여러 요청/응답이 전혀 간섭되지 않고 병렬로 동작하게 됩니다.

![](https://kr.object.ncloudstorage.com/load0ne/http_perfect_guide/http2_2.png)

## 스트림 우선순위

HTTP 2.0은 클라이언트 측에서 스트림에 가중치를 부여하여 우선순위 트리를 만들 수 있습니다.  
예를 들어 일반적인 웹통신에서, 아마 브라우저는 HTML, CSS, JS를 먼저 받고 이에 대한 이미지 등 고용량 리소스를 나중에 받고 싶어 할 것 입니다.

## 출처 당 하나의 연결

HTTP 1.1의 경우 성능을 더 끌어올리기 위해서 병렬 커넥션 등을 활용하는 등 다양한 시도를 했지만, 결국 여러 TCP 커넥션이 생성된다는 것은 그에 대한 TCP 연결성립을 위한 비용도 가중된다는 것을 의미합니다.
따라서, 단 하나의 연결만 사용한다는 것은 큰 장점이 될 수 있습니다.

## 서버 푸쉬

`PUSH_PROMISE` 프레임을 통해 시작되며, 서버측에서 클라이언트에서 필요한 리소스를 미리 예측해서 푸쉬할 수 있습니다. 이는 요청 메시지 프레임보다 일찍 도착해야합니다. 또한 `RST_STREAM` 프레임을 이용해서 클라이언트에선 이를 거부할 수 있습니다. (예. 이미 캐시된 리소스)

## 헤더 압축

헤더는 생각보다 꽤 많은 대역폭을 잡아먹습니다. 중복되는 경우가 많으며, 특히 쿠키의 경우는 더 심하겠죠. HTTP 2.0에서는 이를 HPACK을 이용해서 압축합니다. 

HPACK에서는 Huffman Code 라는 무손실 압축 알고리즘을 사용하는데 실제 헤더가 80% 이상 압축되는 모습을 보였다고 합니다.  
이이 알고리즘은 간단히 요약하면 다음과 같은 느낌인거 같습니다 (자세히 찾아보진 않아서 확실하진 않음)

아래와 같이 두 요청이 있다고 칩시다

```none
<Request_1>
Method: GET
Scheme: https
Host: example.com
Path: /channel/slide_1.png
Accept: image/jpeg
User-Agent: Mozilla ...

<Request_2>
Method: GET
Scheme: https
Host: example.com
Path: /channel/slide_2.png
Accept: image/jpeg
User-Agent: Mozilla ...
```

그럼 각 요청에 대해 색인을 부여하고 요청을 이렇게 보냅니다.  
사실상 중복되는 헤더가 많을텐데 이런식으로 압축하는 듯 합니다.

```none
<Request_1>
index : 1
Method: GET
Scheme: https
Host: example.com
Path: /channel/slide_1.png
Accept: image/jpeg
User-Agent: Mozilla ...

<Request_2>
index : 1
Path: /channel/slide_2.png 
```
