/* 服务器端 */  
#include "stdafx.h"
#include<winsock2.h>  
#include<stdlib.h>
#include<windows.h>  
#include<time.h>  
#pragma comment(lib,"WS2_32.lib")  

int main(int argc,char*argv[])  
{  
	/*加载winsock文件*/  
	WSADATA wsaData;                    //WSADATA结构被用来储存调用AfxSocketInit全局函数返回的Windows Sockets初始化信息    定义在Winsock.h  
	WORD sockVersion=MAKEWORD(2,0);     //使用WINSOCK2版本  

	::WSAStartup(sockVersion,&wsaData);   //第一个参数是WINSOCK 版本号,第二个参数是指向WSADATA的指针.  
	//该函数返回一个INT型值,通过检查这个值来确定初始化是否成功     

	/*创建服务器端的套接字*/  
	SOCKET sServer=::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);  
	//三个参数分别代表 使用TCP/IP;传输过程使用TCP;不适用其他特殊协议  

	if(sServer==INVALID_SOCKET)  
	{     
		printf("Failed socket()\n");  
		::WSACleanup();  
		system("pause");  
		return 0;  
	}  

	/*socket中装入地址信息*/  
	sockaddr_in sin;  
	sin.sin_family=AF_INET;              //sin_family指代协议族，在socket编程中只能是AF_INET  
	sin.sin_port=htons(13);              //表示服务器监听的端口号为13  
	sin.sin_addr.S_un.S_addr=INADDR_ANY; //存储IP地址,INADDR_ANY就是指定地址为0.0.0.0的地址，这个地址事实上表示不确定地址，或“所有地址”、“任意地址”。  

	/*绑定地址及端口号*/  
	if(::bind(sServer,(LPSOCKADDR)&sin,sizeof(sin))==SOCKET_ERROR)  
	{     
		printf("Failed bind()\n");  
		::WSACleanup();  
		system("pause");  
		return 0;  
	}  

	/*监听客户端的连接请求*/  
	if(::listen(sServer,2)==SOCKET_ERROR)  
	{     
		printf("Failed listen()\n");  
		::WSACleanup();  
		system("pause");  
		return 0;  
	}  

	sockaddr_in remoteAddr;  
	int nAddrLen=sizeof(remoteAddr);  
	SOCKET client;  

	time_t t = time( 0 );  
	char tmp[64];  
	strftime( tmp, sizeof(tmp), "%Y/%m/%d %X %A\n\t", localtime(&t) );//提取系统时间  

	/*循环接受连接请求*/  
	while(TRUE)  
	{     
		//accept默认会阻塞进程，直到有一个客户连接建立后返回，它返回的是一个新可用的套接字，这个套接字是连接套接字。  
		client=::accept(sServer,(SOCKADDR*)&remoteAddr,&nAddrLen);		
		if(client==INVALID_SOCKET)  
		{     
			printf("accept() faild! code:%d\n", WSAGetLastError());
			closesocket(sServer); //关闭套接字
			WSACleanup();
			return 0;
		}  
		printf("接收到一个客户端的连接：%s\r\n",inet_ntoa(remoteAddr.sin_addr));  
		char receiveMessage[31];
		int ret = ::recv(client, receiveMessage, 31, 0);
		if(ret == SOCKET_ERROR)
		{
			printf("recv failed!\n");
			return 0;
		}
		if(ret == 0)
		{
			printf("Client has closed the connection\n");
			break;
		}

		printf("接收客户端数据：%s\r\n", receiveMessage);
		printf("等待下一个客户端的连接……\n\n");  
		::send(client,tmp,strlen(tmp),0); /*发送本地时间给客户端*/  

		::closesocket(client); /*关闭连接*/  
	}  

	::closesocket(sServer);/*关闭套接字*/  

	::WSACleanup();  
	system("pause");  
	return 0;  
}  