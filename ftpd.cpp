#include"tcp.h"

void ftpd(int listenfd){
    socklen_t len;
    struct sockaddr_in cli_addr;
    int connfd;
    connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &len);
    if(connfd == -1){
        perror("accept error");
        exit(0);
    }
    int pn = fork();
    if(pn == -1){
        perror("fork error");
        exit(0);
    }else if(pn == 0){
    receive_and_save_file(connfd);
        exit(0);
    }
}