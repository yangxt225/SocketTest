// PhoneClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PhoneClient.h"
#include "PhoneClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define port 8000

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPhoneClientDlg �Ի���




CPhoneClientDlg::CPhoneClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPhoneClientDlg::IDD, pParent)
	, m_DataSend(_T(""))
	, m_connect(FALSE)
	, pSock(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhoneClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Connect, m_ConPC);
	DDX_Text(pDX, IDC_DataSend, m_DataSend);
}

BEGIN_MESSAGE_MAP(CPhoneClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_Connect, &CPhoneClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_Send, &CPhoneClientDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CPhoneClientDlg ��Ϣ�������

BOOL CPhoneClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPhoneClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPhoneClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CPhoneClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPhoneClientDlg::OnBnClickedConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_connect)                             // ����Ѿ����ӣ���Ͽ�������
	{
		m_connect = false;
		pSock->Close();
		delete pSock;
		pSock = NULL;
		m_ConPC.SetWindowText(_T("���ӷ�����"));
		UpdateData(false);
		return;
	}
	else                                                // δ���ӣ������ӷ�����
	{
		pSock = new CClientSocket();
		if (!pSock->Create())         //�����׽���
		{
			AfxMessageBox(_T("�����׽���ʧ�ܣ�"));
			return;
		}
	}
	// �����ڱ����ϲ��ԣ�����IPΪ127.0.0.1
	if (!pSock->Connect(_T("127.0.0.1"), port))    //���ӷ�����
	{
		AfxMessageBox(_T("���ӷ�����ʧ�ܣ�"));
		return;
	}
	else
	{
		m_connect = true;
		m_ConPC.SetWindowText(_T("�Ͽ�������"));
		UpdateData(false);
	}
}

void CPhoneClientDlg::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_connect)
		return;                               //δ���ӷ�������ִ��
	UpdateData(true);                                     //��ȡ��������
	if (m_DataSend != "")                                           
	{
		char* pBuff = new char[m_DataSend.GetLength() * 2];
		memset(pBuff, 0, m_DataSend.GetLength() * 2);
		WChar2MByte(m_DataSend.GetBuffer(0), pBuff, m_DataSend.GetLength() * 2);
		pSock->SendMSG(pBuff, m_DataSend.GetLength() * 2);
	}
}

// �������ڷ��ͺ���SendMSG�е��ã������ַ�����ת���������ַ�ת��Ϊ���ַ���������ת���Ļ������շ�ֻ�ܽ���һ���ֽ�
BOOL CPhoneClientDlg::WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, 0, 0, FALSE);
	if (n==0)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, nlen, 0, FALSE);
	return TRUE;
}

// �������ڷ�ֹ����enter����escʱ�˳�����
BOOL CPhoneClientDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->wParam)
	{
	case VK_RETURN:
	case VK_ESCAPE:
		return true; 
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

