#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUFF_SIZE 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd) {
	char buff[BUFF_SIZE];
	int n;
	for (;;) {
		memset(buff, 0, sizeof(buff));
		printf("Enter the string : ");

        // 메세지를 버퍼에 저장 후 전송
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		write(sockfd, buff, sizeof(buff));

		memset(buff, 0, sizeof(buff));

        // 서버의 메세지를 버퍼에 저장 후 프린트
		read(sockfd, buff, sizeof(buff));
		printf("From Server : %s", buff);

        // exit 메세지가 오면 함수 종료
		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
	}
}

int main() {
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	memset(&servaddr, 0, sizeof(servaddr));

	// IP, 포트 할당
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// 연결
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	func(sockfd);

	close(sockfd);
} 
