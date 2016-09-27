/* 客户端  */  
#include "stdafx.h"
#include<winsock2.h>  
#include<stdlib.h>
#include<windows.h>  
#pragma comment(lib,"WS2_32.lib")  

int main(int argc,char*argv[])  
{  
	/*加载winsock文件*/  
	WSADATA wsaData;  
	WORD sockVersion=MAKEWORD(2,0);  
	::WSAStartup(sockVersion,&wsaData);  

	/*创建客户端的套接字*/  
	SOCKET sClient=::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);  

	if(sClient==INVALID_SOCKET)  
	{     
		printf("Failed socket()\n");  
		::WSACleanup();  
		system("pause");  
	}  

	/*socket中装入地址信息*/  
	sockaddr_in servAddr;  
	servAddr.sin_family=AF_INET;  
	servAddr.sin_port=htons(13); /*接收服务器13端口号*/  
	servAddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");/*本地IP地址为127.0.0.1*/  

	/*连接服务器*/  
	if(::connect(sClient,(sockaddr*)&servAddr,sizeof(servAddr))==-1)  
	{     
		printf("Failed connect()\n");  
		::WSACleanup();  
		system("pause");  
	}  

	char	sendMessage[] = "hello, this is client message.";
	int ret = ::send(sClient, sendMessage, sizeof(sendMessage), 0);
	if (ret == SOCKET_ERROR)
		printf("send() failed!\n");

	/*接收数据并打印到屏幕上*/  
	char buff[256];  
	int nRecv=::recv(sClient,buff,256,0);  
	if(nRecv>0)  
	{     
		buff[nRecv]='\0';  
		printf("连接成功\n");  
		printf("接收到服务端数据：%s\n",buff);  
		system("pause");  
	}  

	return 0;  
}  