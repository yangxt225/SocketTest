// ClientSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PhoneClient.h"
#include "ClientSocket.h"
#include "PhoneClientDlg.h"


// CClientSocket

CClientSocket::CClientSocket() { }
CClientSocket::~CClientSocket() { }


// CClientSocket ��Ա����

void CClientSocket::OnReceive(int nErrorCode)
{
	char* pData = NULL;
	pData = new char[1024];
	memset(pData, 0, sizeof(char)* 1024);
	UCHAR leng = 0;
	CString str;
	leng = Receive(pData, 1024, 0);
	str = pData;
	// �ڱ༭������ʾ���յ�������
	((CPhoneClientDlg*)theApp.GetMainWnd())->SetDlgItemText(IDC_DataReceive, str);
	delete pData;
	pData = NULL;
	CSocket::OnReceive(nErrorCode);
}

bool CClientSocket::SendMSG(LPSTR lpBuff, int nlen)
{
	//����Э��ͷ
	if (Send(lpBuff, nlen) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ʹ���"));
		return FALSE;
	}
	return  TRUE;
}
