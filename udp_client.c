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
clientsock=socket(AF_INET,SOCK_DGRAM,0);
servaddr.sin_family= AF_INET;
servaddr.sin_port=htons(12348);
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
bind (clientsock,(struct sockaddr*)&servaddr,sizeof(servaddr));
socklen_t clen=sizeof(servaddr);
while(1)
{
fgets(sendl,100,stdin);
sendto(clientsock,sendl,strlen(sendl),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(strncmp(sendl,ex,4)==0)
break;
bzero(sendl,100);
recvfrom(clientsock,recvl,100,0,(struct sockaddr*)&servaddr,&clen);
printf("Recieved from server %s",recvl);
if(strncmp(recvl,ex,4)==0)
break;
}
close(clientsock);
return 0;
}

