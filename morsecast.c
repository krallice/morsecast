// File: morsecast.c
// Author: Stephen Rozanc October 2015
// If you ever find yourself in grave danger, and have no access to a phone --
// run morsecast to broadcast SOS via UDP Datagrams on your local subnet (LAN)
// Hopefully someone's listening !!

// Our own header file:
#include "morsecast.h"
	
// Our Bomb-out Function:
void die(char *s) {
	perror(s);
	exit(1);
}

int main(int argc, char *argv[]) {

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
	int sockfd, sockLen=sizeof(sockAddr);
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

	// INET/IP Socket on DESTPORT to DESTINATION:
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(DESTPORT);
	inet_aton(DESTINATION, &sockAddr.sin_addr);

	// Morse Translate multiple characters:

	// Get our string to encode & also generate it's length:
	//char sendString[10] = "emma rules";

	char sendString[MSGLEN];
	int sendStringLen;

	if ( argc < 2 ) {
		printf("Please enter a lowercase message (spaces allowed): ");
		fgets(sendString, MSGLEN, stdin);
		sendStringLen = strlen(sendString) - 1;
	} else {
		memcpy(sendString,argv[1],strlen(argv[1])+1);
		sendStringLen = strlen(sendString);
	}

	char terminatingString[3] = "! ";
	printf("\nEncoding String: %s\n", sendString);

	// Foreach character in our sendString:
	int i, j, encodedMessage[sendStringLen];
	for ( i = 0; i < sendStringLen; i++ ) {
		
		// Loop through our Lookup Tables:
		for ( j = 0; j < LOOKUPLEN; j++ ) {
			
			// If we have a match, populate our encodedMessage integer array
			// encodedMessage holds the array elements of lookupMorse in order
			// in order to codify our ascii --> morse representation:
			if ( sendString[i] == lookupAlpha[j][0] ) {
				encodedMessage[i] = j;
			}
			if ( j == LOOKUPLEN ) {
				encodedMessage[i] = LOOKUPLEN + 1;
			}
		}
	} 

	// Decode for user output:
	printf("Encoded Message is: ");
	for ( i = 0; i < sendStringLen; i++ ) {
		printf("%s ", lookupMorse[encodedMessage[i]]);
	}
	printf("\n\n");

	// Main Loop (Call for help!):
	printf("OK, Socket setup went well, let's do this!\n\n");
	while (1) {

		// For each of our sendString Characters:	
		for ( i = 0; i < sendStringLen; i++ ) {
			
			// Use our socket filedescriptor, Send BUFFERLEN worth of sendString through to sockAddr:
			// Send our Morse Character:
			if (sendto(sockfd, lookupMorse[encodedMessage[i]], strlen(lookupMorse[encodedMessage[i]]), 0, (struct sockaddr* )&sockAddr, sockLen) == -1) {
				die("sendto()");
			} else {
				printf("Send UDP Datagram to %s with content %s\n", DESTINATION, lookupMorse[encodedMessage[i]]);
			}
		}
		
		// Send our terminatingString to notify listeners that broadcast is over and about to loop:
		if (sendto(sockfd, terminatingString, strlen(terminatingString), 0, (struct sockaddr* )&sockAddr, sockLen) == -1) {
			die("sendto()");
		} else {
			printf("Send UDP Datagram to %s with content %s\n", DESTINATION, &terminatingString);
		}
		
		// End of one cycle (Message Complete). Wait 3seconds, resend!
		printf("End of Message, Waiting to Resend\n\n");
		sleep(3);
	}
	
	// Code should never reach here; but for good practice:
	close(sockfd);
	return 0;
}
