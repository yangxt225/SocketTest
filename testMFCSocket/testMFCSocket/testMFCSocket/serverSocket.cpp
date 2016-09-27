// serverSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "testMFCSocket.h"
#include "serverSocket.h"


// CserverSocket

CserverSocket::CserverSocket()
{
}

CserverSocket::~CserverSocket()
{
}


// CserverSocket ��Ա����

void CserverSocket::OnReceive(int nErrorCode)
{
	m_pDlg->RecvData(this);                           // ��������
	CSocket::OnReceive(nErrorCode);
}

void CserverSocket::OnClose(int nErrorCode)
{
	m_pDlg->RemoveClient(this);                   // ɾ�������û�
	CSocket::OnClose(nErrorCode);
}

void CserverSocket::OnAccept(int nErrorCode)
{
	m_pDlg->AddClient();                                  //��������û�
	CSocket::OnAccept(nErrorCode);
}


