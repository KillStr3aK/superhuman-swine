#include "Superhuman.h"

Superhuman* sh = new Superhuman;

namespace Hooks {
    int __fastcall hkCreateUnit(SGameWorld* SGameWorld, void*, int player, const char* classname, float x, float z, float dir, int* upgrades, int level, float xp, bool isStarter, int kills)
    {
        if (!strcmp(sh->GetDescription()->newclassname, "None") == 0) {
            if (!sh->IsHelicopter(classname) && !sh->IsBomber(classname))
            {
                return pCreateUnit(SGameWorld, player, sh->GetDescription()->newclassname, x, z, dir, upgrades, sh->GetDescription()->level, sh->GetDescription()->xp, sh->GetDescription()->isStarter, sh->GetDescription()->kills);
            }
        }

        return pCreateUnit(SGameWorld, player, classname, x, z, dir, upgrades, level, xp, isStarter, kills);
    }

    LRESULT __stdcall hkWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
        if (sh->ShowMenu() && ImGui::GetIO().WantCaptureMouse && (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP || msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP || msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP || msg == WM_MOUSEWHEEL || msg == WM_MOUSEMOVE))
        {
            return TRUE;
        }
        return CallWindowProc(wProc, hwnd, msg, wparam, lparam);
    }

    long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
    {
        if (!bInit)
        {
            sh->pDevice = pDevice;
            ImGui::CreateContext();
            ImGui_ImplWin32_Init(FindWindowA(NULL, GAMETITLE));
            ImGui_ImplDX9_Init(pDevice);
            sh->InitMenuStyle();
            bInit = true;
        }

        if (sh->ShowMenu()) sh->DrawMenu();
        return EndScene(pDevice);
    }

    long __stdcall hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* params)
    {
        ImGui_ImplDX9_InvalidateDeviceObjects();
        auto hr = Reset(pDevice, params);
        ImGui_ImplDX9_CreateDeviceObjects();
        return hr;
    }
}

auto superHuman() -> void
{
    wProc = (WNDPROC)(SetWindowLongPtr(FindWindowA(NULL, GAMETITLE), GWLP_WNDPROC, LONG_PTR(Hooks::hkWndProc)));
    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
    {
        EndScene = (_EndScene)DetourFunction((PBYTE)d3d9Device[42], (PBYTE)Hooks::hkEndScene);
        Reset = (_Reset)DetourFunction((PBYTE)d3d9Device[16], (PBYTE)Hooks::hkReset);
    }

    pCreateUnit = (oCreateUnit)DetourFunction((PBYTE)(sh->dwGetModuleBase() + CreateUnit), (PBYTE)Hooks::hkCreateUnit);
    
    while (true) {
        sh->OnGameFrame();
        if (GetAsyncKeyState(VK_INSERT) & 1) sh->SetMenuState(sh->ShowMenu()?false:true);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH: { CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)superHuman, NULL, NULL, NULL); }
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}