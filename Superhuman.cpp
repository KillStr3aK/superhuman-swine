#include "Superhuman.h"

namespace Draw {
    void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* dev)
    {
        D3DRECT BarRect = { x, y, x + w, y + h };
        dev->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
    }

    void DrawRectRainbow(int x, int y, int width, int height, float flSpeed, float& flRainbow, IDirect3DDevice9* device)
    {
        Color colColor(0, 0, 0);

        flRainbow += flSpeed;
        if (flRainbow > 1.f) flRainbow = 0.f;

        for (int i = 0; i < width; i++)
        {
            float hue = (1.f / (float)width) * i;
            hue -= flRainbow;
            if (hue < 0.f) hue += 1.f;

            Color colRainbow = colColor.FromHSB(hue, 1.f, 1.f);
            DrawFilledRect(x + i, y, 1, height, colRainbow.GetD3DColor(), device);
        }
    }

    static void HelpMarker(const char* desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

    void UnitPage(Superhuman* sh)
    {
        static SUnit* unit;
        static int selectedunit = -1;
        static int filterteam = -1;
        static bool bShowOwn = false;
        ImGui::Columns(2, nullptr, false);
        ImGui::Checkbox("Filter units", &bShowOwn);
        ImGui::SameLine(0.0f, 43.0f);
        ImGui::PushItemWidth(85.0f);
        ImGui::InputInt("Team ID", &filterteam, 1, 1);
        ImGui::PopItemWidth();
        ImGui::SameLine(0.0f, 2.0f);
        Draw::HelpMarker("Singleplayer:\n1 - Enemy/CPU\n0 - You\n\nMultiplayer:\n0 - Host\n1 - Player1\n2 - Player2\n...");
        if (!sh->IsInGame())
        {
            bShowOwn = false;
            selectedunit = -1;
            filterteam = -1;
            ImGui::SameLine(0.0f, 10.0f);
            ImGui::TextColored(RED, "Must be ingame");
        }
        if (filterteam < 0 || filterteam > MAXPLAYERS) filterteam = 0;
        ImGui::Text("Select unit");
        ImGui::ListBoxHeader("", ImVec2(225.0f, 0.0f));
        if (sh->IsInGame())
        {
            int invalid = 0;
            static char ulabel[100];
            if (ImGui::Button("None")) selectedunit = -1;
            for (int i = 0; i < MAX_UNITS; i++)
            {
                unit = sh->GetUnit(i);
                if (sh->IsValidUnit(unit, true, i))
                {
                    if (bShowOwn && unit->TEAMID != filterteam) continue;
                    sprintf_s(ulabel, "%s (%i)", unit->CLASSNAME, unit->ID);
                    if (ImGui::Button(ulabel)) selectedunit = i;
                } else {
                    if (i > MAX_UNITS_MULTIPLAYER) //Prevent crash in multiplayer, Found SCampaign::IsMultiMode() but that returns 0 even in multiplayer
                    {
                        ++invalid;
                        if (invalid > 5) break;
                        else invalid = 0;
                    }
                }
            }
        }
        ImGui::ListBoxFooter();
        if (selectedunit > -1)
        {
            unit = sh->GetUnit(selectedunit);
            ImGui::Text("Selected unit: %s (%i) [%p]", unit->CLASSNAME, unit->ID, unit);
            ImGui::InputFloat("Health", &unit->HEALTH);
            if (!sh->IsServiceUnit(unit))
            {
                if (!(strcmp(unit->CLASSNAME, UNIT_CLASS_RABBIT_MOVINGFORCE) == 0) && !(strcmp(unit->CLASSNAME, UNIT_CLASS_PIG_MOVINGFORCE) == 0)) ImGui::InputInt("Ammo", &unit->AMMO);
                else ImGui::InputInt("Nukecharge", &unit->NUKECHARGE);
                if (!sh->IsSpecialUnit(unit)) ImGui::InputFloat("Fuel", &unit->FUEL);
                ImGui::InputInt("Level", &unit->LEVEL);
                if (unit->LEVEL < 0 || unit->LEVEL > 2) unit->LEVEL = 0;
                ImGui::InputInt("Firerate", &unit->FIRERATE);
                ImGui::SameLine(0.0f, 2.0f);
                Draw::HelpMarker("Less = Faster\nMore = Slower\n\nLess than zero stop the unit from shooting at all, irreversible");
            }

            ImGui::TextColored(RED, "X: %.0f Y: %.0f", unit->POSITIONX, unit->POSITIONY);
            ImGui::SameLine(0.0, 2.0f);
            Draw::HelpMarker("Current position");
            static int iNewPos[2] = { (int)unit->POSITIONX, (int)unit->POSITIONY };
            ImGui::InputInt2("", &iNewPos[0]);
            ImGui::SameLine(0.0f, 10.0f);
            if (ImGui::Button("Teleport"))
            {
                unit->POSITIONX = float(iNewPos[0]);
                unit->POSITIONY = float(iNewPos[1]);
            }

            ImGui::Checkbox("Special", &unit->SPECIALTOGGLE);
            ImGui::SameLine(0.0f, 78.0f);
            ImGui::PushItemWidth(85.0f);
            ImGui::InputInt("TEAM ID", &unit->TEAMID, 1, 1);
            ImGui::SameLine(0.0f, 2.0f);
            if (unit->TEAMID > MAXPLAYERS || unit->TEAMID < 0) unit->TEAMID = 0;
            Draw::HelpMarker("Singleplayer:\n1 - Enemy/CPU\n0 - You\n\nMultiplayer:\n0 - Host\n1 - Player1\n2 - Player2\n...");
            ImGui::Checkbox("Untargetable", &unit->UNTARGETABLE);

            if (!sh->IsServiceUnit(unit) && sh->HasTurretByDefault(unit))
            {
                ImGui::SameLine(0.0f, 43.0f);
                ImGui::Checkbox("Spinbot", &sh->prop[selectedunit].SpinBot);
                ImGui::SameLine(0.0f, 5.0f);
                ImGui::TextColored(unit->TURRETANGLE > 10.0f ? RED : unit->TURRETANGLE > 5.0f ? BLUE : GREEN, "ANG: %.3f", unit->TURRETANGLE);
                ImGui::Checkbox("God Mode", &sh->prop[selectedunit].GodMode);
                ImGui::SameLine(0.0f, 71.0f);
                ImGui::Checkbox("Infinite Resources", &sh->prop[selectedunit].InfiniteResources);
            }

            ImGui::NextColumn();
            if (sh->HasProjectile(unit))
            {
                char* currpr = unit->PROJECTILE;
                const char* projectiles[] = { currpr, AMMO_TYPE_INVISIBLE, AMMO_TYPE_MORTAR, AMMO_TYPE_MOVINGFORCE_PIG, AMMO_TYPE_MOVINGFORCE_RABBIT, AMMO_TYPE_BOMB, AMMO_TYPE_ROCKET, AMMO_TYPE_HOMEROCKET, AMMO_TYPE_ARTILLERY, AMMO_TYPE_CRIT_PIG, AMMO_TYPE_CRIT_RABBIT, AMMO_TYPE_MINE, AMMO_TYPE_SERVICE, AMMO_TYPE_AMMO, AMMO_TYPE_FUEL };
                static int item_current = 0;
                if (ImGui::Combo("Projectile", &item_current, projectiles, IM_ARRAYSIZE(projectiles))) unit->PROJECTILE = (char*)projectiles[item_current];
                ImGui::SameLine(0.0f, 2.0f);
                Draw::HelpMarker("Mortar: Mozsar lovedek\nNuke: Radioaktiv hordo diszno\nRocket: Raketa\nArtillery:Loveg lovedek\n\nIts coded like that in the game, not my business");
            }

            if (!sh->IsSpecialUnit(unit) && !sh->IsServiceUnit(unit))
            {
                char* currcr = unit->CHARACTER;
                const char* characters[] = { currcr, CHARACTER_PIG_COMMAND, CHARACTER_PIG_TANK, CHARACTER_PIG_HARDTANK, CHARACTER_PIG_ARMORED, CHARACTER_PIG_ARTILLERY, CHARACTER_PIG_ROCKET, CHARACTER_PIG_MORTAR, CHARACTER_PIG_MINE, CHARACTER_PIG_TOW, CHARACTER_PIG_CHOPPER, CHARACTER_PIG_BOMBER, CHARACTER_PIG_MOVINGFORCE,
                                                    CHARACTER_RABBIT_COMMAND, CHARACTER_RABBIT_TANK, CHARACTER_RABBIT_HARDTANK, CHARACTER_RABBIT_ARMORED, CHARACTER_RABBIT_ARTILLERY, CHARACTER_RABBIT_ROCKET, CHARACTER_RABBIT_MORTAR, CHARACTER_RABBIT_MINE, CHARACTER_RABBIT_TOW, CHARACTER_RABBIT_CHOPPER, CHARACTER_RABBIT_BOMBER, CHARACTER_RABBIT_MOVINGFORCE };
                static int item_current = 0;
                if (ImGui::Combo("Character", &item_current, characters, IM_ARRAYSIZE(characters))) unit->CHARACTER = (char*)characters[item_current];
                ImGui::SameLine(0.0f, 2.0f);
                Draw::HelpMarker("Some of them may not work properly");

                char* currvc = unit->VOICE;
                const char* voices[] = { currcr, VOICE_PIG_COMMAND, VOICE_PIG_TANK, VOICE_PIG_HARDTANK, VOICE_PIG_ARMORED, VOICE_PIG_ARTILLERY, VOICE_PIG_ROCKET, VOICE_PIG_MORTAR, VOICE_PIG_MINE, VOICE_PIG_TOW, VOICE_PIG_CHOPPER, VOICE_PIG_BOMBER, VOICE_PIG_MOVINGFORCE, VOICE_RABBIT_COMMAND, VOICE_RABBIT_TANK, VOICE_RABBIT_HARDTANK,
                                                VOICE_RABBIT_ARMORED, VOICE_RABBIT_ARTILLERY, VOICE_RABBIT_ROCKET, VOICE_RABBIT_MORTAR, VOICE_RABBIT_MINE, VOICE_RABBIT_TOW, VOICE_RABBIT_CHOPPER, VOICE_RABBIT_BOMBER, VOICE_RABBIT_MOVINGFORCE };
                static int item_current_voice = 0;
                if (ImGui::Combo("Voice", &item_current_voice, voices, IM_ARRAYSIZE(voices))) unit->VOICE = (char*)voices[item_current_voice];
                ImGui::SameLine(0.0f, 2.0f);
                Draw::HelpMarker("Some of them may not work properly");
            }

            ImGui::NewLine();
            ImGui::SliderFloat("Front Armor", &unit->FRONTARMOR, FLT_MIN, 100.0);
            ImGui::SliderFloat("Back Armor", &unit->BACKARMOR, FLT_MIN, 100.0);
            ImGui::SliderFloat("Top Armor", &unit->TOPARMOR, FLT_MIN, 100.0);

            ImGui::SliderFloat("View range", &unit->VIEWRANGE, FLT_MIN, 50.0);
            ImGui::SameLine(0.0f, 2.0f);
            Draw::HelpMarker("May cause crash if you increment it drastically in a short while");
            ImGui::SliderFloat("Min range", &unit->MINRANGE, FLT_MIN, 100.0);
            ImGui::SliderFloat("Max range", &unit->MAXRANGE, FLT_MIN, 100.0);
            ImGui::SliderFloat("Action range", &unit->ACTIONRANGE, FLT_MIN, 100.0);
            if (!sh->IsServiceUnit(unit))
            {
                ImGui::SliderFloat("Speed", &unit->SPEED, FLT_MIN, 5.0);
                ImGui::SameLine(0.0f, 2.0f);
                Draw::HelpMarker("You should change the 'Body rotation' either to avoid the unit from struggling");
                ImGui::SliderFloat("Body rotation", &unit->BODYROTATION, FLT_MIN, 50.0);
                ImGui::SliderFloat("Damage", &unit->DAMAGE, FLT_MIN, 200.0);
                ImGui::SliderFloat("Aim speed", &unit->AIMSPEED, FLT_MIN, 5.0);
            }
        }
    }
    
    void CampaignPage(Superhuman* sh)
    {
        ImGui::Columns(2, nullptr, false);
        if (!sh->IsInGame()) ImGui::TextColored(RED, "Must be ingame");
        else {
            ImGui::TextColored(GOLD, "Ingame cash");
            static int sp = sh->GetSP();
            ImGui::InputInt("SP", &sp, 100, 1000); //&sh->campaign->SP sucks
            sh->SetSP(sp);
            ImGui::NewLine();
            static int iTargetPos[2] = { 280, 54 };
            ImGui::TextColored(RED, "Target Position");
            ImGui::InputInt2("", &iTargetPos[0]);
            ImGui::SameLine(0.0f, 10.0f);
            if (ImGui::Button("Airstrike")) sh->CallAirStrike((float)iTargetPos[0], (float)iTargetPos[1]);
            ImGui::SameLine(0.0f, 2.0f);
            Draw::HelpMarker("May cause crash if you call it multiple times in a short while");
            ImGui::NewLine();
            ImGui::TextColored(GREEN, "Custom Message");
            static char sMessage[128] = "SUPERHUMAN";
            static ImVec4 sColor = { 0.14f, 1.0f, 0.0f, 1.0f };
            ImGui::ColorEdit3("Message Color", &sColor.x);
            ImGui::SameLine(0.0f, 2.0f);
            Draw::HelpMarker("Buggy asfuck but who cares tbh");
            ImGui::InputText("", sMessage, IM_ARRAYSIZE(sMessage));
            ImGui::SameLine(0.0f, 10.0f);
            if (ImGui::Button("Send")) sh->PrintToChat(sMessage, (unsigned int)ImGui::ColorConvertFloat4ToU32(sColor));
            ImGui::NewLine();
            ImGui::TextColored(GOLD, "Random shit");
            if (ImGui::Button("Fake Explode")) sh->FakeExplode();
            ImGui::SameLine(0.0f, 2.0f);
            Draw::HelpMarker("Fake explode every selected unit\nMay cause crash if you call it multiple times in a short while");
            static int targetteam = 0;
            if (ImGui::Button("Get Units"))
            {
                static SUnit* unit;
                static int invalid = 0;
                for (int i = 0; i < MAX_UNITS; i++)
                {
                    unit = sh->GetUnit(i);
                    if (sh->IsValidUnit(unit, true, i))
                    {
                        if (unit->TEAMID != targetteam) unit->TEAMID = targetteam;
                    }
                    else {
                        if (i > MAX_UNITS_MULTIPLAYER) //Prevent crash in multiplayer, Found SCampaign::IsMultiMode() but that returns 0 even in multiplayer
                        {
                            ++invalid;
                            if (invalid > 5) break;
                            else invalid = 0;
                        }
                    }
                }
            }
            ImGui::SameLine(0.0f, 10.0f);
            ImGui::PushItemWidth(85.0f);
            ImGui::InputInt("Target Team", &targetteam, 1, 1);
            ImGui::PopItemWidth();

            ImGui::NextColumn();
            ImGui::TextColored(GOLD, "Unit Market");
            const char* units[] = { "None", UNIT_CLASS_RABBIT_BUNKER, UNIT_CLASS_RABBIT_BUNKER_AIRDEFENSE, UNIT_CLASS_RABBIT_BUNKER_ARTILLERY, UNIT_CLASS_PIG_BUNKER, UNIT_CLASS_PIG_BUNKER_AIRDEFENSE, UNIT_CLASS_PIG_BUNKER_ARTILLERY, UNIT_CLASS_PIG_MOVINGFORCE, UNIT_CLASS_RABBIT_MOVINGFORCE, UNIT_CLASS_PIG_COMMAND, UNIT_CLASS_PIG_TANK,
                                            UNIT_CLASS_PIG_HARDTANK, UNIT_CLASS_PIG_ARMORED, UNIT_CLASS_PIG_ARTILLERY, UNIT_CLASS_PIG_ROCKET, UNIT_CLASS_PIG_MORTAR, UNIT_CLASS_PIG_TOW, UNIT_CLASS_PIG_MINE, UNIT_CLASS_RABBIT_COMMAND, UNIT_CLASS_RABBIT_TANK, UNIT_CLASS_RABBIT_HARDTANK, UNIT_CLASS_RABBIT_ARMORED, UNIT_CLASS_RABBIT_ARTILLERY,
                                            UNIT_CLASS_RABBIT_ROCKET, UNIT_CLASS_RABBIT_MORTAR, UNIT_CLASS_RABBIT_MINE, UNIT_CLASS_RABBIT_TOW, UNIT_CLASS_HERO_ZSK, UNIT_CLASS_HERO_NYSZ, UNIT_CLASS_HERO_FW, UNIT_CLASS_HERO_PR, UNIT_CLASS_HERO_SPY, UNIT_CLASS_HERO_LEGHAJO };
            static int item_current_unit = 0;
            if (ImGui::Combo("Select Unit", &item_current_unit, units, IM_ARRAYSIZE(units))) sh->GetDescription()->newclassname = units[item_current_unit] == "None" ? NULL : (char*)units[item_current_unit];
            ImGui::SameLine(0.0f, 2.0f);
            Draw::HelpMarker("Your next purchase will be this unit, no matter what you select in the real menu\nYou can even select special units like bunkers, heroes etc then pay for an ammo service..\nThe unit color will be the same as your color\n\nSingleplayer:\nPig - Blue\nRabbit - Yellow");
            ImGui::InputInt("Level", &sh->GetDescription()->level, 1, 1);
            if (sh->GetDescription()->level < 0 || sh->GetDescription()->level > 2) sh->GetDescription()->level = 0;
            ImGui::InputFloat("XP", &sh->GetDescription()->xp, 10.0f, 50.0f, 2);
            ImGui::SameLine(0.0f, 2.0f);
            Draw::HelpMarker("Unit experience\n0 - 10.000");
            if (sh->GetDescription()->xp < 0.0 || sh->GetDescription()->xp > 10000.0) sh->GetDescription()->xp = 0.0;
            ImGui::InputInt("Kills", &sh->GetDescription()->kills, 1, 10);
            ImGui::Checkbox("Starter", &sh->GetDescription()->isStarter);
            ImGui::SameLine(0.0f, 10.0f);
            if (ImGui::Button("RESET"))
            {
                item_current_unit = 0;
                sh->GetDescription()->ResetVariables();
            }
        }
    }

    void WelcomeMenu()
    {
        ImGui::TextColored(GOLD, "You may experience crashes");
        ImGui::TextColored(GREEN, "Most of the features got detected in multiplayer and you will be kicked if you try to use them");
    }
}

void Superhuman::DrawMenu()
{
    static float rr;
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();
    ImGui::SetNextWindowSize(ImVec2(960, 680));
    ImGui::Begin(TITLE, NULL, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse);
    Draw::DrawRectRainbow((int)ImGui::GetWindowPos().x, (int)ImGui::GetWindowPos().y-2, 960, 2, 0.003f, rr, this->pDevice);

    static int iMenuPage = 3;
    if (ImGui::Button("UNITS", ImVec2(310.0f, 50.0f))) iMenuPage = 0;
    ImGui::SameLine(0.0, 2.0f);
    if (ImGui::Button("CAMPAIGN", ImVec2(310.0f, 50.0f))) iMenuPage = 1;
    ImGui::SameLine(0.0, 2.0f);
    if (ImGui::Button("EXTRA", ImVec2(310.0f, 50.0f))) iMenuPage = 2;
    ImGui::NewLine();

    switch (iMenuPage) {
        case 0: Draw::UnitPage(this);
            break;
        case 1: Draw::CampaignPage(this);
            break;
        default: Draw::WelcomeMenu();
    }

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void Superhuman::OnGameFrame()
{
    if (this->IsInGame())
    {
        DWORD* firstEnt = (DWORD*)this->dwGetFirstEntity();
        for (int i = 0; i < MAX_UNITS; i++)
        {
            if (IsBadPtr(firstEnt)) break;
            unit[i] = (SUnit*)*(firstEnt + (i * 2));

            if (IsValidUnit(unit[i], true, i))
            {
                if (prop[i].SpinBot)
                {
                    prop[i].flAngle += 0.03f;
                    unit[i]->TURRETANGLE = prop[i].flAngle;
                    if (prop[i].flAngle > 12.0) prop[i].flAngle -= 12.0;
                }

                if (prop[i].GodMode)
                {
                    unit[i]->HEALTH = unit[i]->MAXHP;
                }

                if (prop[i].InfiniteResources)
                {
                    unit[i]->AMMO = unit[i]->MAXAMMO;
                    unit[i]->FUEL = (float)unit[i]->MAXFUEL;
                    if (unit[i]->NUKECHARGE > 0) unit[i]->NUKECHARGE = 100; //Nuke charge will be set around 20-30
                }
            }  else {
                prop[i].ResetVariables();
            }
        }
    }
}

DWORD Superhuman::MultiPtr(DWORD ptr, std::vector<unsigned int> offsets) //GH
{
    DWORD addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        addr = *(DWORD*)addr;
        addr += offsets[i];
    }

    return addr;
}

Superhuman::Superhuman()
{
    this->Initialize();
    this->CreateConsole(TITLE);
    printf("LOADED\n");
}

void Superhuman::Initialize()
{
    this->BaseAddress = (DWORD)GetModuleHandle(NULL);
    this->campaign = (SCampaign*)(this->CampaignAddress = BaseAddress + 0x1B6128);
}

void Superhuman::CreateConsole(const char* title)
{
    if (!bConsole)
    {
        bConsole = AllocConsole();
        SetConsoleTitleA(title);
        FILE* fajl;
        freopen_s(&fajl, "CONIN$", "r", stdin);
        freopen_s(&fajl, "CONOUT$", "w", stderr);
        freopen_s(&fajl, "CONOUT$", "w", stdout);
    }
}

void Superhuman::FakeExplode()
{
    ExplodeUnit = (fExplodeUnit)(this->dwGetModuleBase() + Explode);
    SUnit* unit;
    int invalid = 0;
    for (int i = 0; i < MAX_UNITS; i++)
    {
        unit = GetUnit(i);
        if (IsValidUnit(unit, true, i))
        {
            if (unit->SELECTSTATUS >= UNIT_STATUS_SELECTED)
            {
                ExplodeUnit(unit);
            }
        } else {
            if (i > MAX_UNITS_MULTIPLAYER) //Prevent crash in multiplayer, Found SCampaign::IsMultiMode() but that returns 0 even in multiplayer
            {
                ++invalid;
                if (invalid > 5) break;
                else invalid = 0;
            }
        }
    }
}

void Superhuman::CallAirStrike(float x, float y, int player, int commanderidx)
{
    rAirStrike = (fAirStrike)(this->dwGetModuleBase() + AirStrike);
    rAirStrike((SGameWorld*)(this->dwGetSGameWorld()), x, y, player, commanderidx);
}

void Superhuman::PrintToChat(const char* message, unsigned int color)
{
    rEchoColored = (fEchoColored)(this->dwGetModuleBase() + EchoColored);
    rEchoColored((SGameWorld*)(this->dwGetSGameWorld()), message, color);
}

bool Superhuman::ShowMenu()
{
    return this->bShowMenu;
}

void Superhuman::SetMenuState(bool newstate)
{
    this->bShowMenu = newstate;
}

int Superhuman::GetSP()
{
    return *(int*)((*(DWORD*)this->dwGetCampaign()) + 0x24);
}

void Superhuman::GiveSP(int amount)
{
    *(DWORD*)((*(DWORD*)this->dwGetCampaign()) + 0x24) += amount;
}

void Superhuman::SetSP(int newsp)
{
    *(DWORD*)((*(DWORD*)this->dwGetCampaign()) + 0x24) = newsp;
}

bool Superhuman::IsInGame()
{
    if (!((bool)*(DWORD*)(*(DWORD*)(this->BaseAddress + 0x1B6120) + 0xC0))) return false;
    return (bool)*(DWORD*)(this->BaseAddress + 0x18D468);
}

DWORD Superhuman::dwGetCampaign()
{
    return this->CampaignAddress;
}

DWORD Superhuman::dwGetFirstEntity()
{
    return MultiPtr(CampaignAddress, { 0x8C, 0x43C, 0x4 });
}

DWORD Superhuman::dwGetModuleBase()
{
    return this->BaseAddress;
}

DWORD Superhuman::dwGetSGameWorld()
{
    return MultiPtr(CampaignAddress, { 0x8C, 0x43C, 0x1D4, 0x0, 0x0 });
}

SUnit* Superhuman::GetUnit(int unitindex)
{
    return this->unit[unitindex];
}

SUnit** Superhuman::GetUnits()
{
    return this->unit;
}

SUnitDescription* Superhuman::GetDescription()
{
    return this->desc;
}

SCampaign* Superhuman::GetCampaign()
{
    return this->campaign;
}

SGameWorld* Superhuman::GetGameWorld()
{
    return this->gameworld;
}

bool Superhuman::IsBadPtr(DWORD* ptr) //UC
{
    __try { volatile auto result = *ptr; }
    __except (EXCEPTION_EXECUTE_HANDLER) { return true; }
    return false;
}

bool Superhuman::IsHelicopter(const char* classname)
{
    if (strcmp(classname, UNIT_CLASS_RABBIT_CHOPPER) == 0) return true;
    if (strcmp(classname, UNIT_CLASS_PIG_CHOPPER) == 0) return true;
    return false;
}

bool Superhuman::IsBomber(const char* classname)
{
    if (strcmp(classname, UNIT_CLASS_RABBIT_BOMBER) == 0) return true;
    if (strcmp(classname, UNIT_CLASS_PIG_BOMBER) == 0) return true;
    return false;
}

bool Superhuman::IsServiceUnit(SUnit* unit)
{
    if (strcmp(unit->CLASSNAME, SERVICE_CLASS_AMMO) == 0) return true;
    if (strcmp(unit->CLASSNAME, SERVICE_CLASS_FUEL) == 0) return true;
    if (strcmp(unit->CLASSNAME, SERVICE_CLASS_HEALTH) == 0) return true;
    if (strcmp(unit->CLASSNAME, UNIT_CLASS_HERO_KERO) == 0) return true;
    return false;
}

bool Superhuman::IsSpecialUnit(SUnit* unit)
{
    if ((strcmp(unit->CLASSNAME, UNIT_CLASS_RABBIT_BUNKER) == 0) || (strcmp(unit->CLASSNAME, UNIT_CLASS_PIG_BUNKER) == 0)) return true;
    if ((strcmp(unit->CLASSNAME, UNIT_CLASS_RABBIT_BUNKER_AIRDEFENSE) == 0) || (strcmp(unit->CLASSNAME, UNIT_CLASS_PIG_BUNKER_AIRDEFENSE) == 0)) return true;
    if ((strcmp(unit->CLASSNAME, UNIT_CLASS_RABBIT_BUNKER_ARTILLERY) == 0) || (strcmp(unit->CLASSNAME, UNIT_CLASS_PIG_BUNKER_ARTILLERY) == 0)) return true;
    return false;
}

bool Superhuman::HasTurretByDefault(SUnit* unit)
{
    if ((strcmp(unit->CLASSNAME, UNIT_CLASS_PIG_TOW) == 0) || (strcmp(unit->CLASSNAME, UNIT_CLASS_RABBIT_TOW) == 0)) return false;
    if ((strcmp(unit->CLASSNAME, UNIT_CLASS_PIG_MINE) == 0) || (strcmp(unit->CLASSNAME, UNIT_CLASS_RABBIT_MINE) == 0)) return false;
    if ((strcmp(unit->CLASSNAME, UNIT_CLASS_PIG_COMMAND) == 0) || (strcmp(unit->CLASSNAME, UNIT_CLASS_RABBIT_COMMAND) == 0)) return false;
    if ((strcmp(unit->CLASSNAME, UNIT_CLASS_HERO_ZSK) == 0) || (strcmp(unit->CLASSNAME, UNIT_CLASS_HERO_NYSZ) == 0)) return false;
    if ((strcmp(unit->CLASSNAME, UNIT_CLASS_HERO_FW) == 0) || (strcmp(unit->CLASSNAME, UNIT_CLASS_HERO_PR) == 0)) return false;
    if (strcmp(unit->CLASSNAME, UNIT_CLASS_RABBIT_HARDTANK) == 0) return false;
    return true;
}

bool Superhuman::HasProjectile(SUnit* unit)
{
    if (strcmp(unit->PROJECTILE, AMMO_TYPE_NONE) == 0) return false;
    return true;
}

bool Superhuman::IsHeroUnit(SUnit* unit)
{
    if ((strcmp(unit->CLASSNAME, UNIT_CLASS_HERO_ZSK) == 0) || (strcmp(unit->CLASSNAME, UNIT_CLASS_HERO_NYSZ) == 0)) return true;
    if ((strcmp(unit->CLASSNAME, UNIT_CLASS_HERO_FW) == 0) || (strcmp(unit->CLASSNAME, UNIT_CLASS_HERO_PR) == 0)) return true;
    if ((strcmp(unit->CLASSNAME, UNIT_CLASS_HERO_KERO) == 0) || (strcmp(unit->CLASSNAME, UNIT_CLASS_HERO_SPY)) == 0) return true;
    if ((strcmp(unit->CLASSNAME, UNIT_CLASS_HERO_LEGHAJO) == 0)) return true;
    return false;
}

bool Superhuman::IsValidUnit(SUnit* unit, bool iterate, int index, bool exclview, bool exclmine, bool exlflag)
{
    if (this->IsBadPtr((DWORD*)unit)) return false;
    switch (iterate) {
    case true: if ((!index?0:1 > unit->ID) || MAX_UNITS < unit->ID) return false;
    case false: if (0 > unit->ID || MAX_UNITS < unit->ID) return false;
    }
    
    if ((strcmp(unit->CLASSNAME, "null") == 0) || (strcmp(unit->NAME, "null") == 0)) return false;
    if (exclview && (strcmp(unit->CLASSNAME, UNIT_CLASS_VIEWER) == 0)) return false;
    if (exclmine && (strcmp(unit->CLASSNAME, UNIT_CLASS_MINE) == 0)) return false;
    if (exlflag && (strcmp(unit->CLASSNAME, RABBIT_FLAG) == 0) ||
        (strcmp(unit->CLASSNAME, PIG_FLAG) == 0) ||
        (strcmp(unit->CLASSNAME, CTF_FLAG) == 0) ||
        (strcmp(unit->CLASSNAME, DOMINATION) == 0)) return false;
    return true;
}

void Superhuman::InitMenuStyle()
{
    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style->WindowPadding = ImVec2(15, 15); // ty: https://www.unknowncheats.me/forum/general-programming-and-reversing/269953-imgui-theme-color.html
    style->WindowRounding = .0f;

    style->FramePadding = ImVec2(5, 5);

    style->ItemSpacing = ImVec2(12, 8);
    style->ItemInnerSpacing = ImVec2(8, 6);

    style->IndentSpacing = 25.0f;

    style->ScrollbarSize = 15.0f;
    style->ScrollbarRounding = .0f;

    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;

    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);

    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImVec4(.0f, .0f, .0f, .0f);

    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);

    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);

    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);

    style->Colors[ImGuiCol_CheckMark] = ImVec4(255.0f, 255.0f, 255.0f, 255.0f);

    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);

    style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);

    style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);

    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);

    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);

    style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}
