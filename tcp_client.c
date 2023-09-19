#include <stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>

int main()
{
int clientsock;
struct sockaddr_in servaddr;
char sendl[100],recvl[100],ex[100]="exit";
bzero(sendl,100);
bzero(recvl,100);
bzero(&servaddr,sizeof(servaddr));
clientsock=socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_family= AF_INET;
servaddr.sin_port=htons(12347);
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
connect (clientsock,(struct sockaddr*)&servaddr,sizeof(servaddr));
while(1)
{
fgets(sendl,100,stdin);
send(clientsock,sendl,strlen(sendl),0);
if(strncmp(sendl,ex,4)==0)
break;
bzero(sendl,100);
recv(clientsock,recvl,100,0);
printf("Recieved from server %s",recvl);
if(strncmp(recvl,ex,4)==0)
break;
bzero(recvl,100);
}
close(clientsock);
return 0;
}

