#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

#define BUFLEN 512  //Max length of buffer

void validate_parameters(int argc, char **argv){
    if (argc != 3) {
        printf("Error: ./client <IPAddress> <PorNumber>\n");
        exit(EXIT_FAILURE);
    }
}

int create_new_socket(){
    //Creates a new socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
       printf("Failed to create new socket.");
       exit(EXIT_FAILURE);
    }
    return sockfd;
}

void initialize_server_address(char * server_ip, struct sockaddr_in * server_address, int portNumber){
  bzero(server_address, sizeof(* server_address));
  server_address->sin_family      = AF_INET;
  server_address->sin_port        = htons(portNumber);

  //Converts server address IP from string to binary and saves in server_address
  if (inet_pton(AF_INET, server_ip, &(server_address->sin_addr) ) <= 0) {
      printf("Error to convert server ip from text to binary.\n");
      exit(EXIT_FAILURE);
  }
}

void sentMessageToServer(int sockfd, char * message, struct sockaddr * server_address, socklen_t slen){
  if (sendto(sockfd, message, strlen(message) , 0 , server_address, slen)==-1){
    printf("Error: sendto() method.\n");
    exit(EXIT_FAILURE);
  }
}

void receiveMessageFromServer(int sockfd, char * buf, struct sockaddr * server_address, socklen_t * slen){
  if (recvfrom(sockfd, buf, BUFLEN, 0, server_address, slen) == -1){
    printf("Error: recvfrom() method.\n");
    exit(EXIT_FAILURE);
  }
}

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char **argv)
{
    struct sockaddr_in server_address;
    socklen_t slen;
    int sockfd;
    char buf[BUFLEN];
    char message[BUFLEN];

    validate_parameters(argc, argv);

    sockfd = create_new_socket();
    initialize_server_address(argv[1], &server_address, atoi(argv[2]));

    for(;;){
        printf("Enter message : ");
        gets(message);

        //send the message
        slen=sizeof(server_address);
        sentMessageToServer(sockfd, message, (struct sockaddr *) &server_address, slen);

        memset(buf,'\0', BUFLEN);
        receiveMessageFromServer(sockfd, buf, (struct sockaddr *) &server_address, &slen);

        puts(buf);
    }

    close(sockfd);
    return 0;
}