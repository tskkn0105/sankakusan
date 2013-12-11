#include<tweet.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<uxtheme.h>

#include <vector>
#include <string>
#include <wininet.h>
#include<TCHAR.h>

#if DXLIBFLAG
#include"DxLib.h"
#endif

#pragma once
#pragma comment(lib, "UxTheme.lib")
#pragma comment(lib, "wininet.lib")//URL�̃\�[�X��\���Ƃ������邽�߂̕�
#pragma comment(lib, "imm32.lib" )// �h�l�d����p���C�u����

LRESULT CALLBACK ChildProc(HWND hChdWnd, UINT msg, WPARAM wp, LPARAM lp);
HWND hWnd;
static std::string init_key,init_secret;
static int ReturnNum;
static TCHAR* outdata;
static LPSTR outurl;
static bool rbol;
#define MESSAGE 100
#define ATT     101

void init(){

#if 0
	//�f�o�b�O�p�ŏI�I�ɂ͂������������ƁI
	init_key = GetKey();
	init_secret = GetSecret();
#else
	init_key = "";
	init_secret = "";
	std::string retnum = "";

	TCHAR buf[MAX_PATH*1024] = "";
	std::string LineReadText = "\0";
	HANDLE hkey = CreateFile( _T("option.ini"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hkey != INVALID_HANDLE_VALUE ){  //�{���ɊJ�����Ƃ��ł�����
		DWORD readsize;
		ReadFile( hkey,buf, sizeof(buf), &readsize, NULL );
		buf[readsize] = TEXT('\0');	//������'\0'�������̂ŕt��
		CloseHandle( hkey );
		int LineNum=0;
		for(int i=0;buf[i]>0&&LineNum<=4;i++){
			if(buf[i]=='\r'||buf[i]=='\n'){}
			else if(1 == LineNum){ retnum += buf[i]; }
			else if(3 == LineNum){ init_key += buf[i]; }
			else if(4 == LineNum){ init_secret += buf[i]; }
			if(buf[i]=='\n'){ LineNum++; }
		}
		ReturnNum = atoi(retnum.c_str());
	}
#endif
}

bool TweetFlag(){
	if(ReturnNum== 0 ){ return true; }
	else{ return false; }
}
void imedel(){
	//ime���I�t
	HIMC hImc;
	hImc = ImmGetContext( hWnd );
	ImmSetOpenStatus(hImc, false);
	ImmReleaseContext(hWnd, hImc);
}

void tweet(std::string text,LPSTR url){
	if(ReturnNum == 0){
		//������key�Ƃ�secret�Ƃ����擾���Ă����񂾂����炱���̕�����SetTweetText�ɕύX
		//SetTweetText�ɂ����ꍇ�ASetTweetText(text,init_key,initsecret,[�����Ŏ擾���Ă����L�[],[�����Ŏ擾���Ă���secret]);
		//�ŏ����Ă�������
		tweetText(text,url,init_key,init_secret);
	}
}
#if _UNICODE
void tweetA(std::wstring edit){
	char utf8[1000];
	if (!edit.empty()) {
		int n;
		wchar_t ucs2[1000];
		n = MultiByteToWideChar(CP_ACP, 0, edit.c_str(), edit.size(), ucs2, 1000);
		n = WideCharToMultiByte(CP_UTF8, 0, ucs2, n, utf8, 1000, 0, 0);
		edit.assign(utf8, n);
	}
	tweetTextA(utf8,init_key,init_secret);
}
#endif
/*
	�ʑ���\��������
	childwindow���ǂ����邩
	HWND�������Ă���邩�ǂ���
*/
ATOM InitApp(HINSTANCE hInst, WNDPROC Proc, LPCSTR szClassName)
{
	WNDCLASSEX wc;
	
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Proc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = DLGWINDOWEXTRA;
	wc.hInstance = hInst;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;

	wc.hIcon = (HICON)LoadImage(NULL,MAKEINTRESOURCE(IDI_APPLICATION),IMAGE_ICON,0,0,LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(NULL,MAKEINTRESOURCE(IDC_ARROW),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE | LR_SHARED);
	wc.hIconSm = wc.hIcon;

	//���݂̃e�[�}
	if(!IsThemeActive()) wc.hbrBackground = (HBRUSH)CreateSolidBrush(GetSysColor(COLOR_MENU));
	else wc.hbrBackground = (HBRUSH)CreateSolidBrush(GetSysColor(COLOR_MENUBAR));

	return (RegisterClassEx(&wc));
}

HWND ChildWindow(char* Text,LPSTR url ){

	int w = 400;
	int h = 170;
	
	if(IsThemeActive()) h += 8;
	RECT rc = {0,0,w,h};

	outdata = Text;
	outurl = url;

	InitApp(NULL,ChildProc,_T("Child"));

	/////
#if DXLIBFLAG
	int dx,dy,wx,wy;
	GetWindowSize(&dx,&dy);
	GetWindowPosition(&wx,&wy);
	/////

	HWND hWndChild = CreateWindow(
			_T("Child"),_T("���[��"),
			WS_VISIBLE|WS_CAPTION|WS_SYSMENU,
			//�\���ʒu
			3+wx+(dx-w)/2,22+wy+(dy-h)/2,
			//( GetSystemMetrics( SM_CXSCREEN ) - rc.right-rc.left ) / 2, (GetSystemMetrics( SM_CYSCREEN ) - rc.bottom-rc.top ) / 2,
			w,h,NULL,NULL,NULL,NULL);
#else
	HWND hWndChild = CreateWindow(
			_T("Child"),_T("���[��"),
			WS_VISIBLE|WS_CAPTION|WS_SYSMENU,
			//�\���ʒu
			( GetSystemMetrics( SM_CXSCREEN ) - rc.right-rc.left ) / 2, (GetSystemMetrics( SM_CYSCREEN ) - rc.bottom-rc.top ) / 2,
			w,h,NULL,NULL,NULL,NULL);
#endif

	hWnd = hWndChild;

	ShowWindow(hWndChild, SW_SHOW);
	UpdateWindow(hWndChild);

	return hWndChild;
}

LRESULT CALLBACK ChildProc(HWND hChdWnd, UINT msg, WPARAM wp, LPARAM lp){

	static std::string textdata = _T("");
	static int flag;

	switch(msg){
	case WM_CREATE://�������ꂽ�Ƃ�
		CreateWindow(_T("STATIC"),outdata,WS_CHILD|WS_VISIBLE|SS_LEFT|SS_CENTERIMAGE,10,10,(((LPCREATESTRUCT)lp)->cx)-25,30,hChdWnd,0,((LPCREATESTRUCT)lp)->hInstance,0);
		CreateWindowEx(WS_EX_CLIENTEDGE,TEXT("EDIT"),0,WS_CHILD|WS_VISIBLE|WS_TABSTOP|ES_MULTILINE,10,50,(((LPCREATESTRUCT)lp)->cx)-25,45,hChdWnd,(HMENU)MESSAGE,((LPCREATESTRUCT)lp)->hInstance,0);
		CreateWindow(_T("BUTTON"),_T("�Ԃ₭"),WS_CHILD|WS_VISIBLE|WS_TABSTOP,(((LPCREATESTRUCT)lp)->cx)/2-40,110-5,80,30,hChdWnd,(HMENU)ATT,((LPCREATESTRUCT)lp)->hInstance,0);
		textdata = outdata;
		flag = 1;
#if DXLIBFLAG
		SetUseIMEFlag(true);
#endif
		break;
	case WM_COMMAND:
		switch(LOWORD(wp)){
			case ATT:
				{//�c�C�[�g����AMESSAGE�ɓ����Ă镶�͂��N���A
					TCHAR Data[200];
					DWORD dwMessage = GetDlgItemText(hChdWnd,MESSAGE,Data,sizeof(Data));
					
					///�X�N���[���Ȃ����p40���A�S�p40��
					int textnum=0;
					TCHAR Text[81] = _T("");
					for(int i=0;textnum<=80&&i<=80;i++){
						Text[i]=Data[i];
						textnum++;
						if(Text[i]<=0x7f&&Text[i]>0x00){textnum++;}
					}
					
					std::string o_data;

					o_data = Data;
					o_data += " ";
					o_data += textdata;

					if(!webcop()){
#if DXLIBFLAG
						SetUseIMEFlag(false);
#endif
						imedel();DestroyWindow(hChdWnd); }
					if(ReturnNum == 0){
						//������key�Ƃ�secret�Ƃ����擾���Ă����񂾂����炱���̕�����SetTweetText�ɕύX
						tweetText(o_data,outurl,init_key,init_secret);
					}
					//SetDlgItemText(hChdWnd,MESSAGE,_T(""));
				}
#if DXLIBFLAG
				SetUseIMEFlag(false);
#endif
				imedel();
				DestroyWindow(hChdWnd);
				break;
		}

		break;
	case WM_CLOSE:
#if DXLIBFLAG
		SetUseIMEFlag(false);
#endif
		imedel();
		DestroyWindow(hChdWnd);
		break;
	case WM_ACTIVATE:
		flag = 2;
		break;
	case WM_NCACTIVATE:
		if(flag==2){
#if DXLIBFLAG
			SetUseIMEFlag(false);
#endif
			imedel();DestroyWindow(hChdWnd); }
		break;

		default:
			return (DefWindowProc(hChdWnd, msg, wp, lp));
	}

	return 0;
}


