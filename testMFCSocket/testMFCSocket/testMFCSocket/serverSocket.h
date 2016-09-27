#pragma once
#include "testMFCSocketDlg.h"
// CserverSocket ÃüÁîÄ¿±ê
class CtestMFCSocketDlg;

class CserverSocket : public CSocket
{
public:
	CtestMFCSocketDlg *m_pDlg;
	CserverSocket();
	virtual ~CserverSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
};


