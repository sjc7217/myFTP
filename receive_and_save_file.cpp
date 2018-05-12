#include"tcp.h"

void receive_and_save_file(int connfd){
    char buff[4096];
    ssize_t size=0;
    char* cur = buff;
    int filefd;
    for(;;){//首先传输的是文件的名字，以'\0'结束
        size = read(connfd,cur,1);
        if(size!=1){
            perror("read error");
            exit(1);
        }
        if(*cur == '\0') break;
        cur++;
    }

   // printf("%s\n",buff);
    char * filename = cur;
    while(*filename != '/') {//确定文件名字
        if(filename == buff){
            filename--;
            break;
        }
        filename--;
    }
    filefd = open(++filename,O_CREAT|O_WRONLY,0777);//打开文件
    if(filefd == -1){
        perror("create file error");
        exit(3);
    }
    for(;;){//传输文件
        size = read(connfd,buff,4096);
        if(size==-1){
            perror("read error");
            exit(2);
        }
        if(size==0) break;//read返回0表示到达文件末尾，正常结束
        write(filefd,buff,size);
    }
    close(filefd);
    close(connfd);
    return;
}
