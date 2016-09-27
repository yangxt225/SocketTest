// testMFCSocketDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "serverSocket.h"

// CtestMFCSocketDlg �Ի���
class CserverSocket;
class CtestMFCSocketDlg : public CDialog
{
// ����
public:
	CtestMFCSocketDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void AddClient();                       // �����û�����Ӧ�û�����
	void RemoveClient(CserverSocket* pSocket);          // �Ƴ����ߵ��û�
	void RecvData(CserverSocket* pSocket);                 // ��ȡ����
	void UpdateEvent(CString str);  // �����¼���־
	BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);        
	//�ַ�ת��
	void SendMSG(CString str);       // ������Ϣ�������ͻ���
	void ControlPC(CString AndroidControl);  // �ֻ�����PC����Ӧ����

// �Ի�������
	enum { IDD = IDD_TESTMFCSOCKET_DIALOG };

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
	afx_msg void OnBnClickedStartserver();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();

	UINT m_port;
	CEdit m_event;
	unsigned int m_userCount;
	CserverSocket* listenSocket;     // ���ڴ򿪷�����
	CPtrList m_clientList;                 // �������ڴ洢�û�
	bool m_connect;                       // ���ڱ�Ƿ�����״̬
public:
	afx_msg void OnEnChangePort();
};
