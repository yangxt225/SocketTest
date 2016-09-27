// PhoneClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "ClientSocket.h"

// CPhoneClientDlg �Ի���
class CserverSocket;
class CPhoneClientDlg : public CDialog
{
// ����
public:
	CPhoneClientDlg(CWnd* pParent = NULL);	// ��׼���캯��
	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);      
	virtual BOOL PreTranslateMessage(MSG* pMsg); 

// �Ի�������
	enum { IDD = IDD_PHONECLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_ConPC;
	CString m_DataSend;
	bool m_connect;
	CClientSocket *pSock;                        // �ͻ����׽���ָ�����
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedSend();
public:
	afx_msg void OnEnChangeDatasend();
};
