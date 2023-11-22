#pragma once


// CUDPServerDlg 대화 상자
class CUDPServerDlg : public CDialogEx
{
	// 생성입니다.
public:
	CUDPServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UDP_SERVER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnOK();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CListBox m_msg_list;
	CEdit msgEdit;
	CEdit mtIpEdit;
	CEdit mtPortEdit;
	CEdit myNumEdit;

	void InsertMsg(CString str);
	afx_msg void ConnectBtnClicked();
	afx_msg void SendBtnClicked();
	static UINT RecvFunc(LPVOID pParam);

private:
	SOCKET send_socket;
	SOCKET recv_socket;
	SOCKADDR_IN my_addr;
	SOCKADDR_IN multi_addr;
};