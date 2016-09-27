// testMFCSocketDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "testMFCSocket.h"
#include "testMFCSocketDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CtestMFCSocketDlg �Ի���




CtestMFCSocketDlg::CtestMFCSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtestMFCSocketDlg::IDD, pParent)
	, m_userCount(0)
	, listenSocket(NULL)
	, m_connect(FALSE)
	, m_port(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestMFCSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EventRecord, m_event);
	DDX_Text(pDX, IDC_PORT, m_port);
	DDV_MinMaxUInt(pDX, m_port, 1024, 65535);
}

BEGIN_MESSAGE_MAP(CtestMFCSocketDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_StartServer, &CtestMFCSocketDlg::OnBnClickedStartserver)
END_MESSAGE_MAP()


// CtestMFCSocketDlg ��Ϣ�������

BOOL CtestMFCSocketDlg::OnInitDialog()
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

void CtestMFCSocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CtestMFCSocketDlg::OnPaint()
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
HCURSOR CtestMFCSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CtestMFCSocketDlg::OnBnClickedStartserver()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_connect)
	{
		delete listenSocket;
		listenSocket = NULL;
		m_connect = false;
		SetDlgItemText(IDC_StartServer, _T("�򿪷�����"));
		UpdateEvent(_T("ϵͳ�رշ�����."));
		return;
	}
	listenSocket = new CserverSocket();
	// ָ���Ի���Ϊ���Ի��򣬲����������
	listenSocket->m_pDlg = this;
	UpdateData(TRUE);
	if (!listenSocket->Create(m_port))                     
		// �������������׽��֣�IP��ַĬ�ϱ���IP
	{
		AfxMessageBox(_T("�����׽��ִ���"));
		listenSocket->Close();
		return;
	}
	if (!listenSocket->Listen())
	{
		AfxMessageBox(_T("����ʧ�ܣ�"));
		listenSocket->Close();
		return;
	}
	m_connect = true;
	SetDlgItemText(IDC_StartServer, _T("�رշ�����"));
	UpdateEvent(_T("ϵͳ�򿪷�����."));
}

void CtestMFCSocketDlg::AddClient()
{
	CserverSocket *pSocket = new CserverSocket;
	pSocket->m_pDlg = this;
	listenSocket->Accept(*pSocket);
	pSocket->AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE);
	m_clientList.AddTail(pSocket);
	m_userCount = m_clientList.GetCount();
	UpdateData(false);
	UpdateEvent(_T("�û����ӷ�����."));
	SendMSG(_T("Hello!"));
}

void CtestMFCSocketDlg::RemoveClient(CserverSocket* pSocket)
{
	POSITION nPos = m_clientList.GetHeadPosition();
	POSITION nTmpPos = nPos;
	while (nPos)
	{
		CserverSocket* pSockItem = (CserverSocket*)m_clientList.GetNext(nPos);
		if (pSockItem->m_hSocket == pSocket->m_hSocket)
		{                          
			pSockItem->Close();
			delete pSockItem;
			m_clientList.RemoveAt(nTmpPos);
			m_userCount = m_clientList.GetCount();
			UpdateData(false);
			UpdateEvent(_T("�û��뿪."));
			return;
		}
		nTmpPos = nPos;
	}
}

void CtestMFCSocketDlg::RecvData(CserverSocket* pSocket)
{
	char* pData = NULL;
	pData = new char[1024];
	memset(pData, 0, sizeof(char)* 1024);
	UCHAR leng = 0;
	CString str;
	if (pSocket->Receive(pData, 1024, 0) != SOCKET_ERROR)
	{
		str = pData;
		//ControlPC(str);     // ����ָ����Ƶ���
		SendMSG(str);     // ת�����ݸ������û��������������ݵ��û�
	}
	delete pData;
	pData = NULL;
}

void CtestMFCSocketDlg::UpdateEvent(CString str)
{
	CString string;
	CTime time = CTime::GetCurrentTime();                  
	// ��ȡϵͳ��ǰʱ��
	str += _T("\r\n");                                                             
	// ���ڻ�����ʾ��־
	string = time.Format(_T("%Y/%m/%d %H:%M:%S  ")) + str;         
	// ��ʽ����ǰʱ��
	int lastLine = m_event.LineIndex(m_event.GetLineCount() - 1);
	//��ȡ�༭�����һ������
	m_event.SetSel(lastLine+1,lastLine+2,0);                                     
	//ѡ��༭�����һ��
	m_event.ReplaceSel(string);    //�滻��ѡ��һ�е�����
}

// �������ڷ��ͺ���SendMSG�е��ã������ַ�����ת���������ַ�ת��Ϊ���ַ���������ת���Ļ������շ�ֻ�ܽ���һ���ֽ�
BOOL CtestMFCSocketDlg::WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, 0, 0, FALSE);
	if (n==0)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, nlen, 0, FALSE);
	return TRUE;
}

void CtestMFCSocketDlg::SendMSG(CString str)
{
	char *pSend = new char[str.GetLength()*2];
	memset(pSend, 0, str.GetLength()*sizeof(char)*2);
	if (!WChar2MByte(str.GetBuffer(0), pSend, str.GetLength()*2))
	{
		AfxMessageBox(_T("�ַ�ת��ʧ��"));
		delete pSend;
		return;
	}
	POSITION nPos = m_clientList.GetHeadPosition();
	while (nPos)
	{
		CserverSocket* pTemp = (CserverSocket*)m_clientList.GetNext(nPos);
		pTemp->Send(pSend, str.GetLength()*2);
	}
	delete pSend;
}

void CtestMFCSocketDlg::ControlPC(CString AndroidControl)
{
	if (AndroidControl == "mop")             //�򿪲�����
	{
		ShellExecute(NULL, _T("open"), _T("C:\\Program Files (x86)\\KuGou\\KGMusic\\KuGou.exe"), NULL, NULL, SW_SHOWNORMAL);
	}
	else if (AndroidControl == "mcl")         //�رղ�����
	{
		DWORD id_num;
		HWND hWnd = ::FindWindow(_T("kugou_ui"), NULL);
		GetWindowThreadProcessId(hWnd, &id_num);                      
		//ע�⣺�ڶ��������ǽ��̵�ID������ֵ���̵߳�ID��
		HANDLE hd = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id_num);
		TerminateProcess(hd, 0);
	}
	else if (AndroidControl == "mpl" || AndroidControl == "mpa")                //����/��ͣ
	{
		keybd_event(VK_LMENU, 0, 0, 0);
		keybd_event(VK_F5, 0, 0, 0);
		keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	}
}
// �������ڷ�ֹ����enter����escʱ�˳�����
BOOL CtestMFCSocketDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->wParam)
	{
	case VK_RETURN:
	case VK_ESCAPE:
		return true; break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

