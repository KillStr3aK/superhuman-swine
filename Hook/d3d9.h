#pragma once
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

static bool bInit = false;
static void* d3d9Device[119];

typedef long(__stdcall* _EndScene)(LPDIRECT3DDEVICE9);
typedef long(__stdcall* _Reset)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

static _EndScene EndScene;
static _Reset Reset;
static WNDPROC wProc;

static HWND window;
BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);
HWND GetProcessWindow();
bool GetD3D9Device(void** pTable, size_t Size);