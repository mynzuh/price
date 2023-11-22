#pragma once


// CUDPServerDlg ��ȭ ����
class CUDPServerDlg : public CDialogEx
{
	// �����Դϴ�.
public:
	CUDPServerDlg(CWnd* pParent = nullptr);	// ǥ�� �������Դϴ�.

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UDP_SERVER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


	// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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