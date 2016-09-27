// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "PhoneClient.h"
#include "ClientSocket.h"
#include "PhoneClientDlg.h"


// CClientSocket

CClientSocket::CClientSocket() { }
CClientSocket::~CClientSocket() { }


// CClientSocket 成员函数

void CClientSocket::OnReceive(int nErrorCode)
{
	char* pData = NULL;
	pData = new char[1024];
	memset(pData, 0, sizeof(char)* 1024);
	UCHAR leng = 0;
	CString str;
	leng = Receive(pData, 1024, 0);
	str = pData;
	// 在编辑框中显示接收到的数据
	((CPhoneClientDlg*)theApp.GetMainWnd())->SetDlgItemText(IDC_DataReceive, str);
	delete pData;
	pData = NULL;
	CSocket::OnReceive(nErrorCode);
}

bool CClientSocket::SendMSG(LPSTR lpBuff, int nlen)
{
	//生成协议头
	if (Send(lpBuff, nlen) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("发送错误！"));
		return FALSE;
	}
	return  TRUE;
}
