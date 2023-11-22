#include "pch.h"
#include "framework.h"
#include "UDP_Server.h"
#include "UDP_ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUDPServerDlg ��ȭ ����



CUDPServerDlg::CUDPServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UDP_SERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDPServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PORT_EDIT, myNumEdit);
	DDX_Control(pDX, IDC_MSG_LIST, m_msg_list);
	DDX_Control(pDX, IDC_MSG_EDIT, msgEdit);
	DDX_Control(pDX, IDC_IP_EDIT2, mtIpEdit);
	DDX_Control(pDX, IDC_PORT_EDIT2, mtPortEdit);
}

BEGIN_MESSAGE_MAP(CUDPServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BUTTON, &CUDPServerDlg::ConnectBtnClicked)
	ON_BN_CLICKED(IDC_SEND_BUTTON, &CUDPServerDlg::SendBtnClicked)
END_MESSAGE_MAP()


// CUDPServerDlg �޽��� ó����

BOOL CUDPServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CUDPServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CUDPServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CUDPServerDlg::OnOK() {
	CUDPServerDlg::SendBtnClicked();
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CUDPServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���� ��ư Ŭ�� �Լ�
void CUDPServerDlg::ConnectBtnClicked()
{
	UINT mtPort;
	CString strPort2;
	mtPortEdit.GetWindowText(strPort2); // ����� �Է� ��Ƽ ��Ʈ
	mtPort = _tstoi(strPort2);

	TCHAR mtIp[20];
	mtIpEdit.GetWindowTextA(mtIp, 20); // ����� �Է� ��Ƽ ip

	// ���� IP ��������
	char myaddr[20] = "";
	gethostname(myaddr, sizeof(myaddr));
	PHOSTENT hostInfo = gethostbyname(myaddr);
	SOCKADDR_IN addr;
	CArray<sockaddr_in, sockaddr_in& > ipArray;
	CString msgIp("");
	if (hostInfo) {
		for (int i = 0; hostInfo->h_addr_list[i] != NULL; i++) {
			memcpy(&addr.sin_addr, hostInfo->h_addr_list[i], hostInfo->h_length);
			ipArray.Add(addr);
		}
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(mtPort);
	addr.sin_addr.s_addr = ipArray.GetAt(0).sin_addr.s_addr;

	multi_addr.sin_family = AF_INET;
	multi_addr.sin_port = htons(mtPort);
	multi_addr.sin_addr.s_addr = inet_addr(mtIp);

	// �޽��� �۽��� ���� ����
	send_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (send_socket == INVALID_SOCKET)
	{
		InsertMsg("send socket error");
		return;
	}

	// ��Ƽĳ��Ʈ ��Ŷ�� TTL ����, �����ϸ� sentto ����
	int time_live = 64; // TTL 
	if (setsockopt(send_socket, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&time_live, sizeof(time_live)) < 0)
	{
		InsertMsg("ttl error");
		return;
	}

	// �޽��� ������ ���� ����
	recv_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (recv_socket == INVALID_SOCKET)
	{
		InsertMsg("recv socket error");
		return;
	}

	// �ּ� ���� ���� (���� ����)
	UINT yes = 1;
	if (setsockopt(recv_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes)) < 0)
	{
		InsertMsg("reuse error");
		return;
	}

	// ��Ƽĳ��Ʈ �׷� ������ ���� ����ü
	struct ip_mreq socket_group;
	socket_group.imr_multiaddr = multi_addr.sin_addr;
	socket_group.imr_interface.s_addr = ipArray.GetAt(0).sin_addr.s_addr;

	// ��Ƽĳ��Ʈ �׷� ����
	if (setsockopt(recv_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&socket_group, sizeof(socket_group)) < 0)
	{
		InsertMsg("membership error");
		return;
	}

	// ���� ���� bind()
	if (bind(recv_socket, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		InsertMsg(_T("bind error"));
		return;
	}

	InsertMsg(_T("Address Setting Complete"));

	AfxBeginThread(RecvFunc, this); // ���� ������ ����

}

// ���� ������
UINT CUDPServerDlg::RecvFunc(LPVOID pParam) {

	CUDPServerDlg* pDlg = (CUDPServerDlg*)pParam;

	while (1)
	{
		char temp[1024] = "";
		int strlen;

		// �޽��� ����, ������ �޽��� ���� ��ȯ
		strlen = recvfrom(pDlg->recv_socket, temp, sizeof(temp), 0, NULL, NULL);
		if (strlen == -1) // ����
		{
			pDlg->InsertMsg("read error");
			break;
		}
		else // �޽��� ���� ����
		{
			// ��Ƽ �׷� ��ü�� ������ ������ �ڽ��� �޽����� ����
			CString str = (LPSTR)temp;
			pDlg->InsertMsg(str); // ������ ListBox �߰�
		}
	}
	closesocket(pDlg->recv_socket);
	return 0;
}

// �޽��� ListBox �߰� �Լ�
void CUDPServerDlg::InsertMsg(CString str)
{
	m_msg_list.InsertString(-1, str);
	m_msg_list.SetTopIndex(m_msg_list.GetCount() - 1);
}

// ���� ��ư Ŭ�� �Լ�
void CUDPServerDlg::SendBtnClicked()
{
	UINT mNum;
	CString strNum;
	myNumEdit.GetWindowText(strNum);
	mNum = _tstoi(strNum); // ������ȣ

	CString msg, str;
	msgEdit.GetWindowText(msg);

	// �޽��� ���� �� User+num���� ���̵��� �޽��� ����
	str.Format(_T("User%d : "), mNum);
	msg = str + msg;

	int len = msg.GetLength();
	char* message = new char[len + 10];
	strcpy(message, msg.GetBuffer(0));

	// ��뿡�� �޽��� ����
	if (sendto(send_socket, message, 1024, 0, (SOCKADDR*)&multi_addr, sizeof(multi_addr)) == -1)
	{
		InsertMsg("send error");
	}
	else
	{
		msgEdit.SetWindowTextA("");
	}
}