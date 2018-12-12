#include "main.h"

void doprocessing (void* data) {
	int sock = *(int*)data;
	int n;
	char buffer[256];
	bzero(buffer,256);
	n = read(sock,buffer,255);

	if (n < 0) {
		perror("ERROR reading from socket");
		exit(1);
	}

	printf("Here is the message: %s\n",buffer);
	n = write(sock,"I got your message",18);

	if (n < 0) {
		perror("ERROR writing to socket");
		exit(1);
	}

}

