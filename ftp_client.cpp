#include"tcp.h"

int main(int argc,char**argv){
    if(argc!=4){
        printf("Wrong parameters,please use:<./client>  <file_path> <ip> <port>\n");
        exit(0);
    }

    int sockfd,filefd,SERV_PORT;
	struct sockaddr_in servaddr;
	struct in_addr addr;
    char buff[4096];

    SERV_PORT = atoi(argv[3]);//端口判别
    if(SERV_PORT<0 ||SERV_PORT>65536){
        printf("Wrong port!\n");
        exit(0);
    }

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){//打开客户端Socket
		perror("Socket Create error");
		exit(0);
	}

	bzero(&servaddr,sizeof(servaddr));//需要连接的服务器端地址设置
	servaddr.sin_family = AF_INET;

	servaddr.sin_port = htons(SERV_PORT);
	// if(inet_aton(argv[1],&addr) != 1){//字符串ip地址转换
	// 	printf("Invalid Address!\n");
	// 	exit(0);
	// }
    if(inet_pton(AF_INET,argv[2],&addr) != 1){
        printf("Wrong IP address!\n");
        exit(0);
    }
	servaddr.sin_addr.s_addr =addr.s_addr;

	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1){//客户端开始发起TCP连接
		perror("Connect Fail");
		exit(0);
	}

    filefd = open(argv[1],O_RDONLY);//打开需要传输的文件
    if(filefd == -1){
        perror("open file error");
        exit(0);
    }

    int filename_len = strlen(argv[1]);//传输文件名字
    write(sockfd,argv[1],filename_len+1);

    ssize_t size = 0;
    for(;;){//传输文件
        size = read(filefd,buff,4096);
        if(size == -1){
            perror("read error");
            exit(0);
        }
        if(size == 0) break;
        ssize_t left_bytes = size;
        char * cur = buff;
        while(left_bytes>0){
            ssize_t temp = write(sockfd,cur,left_bytes);
            if(temp == -1){
                perror("write error");
                exit(0);
            }
            left_bytes-=temp;
            cur+=temp;
        }
    }

    exit(0);

}
