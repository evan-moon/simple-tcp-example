#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUFF_SIZE 80 
#define PORT 8080 
#define SA struct sockaddr 

void func(int sockfd) { 
	char buff[BUFF_SIZE]; 
	int n;
	for (;;) { 
		bzero(buff, BUFF_SIZE); 

		// 클라이언트의 메세지를 버퍼에 저장 후 프린트
		read(sockfd, buff, sizeof(buff)); 
		printf("From client: %s\t To client : ", buff); 

		bzero(buff, BUFF_SIZE); 

        // 서버 메세지를 버퍼에 저장 후 전송
		n = 0; 
		while ((buff[n++] = getchar()) != '\n') 
			; 

		write(sockfd, buff, sizeof(buff)); 

		// exit 메세지가 오면 함수 종료
		if (strncmp("exit", buff, 4) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		} 
	} 
} 

int main() { 
	int sockfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cli; 

	// Raw 소켓 생성
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
        
	bzero(&servaddr, sizeof(servaddr)); 

	// IP, 포트 할당
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 

	func(connfd); 

	close(sockfd); 
} 
