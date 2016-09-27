// PhoneClientDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "ClientSocket.h"

// CPhoneClientDlg 对话框
class CserverSocket;
class CPhoneClientDlg : public CDialog
{
// 构造
public:
	CPhoneClientDlg(CWnd* pParent = NULL);	// 标准构造函数
	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);      
	virtual BOOL PreTranslateMessage(MSG* pMsg); 

// 对话框数据
	enum { IDD = IDD_PHONECLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_ConPC;
	CString m_DataSend;
	bool m_connect;
	CClientSocket *pSock;                        // 客户端套接字指针对象
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedSend();
public:
	afx_msg void OnEnChangeDatasend();
};
