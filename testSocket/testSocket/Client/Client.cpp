/* �ͻ���  */  
#include "stdafx.h"
#include<winsock2.h>  
#include<stdlib.h>
#include<windows.h>  
#pragma comment(lib,"WS2_32.lib")  

int main(int argc,char*argv[])  
{  
	/*����winsock�ļ�*/  
	WSADATA wsaData;  
	WORD sockVersion=MAKEWORD(2,0);  
	::WSAStartup(sockVersion,&wsaData);  

	/*�����ͻ��˵��׽���*/  
	SOCKET sClient=::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);  

	if(sClient==INVALID_SOCKET)  
	{     
		printf("Failed socket()\n");  
		::WSACleanup();  
		system("pause");  
	}  

	/*socket��װ���ַ��Ϣ*/  
	sockaddr_in servAddr;  
	servAddr.sin_family=AF_INET;  
	servAddr.sin_port=htons(13); /*���շ�����13�˿ں�*/  
	servAddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");/*����IP��ַΪ127.0.0.1*/  

	/*���ӷ�����*/  
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

	/*�������ݲ���ӡ����Ļ��*/  
	char buff[256];  
	int nRecv=::recv(sClient,buff,256,0);  
	if(nRecv>0)  
	{     
		buff[nRecv]='\0';  
		printf("���ӳɹ�\n");  
		printf("���յ���������ݣ�%s\n",buff);  
		system("pause");  
	}  

	return 0;  
}  