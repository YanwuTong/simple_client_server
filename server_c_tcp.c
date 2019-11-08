//server_c_tcp.c
//look the example from http://www.linuxhowtos.org/data/6/client.c I use the skeleton from the original code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[255];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,255);

     //this is a try
     int temp;
     char result[255];
     bzero(result,255);
     n = read(newsockfd,buffer,255);

     while(1){
     	//printf("Strat while loop\n");
     	memset(result,0,255);
     	//n = read(newsockfd,buffer,255);
     	n = strlen(buffer);
     	if (n < 0) error("ERROR reading from socket");

     	//printf("Get information: %s\n", buffer);
     	//printf("length of buffer%ld\n", strlen(buffer));

        //check whether all input is integer, if so, add them together
     	for(int i = 0; i < strlen(buffer); i++){
     		if(buffer[i] != 10){
	     		//printf("current index is: %d,buffer: %d\n",i, buffer[i]);
    	 		if(buffer[i] < 48 || buffer[i] > 57){
     				n = write(newsockfd, "Sorry, cannot compute!\n", strlen("Sorry, cannot compute!\n"));
     				close(newsockfd);
     				close(sockfd);
     				return 0;
     			}
     			else{
     				temp = temp + buffer[i] - 48;
     			}
     		}
     	}

        //send the result to the client
     	sprintf(result,"From Server: %d\n",temp);
     	n = write(newsockfd,result, strlen(result));
     	if (n < 0) error("ERROR writing to socket");
     	//printf("Send information: %s\n", result);

        //the while is done once we get a result with one digit
     	if(temp < 10){
     		close(newsockfd);
     		close(sockfd);
     		return 0;
     	}

        //reset the input and result
     	memset(buffer,0,255);
     	sprintf(buffer, "%d", temp);
     	temp = 0;
     	//printf("Reset successful\n");
     }
     close(newsockfd);
     close(sockfd);
     return 0;
     //this is the end of the try
}