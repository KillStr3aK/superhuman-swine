#pragma once
#include <Windows.h>
#include <stdarg.H>
#include <iostream>
#include <vector>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

#include "Hook/detours.h" //UC
#include "Hook/d3d9.h" //GH
#include "CColor.h" //UC? maybe, idk

#include "SGameWorld.h"
#include "SCampaign.h"
#include "SUnit.h"

#define MAXPLAYERS 9
#define GAMETITLE "S.W.I.N.E. HD Remaster"
#define TITLE "SUPERHUMAN - S.W.I.N.E."

#define EchoColored 0x9E980
#define AirStrike 0x9BC70
#define CreateUnit 0x9DA40
#define Explode 0xB9340

typedef void(__thiscall* fEchoColored)(SGameWorld*, const char*, unsigned int);
typedef void(__thiscall* fAirStrike)(SGameWorld*, float, float, int, int);
typedef void(__thiscall* fExplodeUnit)(SUnit*);

typedef int(__thiscall* oCreateUnit)(SGameWorld*, int, const char*, float, float, float, int*, int, float, bool, int);

static fExplodeUnit ExplodeUnit;
static fAirStrike rAirStrike;
static fEchoColored rEchoColored;

static oCreateUnit pCreateUnit;

class Superhuman {
public:
    LPDIRECT3DDEVICE9 pDevice;
    SCampaign* campaign;
    SGameWorld* gameworld;
    SUnit* unit[MAX_UNITS];
    SUnitProp prop[MAX_UNITS];
    SUnitDescription* desc = new SUnitDescription;

    Superhuman();
	bool IsInGame(); //buggy sometimes, causing random crashes while in the menu
    bool IsValidUnit(SUnit* unit, bool iterate = true, int index = 0, bool exclview = true, bool exclmine = true, bool exlflag = true);
    bool IsServiceUnit(SUnit* unit);
    bool IsSpecialUnit(SUnit* unit);
    bool IsHeroUnit(SUnit* unit);
    bool HasTurretByDefault(SUnit* unit);
    bool HasProjectile(SUnit* unit);
    SUnit** GetUnits();
    SUnit* GetUnit(int unitindex);
    SUnitDescription* GetDescription();
    SCampaign* GetCampaign();
    SGameWorld* GetGameWorld();
    bool IsHelicopter(const char* classname);
    bool IsBomber(const char* classname);
    int GetSP();
    void GiveSP(int amount);
    void SetSP(int newsp);

    void FakeExplode();
    void CallAirStrike(float x, float y, int player = 0, int commanderidx = 0);
    void PrintToChat(const char* message, unsigned int color = 16777215);

    bool ShowMenu();
    void SetMenuState(bool newstate);
    void DrawMenu();
    void InitMenuStyle();
    void OnGameFrame();
    bool IsBadPtr(DWORD* ptr);

    DWORD dwGetModuleBase();
    DWORD dwGetSGameWorld();
    DWORD dwGetFirstEntity();
    DWORD dwGetCampaign();
private:
    DWORD BaseAddress;
    DWORD CampaignAddress;

    bool bConsole = false;
    bool bShowMenu = false;
    void CreateConsole(const char* title);
    void Initialize();
    DWORD MultiPtr(DWORD ptr, std::vector<unsigned int> offsets);
};