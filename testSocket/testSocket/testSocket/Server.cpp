/* �������� */  
#include "stdafx.h"
#include<winsock2.h>  
#include<stdlib.h>
#include<windows.h>  
#include<time.h>  
#pragma comment(lib,"WS2_32.lib")  

int main(int argc,char*argv[])  
{  
	/*����winsock�ļ�*/  
	WSADATA wsaData;                    //WSADATA�ṹ�������������AfxSocketInitȫ�ֺ������ص�Windows Sockets��ʼ����Ϣ    ������Winsock.h  
	WORD sockVersion=MAKEWORD(2,0);     //ʹ��WINSOCK2�汾  

	::WSAStartup(sockVersion,&wsaData);   //��һ��������WINSOCK �汾��,�ڶ���������ָ��WSADATA��ָ��.  
	//�ú�������һ��INT��ֵ,ͨ��������ֵ��ȷ����ʼ���Ƿ�ɹ�     

	/*�����������˵��׽���*/  
	SOCKET sServer=::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);  
	//���������ֱ���� ʹ��TCP/IP;�������ʹ��TCP;��������������Э��  

	if(sServer==INVALID_SOCKET)  
	{     
		printf("Failed socket()\n");  
		::WSACleanup();  
		system("pause");  
		return 0;  
	}  

	/*socket��װ���ַ��Ϣ*/  
	sockaddr_in sin;  
	sin.sin_family=AF_INET;              //sin_familyָ��Э���壬��socket�����ֻ����AF_INET  
	sin.sin_port=htons(13);              //��ʾ�����������Ķ˿ں�Ϊ13  
	sin.sin_addr.S_un.S_addr=INADDR_ANY; //�洢IP��ַ,INADDR_ANY����ָ����ַΪ0.0.0.0�ĵ�ַ�������ַ��ʵ�ϱ�ʾ��ȷ����ַ�������е�ַ�����������ַ����  

	/*�󶨵�ַ���˿ں�*/  
	if(::bind(sServer,(LPSOCKADDR)&sin,sizeof(sin))==SOCKET_ERROR)  
	{     
		printf("Failed bind()\n");  
		::WSACleanup();  
		system("pause");  
		return 0;  
	}  

	/*�����ͻ��˵���������*/  
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
	strftime( tmp, sizeof(tmp), "%Y/%m/%d %X %A\n\t", localtime(&t) );//��ȡϵͳʱ��  

	/*ѭ��������������*/  
	while(TRUE)  
	{     
		//acceptĬ�ϻ��������̣�ֱ����һ���ͻ����ӽ����󷵻أ������ص���һ���¿��õ��׽��֣�����׽����������׽��֡�  
		client=::accept(sServer,(SOCKADDR*)&remoteAddr,&nAddrLen);		
		if(client==INVALID_SOCKET)  
		{     
			printf("accept() faild! code:%d\n", WSAGetLastError());
			closesocket(sServer); //�ر��׽���
			WSACleanup();
			return 0;
		}  
		printf("���յ�һ���ͻ��˵����ӣ�%s\r\n",inet_ntoa(remoteAddr.sin_addr));  
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

		printf("���տͻ������ݣ�%s\r\n", receiveMessage);
		printf("�ȴ���һ���ͻ��˵����ӡ���\n\n");  
		::send(client,tmp,strlen(tmp),0); /*���ͱ���ʱ����ͻ���*/  

		::closesocket(client); /*�ر�����*/  
	}  

	::closesocket(sServer);/*�ر��׽���*/  

	::WSACleanup();  
	system("pause");  
	return 0;  
}  