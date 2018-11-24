#pragma once
#define DIRECTINPUT_VERSION 0x0800

#include <windows.h>
#include <assert.h>
#include <tchar.h>

#include <iostream>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <d3dx11.h>
#include <dxgi.h>
#include <dinput.h>

#include "D3Dcompiler.h"		//D3DCOMPILE_DEBUG
#include <math.h>
using namespace std;

//������Ʈ �Ӽ����� �߰� ���Ӽ��� ������ �ڵ�� ������ �ִ�.
//#pragma comment(lib, "xCoreLib.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment( lib, "dinput8.lib")
#pragma comment( lib, "dxguid.lib")
#pragma comment( lib, "d3dx11.lib")
#pragma comment(lib, "winmm.lib")

#pragma warning (disable : 4005)

typedef std::basic_string <char>	C_STR;	//multi-byte
typedef std::basic_string <wchar_t>	W_STR;	//unicode byte
typedef std::basic_string <TCHAR>	T_STR;	//������Ʈ�Ӽ��� ��Ƽ����Ʈ�̸� ��Ƽ����Ʈ, �����ڵ��̸� �����ڵ�� �ٲ�.

											//string a;		//multi-byte
											//wstring b;	//unicode byte

#define GAMESTART int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow) {
											//
											////L#s ==> L"" s�� ���ڿ��̹Ƿ� #�� ���δ�. �����ڵ�� L�� ���δ�.
											//#define GAMERUN(s) xWindow win; win.SetWindow(hInstance, L#s, 600, 800); win.Run();
											//
#define GAME_END }


											//L#s ==> L"" s�� ���ڿ��̹Ƿ� #�� ���δ�. �����ڵ�� L�� ���δ�.

#define GAMERUN(s, w, h) int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow) { Sample win; win.SetWindow(hInst, L#s, w, h); win.Run(); }



extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;
extern float		g_fSecPerFrame;
extern RECT			g_rtClient;
extern float		g_fGameTimer;
extern float		g_fSecPerFrame;
extern ID3D11Device*g_pd3dDevice;
extern ID3D11DeviceContext*	g_pContext;
extern bool g_bActiveApp;


typedef struct _D3DVECTOR {
	float x;
	float y;
	float z;
} D3DVECTOR;


struct tPoint
{
	float x, y;
};


extern HDC g_hOffScreenDC;





template<class T> class TSingleton
{
public:
	static T& GetInstance()
	{
		static T theSingleInstance;
		return theSingleInstance;
	}
};



#ifndef V_RETURN
#define V_RETURN(x) { hr = (x); if( FAILED(hr) ) {return hr;} }
#endif

#ifndef V
#define V(x) { hr = (x);}
#endif