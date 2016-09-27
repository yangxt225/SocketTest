// serverSocket.cpp : 实现文件
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


// CserverSocket 成员函数

void CserverSocket::OnReceive(int nErrorCode)
{
	m_pDlg->RecvData(this);                           // 接收数据
	CSocket::OnReceive(nErrorCode);
}

void CserverSocket::OnClose(int nErrorCode)
{
	m_pDlg->RemoveClient(this);                   // 删除下线用户
	CSocket::OnClose(nErrorCode);
}

void CserverSocket::OnAccept(int nErrorCode)
{
	m_pDlg->AddClient();                                  //添加上线用户
	CSocket::OnAccept(nErrorCode);
}


