// File: morsecast.c
// Author: Stephen Rozanc October 2015
// If you ever find yourself in grave danger at home, and have no acess to a phone
// Run morsecast to broadcast SOS via UDP Datagrams via your local subnet (LAN)
// Hopefully someone's listening !!

// Standard Headers:
#include <stdio.h> // Standard Printing/IO Functions
#include <string.h> // String Manipulation Functions
#include <stdlib.h> // Standard Functions including exit();

// Network Includes:
#include <arpa/inet.h>
#include <sys/socket.h>

// Our Bomb-out Function:
void die(char *s) {
	perror(s);
	exit(1);
}

int main(void) {

	printf("In trouble?? OK, Let's get you some help!\n");

}
