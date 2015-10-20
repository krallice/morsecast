// File: morsecast.c
// Author: Stephen Rozanc October 2015
// If you ever find yourself in grave danger, and have no access to a phone --
// run morsecast to broadcast SOS via UDP Datagrams on your local subnet (LAN)
// Hopefully someone's listening !!

// Standard Headers:
#include <stdio.h> // Standard Printing/IO Functions
#include <string.h> // String Manipulation Functions
#include <stdlib.h> // Standard Functions including exit();

// Network Includes:
#include <arpa/inet.h>
#include <sys/socket.h>

#define DESTINATION "255.255.255.255"
#define DESTPORT 7474
	
// Our Bomb-out Function:
void die(char *s) {
	perror(s);
	exit(1);
}

int main(void) {

	// Useless preamble:
	printf("In trouble?? OK, Let's get you some help!\n");
	
	// Create an address structure in memory for the connection
	// Per man pages, this struct looks like this:
	/*
		struct sockaddr_in {
			sa_family_t    sin_family; address family: AF_INET 
			in_port_t      sin_port;   port in network byte order 
			struct in_addr sin_addr;   internet address 
		};
		Internet address: 
		struct in_addr {
			uint32_t       s_addr;     address in network byte order 
		};
	*/
	// Dial in one of these structures for our destination socket:
	struct sockaddr_in sockAddr;
	
	// Create a socket filedescriptor for an INET/Datagram through UDP socket:
	int sockfd, i, sockLen=sizeof(sockAddr);
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		die("socket");
	}

	// Enable Broadcast on the socket:
	int broadcastOn = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastOn, sizeof(broadcastOn)) == -1) {
		die("setsockopt");
	}
	
	// Zero out the socket:
	memset((char *) &sockAddr, 0, sockLen);
}
