//server_c_udp.c
//look the example from http://www.linuxhowtos.org/data/6/server_udp.c I use the skeleton form the original code

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
   int sock, length, n;
   socklen_t fromlen;
   struct sockaddr_in server;
   struct sockaddr_in from;
   char buf[1024];

   if (argc < 2) {
      fprintf(stderr, "ERROR, no port provided\n");
      exit(0);
   }
   
   sock=socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("Opening socket");
   length = sizeof(server);
   bzero(&server,length);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr=INADDR_ANY;
   server.sin_port=htons(atoi(argv[1]));
   if (bind(sock,(struct sockaddr *)&server,length)<0) 
       error("binding");
   fromlen = sizeof(struct sockaddr_in);

   char temp [255];
   int result;
   while (1) {
    //printf("this is the first loop\n");
       result = 0;
       n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
       if (n < 0) error("reveive nothing");
       //write(1,"Received a datagram: ",21);
       //write(1,buf,n);
       //add number together
       for(int i = 0; i < strlen(buf); i++){
        //printf("this is the value for buf[%d]: %d\n", i, buf[i]);
        if(buf[i]!=10){
          result = result + buf[i] - 48;
        }
       }
       sprintf(temp, "From server: %d\n", result);
       n = sendto(sock,temp,strlen(temp),0,(struct sockaddr *)&from,fromlen);
       if (n  < 0) error("send nothing");

       //this is a try
       while(1){
        //printf("this is the second loop\n");
        memset(buf, 0, 255);
        sprintf(buf,"%d",result);
        //printf("this is our new buf: %s\n", buf);
        memset(temp, 0, 255);
        if(result > 10){
          //printf("ok, we have a reslut > 10\n");
          result = 0;
          for(int i = 0; i < strlen(buf); i++){
            result = result + buf[i] - 48;
          }
          sprintf(temp, "From server: %d\n", result);
          n = sendto(sock,temp,strlen(temp),0,(struct sockaddr *)&from,fromlen);
          if (n  < 0) error("send nothing");
        }
        else{
          result = 0;
          break;
        }
       }
       result = 0;
   }
   return 0;
 }