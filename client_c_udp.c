//client_c_udp.c
//look the example from http://www.linuxhowtos.org/data/6/client_udp.c I use the skeleton from the original code

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void error(const char *);
int main(int argc, char *argv[])
{
   int sock, n;
   unsigned int length;
   struct sockaddr_in server, from;
   struct hostent *hp;
   char buffer[256];
   
   if (argc != 3) { printf("Usage: server port\n");
                    exit(1);
   }
   sock= socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("socket");

   server.sin_family = AF_INET;
   hp = gethostbyname(argv[1]);
   if (hp==0) error("Unknown host");

   bcopy((char *)hp->h_addr, 
        (char *)&server.sin_addr,
         hp->h_length);
   server.sin_port = htons(atoi(argv[2]));
   length=sizeof(struct sockaddr_in);
   printf("Enter string: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);

   if(strlen(buffer)>129){
    printf("the maximum length of input is 128\n");
    close(sock);
    return 0;
   }
   //check whether all input is integer
   for(int i = 0; i< strlen(buffer); i++){
    if(buffer[i]< 48 || buffer[i]> 57){
      if(buffer[i] != 10){
        printf("Sorry, cannot compute!\n");
        close(sock);
        return 0;
      }
    }
   }

   n=sendto(sock,buffer,
            strlen(buffer),0,(const struct sockaddr *)&server,length);

   
   if (n < 0) error("Sendto");
   


   n = recvfrom(sock,buffer,256,0,(struct sockaddr *)&from, &length);
   if (n < 0) error("recvfrom");
   write(1,buffer,n); 
   //printf("this is the length of buffer: %ld\n", strlen(buffer));

   //a while loop to check whether we get only one digit feedback, if so, close the program 
   while(strlen(buffer)>15){
    memset(buffer,0,255);
    n = recvfrom(sock,buffer,256,0,(struct sockaddr *)&from, &length);
    if (n < 0) error("recvfrom");
    write(1,buffer,n);
    if(strlen(buffer)< 16) {
      //printf("oh, it will close\n");
      close(sock);
      return 0;
    }
  }
  close(sock);
  return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}