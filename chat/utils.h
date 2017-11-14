#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFLEN 512  //Max length of buffer

typedef struct Client {
  int portNumber;
  char iPAddress[20];
  char nickname[50];
} Client;

enum MESSAGE_TYPE {
  REGISTER_USER=33,
  NORMAL=2
};
