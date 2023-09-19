#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>
int main()
{
int listen_fd,comm_fd;
char str[100],ex[100]="exit";
struct sockaddr_in servaddr;
listen_fd= socket(AF_INET,SOCK_DGRAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(12348);
servaddr.sin_addr.s_addr=INADDR_ANY;
bind (listen_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
socklen_t serlen=sizeof(servaddr);
while(1)
{
bzero(str,100);
recvfrom(listen_fd,str,100,0,(struct sockaddr*)&servaddr,&serlen);
printf("%s",str);
if(strncmp(str,ex,4)==0)
break;
bzero(str,100);
fgets(str,100,stdin);
sendto(listen_fd,str,strlen(str),0,(struct sockaddr*)&servaddr,serlen);
if(strncmp(str,ex,4)==0)
break;
}
close(listen_fd);
}
