#pragma once

//#define SERVERIP4 _T("127.0.0.1")
//#define SERVERIP6 _T("::1")
//#define SERVERPORT 9000

#define SIZE_TOT 256
#define SIZE_DAT (SIZE_TOT-sizeof(int))

#define TYPE_CHAT 1000
#define TYPE_DRAWLINE 1001
#define TYPE_ERASEPIC 1002

#define WM_DRAWLINE (WM_USER+1)
#define WM_ERASEPIC (WM_USER+2)

// 공통 메시지 형식
// sizeof(COMM_MSG) == 256
typedef struct COMM_MSG_h
{
	int type;
	char dummy[SIZE_DAT];
} COMM_MSG_h;

// 채팅 메시지 형식
// sizeof(CHAT_MSG) == 256
typedef struct CHAT_MSG_h
{
	int type;
	char msg[SIZE_DAT];
} CHAT_MSG_h;

// 선 그리기 메시지 형식
// sizeof(DRAWLINE_MSG) == 256
typedef struct DRAWLINE_MSG_h
{
	int type;
	int color;
	int x0, y0;
	int x1, y1;
	char dummy[SIZE_TOT - 6 * sizeof(int)];
} DRAWLINE_MSG_h;

// 그림 지우기 메시지 형식
// sizeof(ERASEPIC_MSG) == 256
typedef struct ERASEPIC_MSG_h
{
	int type;
	char dummy[SIZE_DAT];
} ERASEPIC_MSG_h;

// 대화상자 프로시저
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
// 자식 윈도우 프로시저
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);
// 소켓 통신 스레드 함수
DWORD WINAPI ClientMain(LPVOID arg);
DWORD WINAPI ReadThread(LPVOID arg);
DWORD WINAPI WriteThread(LPVOID arg);
// 에디트 컨트롤 출력 함수
void DisplayText(const char* fmt, ...);