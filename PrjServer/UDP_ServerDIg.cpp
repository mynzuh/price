#include "pch.h"
#include "framework.h"
#include "UDP_Server.h"
#include "UDP_ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
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


// CUDPServerDlg 대화 상자



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


// CUDPServerDlg 메시지 처리기

BOOL CUDPServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CUDPServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
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

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CUDPServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 연결 버튼 클릭 함수
void CUDPServerDlg::ConnectBtnClicked()
{
	UINT mtPort;
	CString strPort2;
	mtPortEdit.GetWindowText(strPort2); // 사용자 입력 멀티 포트
	mtPort = _tstoi(strPort2);

	TCHAR mtIp[20];
	mtIpEdit.GetWindowTextA(mtIp, 20); // 사용자 입력 멀티 ip

	// 나의 IP 가져오기
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

	// 메시지 송신을 위한 소켓
	send_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (send_socket == INVALID_SOCKET)
	{
		InsertMsg("send socket error");
		return;
	}

	// 멀티캐스트 패킷의 TTL 설정, 성공하면 sentto 가능
	int time_live = 64; // TTL 
	if (setsockopt(send_socket, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&time_live, sizeof(time_live)) < 0)
	{
		InsertMsg("ttl error");
		return;
	}

	// 메시지 수신을 위한 소켓
	recv_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (recv_socket == INVALID_SOCKET)
	{
		InsertMsg("recv socket error");
		return;
	}

	// 주소 재사용 설정 (생략 가능)
	UINT yes = 1;
	if (setsockopt(recv_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes)) < 0)
	{
		InsertMsg("reuse error");
		return;
	}

	// 멀티캐스트 그룹 가입을 위한 구조체
	struct ip_mreq socket_group;
	socket_group.imr_multiaddr = multi_addr.sin_addr;
	socket_group.imr_interface.s_addr = ipArray.GetAt(0).sin_addr.s_addr;

	// 멀티캐스트 그룹 가입
	if (setsockopt(recv_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&socket_group, sizeof(socket_group)) < 0)
	{
		InsertMsg("membership error");
		return;
	}

	// 수신 소켓 bind()
	if (bind(recv_socket, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		InsertMsg(_T("bind error"));
		return;
	}

	InsertMsg(_T("Address Setting Complete"));

	AfxBeginThread(RecvFunc, this); // 수신 스레드 시작

}

// 수신 스레드
UINT CUDPServerDlg::RecvFunc(LPVOID pParam) {

	CUDPServerDlg* pDlg = (CUDPServerDlg*)pParam;

	while (1)
	{
		char temp[1024] = "";
		int strlen;

		// 메시지 수신, 수신한 메시지 길이 반환
		strlen = recvfrom(pDlg->recv_socket, temp, sizeof(temp), 0, NULL, NULL);
		if (strlen == -1) // 오류
		{
			pDlg->InsertMsg("read error");
			break;
		}
		else // 메시지 정상 수신
		{
			// 멀티 그룹 전체에 보내기 때문에 자신의 메시지도 수신
			CString str = (LPSTR)temp;
			pDlg->InsertMsg(str); // 메지시 ListBox 추가
		}
	}
	closesocket(pDlg->recv_socket);
	return 0;
}

// 메시지 ListBox 추가 함수
void CUDPServerDlg::InsertMsg(CString str)
{
	m_msg_list.InsertString(-1, str);
	m_msg_list.SetTopIndex(m_msg_list.GetCount() - 1);
}

// 전송 버튼 클릭 함수
void CUDPServerDlg::SendBtnClicked()
{
	UINT mNum;
	CString strNum;
	myNumEdit.GetWindowText(strNum);
	mNum = _tstoi(strNum); // 고유번호

	CString msg, str;
	msgEdit.GetWindowText(msg);

	// 메시지 보낼 때 User+num으로 보이도록 메시지 가공
	str.Format(_T("User%d : "), mNum);
	msg = str + msg;

	int len = msg.GetLength();
	char* message = new char[len + 10];
	strcpy(message, msg.GetBuffer(0));

	// 상대에게 메시지 전송
	if (sendto(send_socket, message, 1024, 0, (SOCKADDR*)&multi_addr, sizeof(multi_addr)) == -1)
	{
		InsertMsg("send error");
	}
	else
	{
		msgEdit.SetWindowTextA("");
	}
}