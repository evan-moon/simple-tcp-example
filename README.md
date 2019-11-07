# Simple TCP Example Client and Server
`tcpdump`와 `netstat`을 사용하여 TCP의 핸드쉐이크와 상태 변경 과정을 알아보기 위한 예제. 클라이언트와 서버가 간단한 메세지를 주고받는 기능 밖에 없다. 먼저 요청을 종료하고 싶은 쪽이 `exit`라고 보내고 상대방도 `exit`라고 입력하면 연결이 종료된다.

## 컴파일
```bash
$ gcc ./client.c -o client
$ gcc ./server.c -o server
```

## 실행
```bash
$ ./client
$ ./server
```