#include"tcp.h"

void sigchild_process(int sig_num){
    pid_t pid;
	int stat;
	pid = wait(&stat);
	//printf("Child %d terminated\n",pid);
	return;
}

int main(int argc,char** argv){

    if(argc !=2){
        printf("Wrong parameters,please use <command> <port>\n");
        exit(0);
    }

    int listenfd,SERV_PORT;
	struct sockaddr_in servaddr;

    signal(SIGCHLD, sigchild_process);

    SERV_PORT = atoi(argv[1]);
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("Create socket error");
		exit(0);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
		perror("Bind Fail");
		exit(0);
	}

	if(listen(listenfd, 5 ) == -1){
		perror("Listen Fail");
		exit(0);
	}

    int pid = fork();//使之成为守护进程的第一个fork，使得子进程不可能是进程组组长
    if(pid == 0){
        setsid();
        signal(SIGHUP, SIG_IGN);//添加SIGHUP信号屏蔽，回话首进程退出时会向其他回话进程发送SIGHUP信号，该信号默认结束进程
        int pid2 = fork();//第二次fork使之不是回话首进程，防止终端绑定
        if(pid2 > 0){
            _exit(0);
        }
        close(0);//关闭stdin.stdout,stderr三个fd，并且把0,1,2号文件描述符全部指向空设备/dev/null
        close(1);
        close(2);
        open("/dev/null", O_RDONLY);
        open("/dev/null", O_RDWR);
        open("/dev/null", O_RDWR);
    }else if(pid > 0){
        _exit(0);
    }
    while(true){
        ftpd(listenfd);
    }
}
