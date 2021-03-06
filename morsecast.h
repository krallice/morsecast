// File: morsecast.h
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

// Global Preprocessor Defines:
#define DESTINATION "255.255.255.255"
#define DESTPORT 7474
#define BUFFERLEN 32
#define MSGLEN 48

// TOGGLEMORSE = 1 -> Encode String into Morse Code
// TOGGLEMORSE = 0 -> Send PlainText:
#define TOGGLEMORSE 1

// Our lookups for Alpha -> Morse Translation:
#define LOOKUPLEN 27
char *lookupAlpha[LOOKUPLEN] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
					"q", "r", "s", "t", "u", "v", "w", "x", "y", "z", " "	};

char *lookupMorse[LOOKUPLEN] = { "x- ", "-xxx ", "-x-x ", "-xx ", "x ", "xx-x ", "--x ", "xxxx ", "xx ", "x--- ", "-x- ", "x-xx ", "-- ", "-x ", "--- ", "x--x ",
					"xx-x ", "x-x ", "xxx ", "- ", "xx- ", "xxx- ", "x-- ", "-xx- ", "-x-- ", "--xx ", " / ",   	};
