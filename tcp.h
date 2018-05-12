/*************************************************************************
    > File Name: tcp.h
    > Author: J1ac Shi
    > Mail: zjsxsjc@gmail.com 
    > Created Time: 2018-04-24
 ************************************************************************/
#include<signal.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<strings.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<string>
#include<fcntl.h>
//#define SERV_PORT 9877
#define MAXLINE 100
void ftpd(int listenfd);
void receive_and_save_file(int connfd);
