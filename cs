#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
void parse(char* buf){
        int i , len ;
        len = strlen(buf) ;
        for(i=0;i<len;i++){
                if( buf[i]>='a' && buf[i]<='z')
                        buf[i] -= 32 ;
        }
}

int readline(int cfd,char buf[1024]){
        int i =0 ;
        while(1){
                if( read(cfd,&buf[i],1) <= 0 ) {
                      break ;
                }
                if( buf[i] == '\n' ){
                        break ;
                }
                ++i ;
        }
        buf[++i] = '\0' ;
        return i ;
}
void echo_file(int cfd,char* p ) {
        p++ ;
        printf("p = %s\n",p) ;
        printf("cfd = %d\n",cfd) ;

        int fd = open(p,O_RDONLY) ;

        if( fd == -1 ){
                char* msg = "page not found\\r\n" ;
                write(cfd,msg,strlen(msg)) ;
                return ;
        }

 char buf[1024] ;
        while(1){
                memset(buf,0x00,sizeof(buf)) ;
                int r = read(fd,buf,1000) ;
                printf("response client = [%s]\n",buf) ;
                if( r <= 0 ) {
                        close(fd) ;
                        break ;
}       
                write(cfd,buf,r) ;
        }
}
void do_get(int cfd,char buf[1024]) {
        // GET /index.html HTTP/1.1
        char* p = strchr(buf,' ') ;
 if( p != NULL ) {
                *p = '\0' ;
        }
        p++ ;
        char* q = strchr(p,' ') ;
        *q = '\0' ;
        printf("filename = %s\n",p) ;
        echo_file(cfd,p) ;
}
void do_client(int cfd){
        char buf[1024] ;
        while(1){
                int r = readline(cfd,buf) ;
                if( r <= 2 ) {
                        close(cfd) ;
                        break ;
                }
                printf("r = %d,buf = [%s]\n",r,buf) ;
     if( strncasecmp(buf,"GET",3) == 0 )
                        do_get(cfd,buf) ;
        }
}
void do_client1(int cfd){
        char buf[1024] ;
        while(1){
                int r = read(cfd,buf,1022) ;
                if( r <= 2 ) {
                        printf("get\\r\\n\n") ;
                        close(cfd) ;
                        exit(1) ;
                }
                printf("buf=[%s]\n",buf) ;
        }
}
void main(){


// 创建监听套接子
        printf("创建套接字\n") ;
  int lfd = socket(AF_INET,SOCK_STREAM,0) ;
        struct sockaddr_in addr ;
        addr.sin_family = AF_INET ;
        addr.sin_port = htons(80) ;
        inet_aton("192.168.73.129",&addr.sin_addr) ;
// 绑定
        printf("绑定\n") ;
        int r = bind(lfd,(struct sockaddr*)&addr,sizeof(addr)) ;
        if( -1 == r ) {
                perror("bind error") , exit(1) ;
        }
/// 设置成被动套接子
        printf("监听\n") ;
        r = listen(lfd,SOMAXCONN) ;
        if( r == -1 ) perror("listen") , exit(1) ;

        for(;;) { //等待
// 等待客户端的连接
                int newfd = accept(lfd,NULL,NULL) ;

                if( newfd == -1 && errno == EINTR ) {
                        continue ;
                }

                do_client(newfd) ;
                close(newfd) ;
        }
                                                                                                                      127,1-8       99%
}





	




struct s{
	int a;
	int b;
	char* c;
};

struct sc{
	int a;
	int b;
	char c[];
}; 
void test(){
	// 申请内存方式

	// 两次申请，内存并不一定连续
	// 释放内存需要释放两次
	struct s* t0 = (struct s*)malloc(sizeof(struct s));
	t0->c = (char*)malloc(sizeof(char) * 16);


	// 此处释放内存只需要释放一次
	//内存申请只需要一次，地址连续
	struct sc* t1 = (struct sc*)malloc(sizeof(struct sc) + sizeof(char) * 16);

	cout << "t0" << sizeof t0 << endl;
	cout << "t1" << sizeof t1 << endl;
	t1->c;//访问方式和普通成员访问方式一致
	cout << sizeof(struct s) << endl; // 12
	cout << sizeof(struct sc) << endl; // 8
	int a = 1;
	cout << sizeof a << endl;

	// 两种不同的方式导致数据拷贝的方式也不一致
	//前者需要拷贝两端，分别拷贝
	// 而后者只需要拷贝一段，直接一次拷贝,由于柔性数组的内存，它的数据内同和结构体成员的地址是连续的，因此可以直接拷贝
	
	// 减少内存碎片
	// 由于结构体的柔性数组和结构体成员的地址是连续的，即可一同申请内存，因此更大程度地避免了内存碎片，另外
	// 由于该成员本身不占结构体空间，因此，整体而言，比普通的数组郑源栈空间会稍微小点

	// 零长数组实现同样的功能
	// 但是不是C99标准，因此考虑到可移植问题，因此不建议使用

	//总结：
	// 柔性数组的使用：
	// 位于结构体的最后一个位置
	// 不完整数组类型
	// 不是唯一成员
}