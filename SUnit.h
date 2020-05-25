#pragma once

#define UNIT_STATUS_NONE 0 //Not hovered, not selected
#define UNIT_STATUS_SELECTED 1 //Not hovered, selected
#define UNIT_STATUS_HOVERED 2 //Hovered, not selected
#define UNIT_STATUS_BOTH 3 //Hovered, selected

#define UNIT_SHOT_NORMAL 1
#define UNIT_SHOT_THROUGH 5

#define UNIT_CLASS_PIG_COMMAND "Diszno dzsip"
#define UNIT_CLASS_PIG_TANK "Diszno normal tank"
#define UNIT_CLASS_PIG_HARDTANK "Diszno hard tank"
#define UNIT_CLASS_PIG_ARMORED "Diszno pancelauto"
#define UNIT_CLASS_PIG_ARTILLERY "Diszno loveg"
#define UNIT_CLASS_PIG_ROCKET "Diszno raketas"
#define UNIT_CLASS_PIG_MORTAR "Diszno mozsar"
#define UNIT_CLASS_PIG_MINE "Diszno aknarako"
#define UNIT_CLASS_PIG_TOW "Diszno vontato"
#define UNIT_CLASS_PIG_CHOPPER "Diszno helikopter"
#define UNIT_CLASS_PIG_BOMBER "Diszno bombazo"
#define UNIT_CLASS_PIG_MOVINGFORCE "Diszno movingforce"
#define UNIT_CLASS_PIG_BUNKER "Diszno bunker mozsar"
#define UNIT_CLASS_PIG_BUNKER_AIRDEFENSE "Diszno bunker airdefense"
#define UNIT_CLASS_PIG_BUNKER_ARTILLERY "Diszno bunker loveg"

#define UNIT_CLASS_MINE "Akna"
#define UNIT_CLASS_VIEWER "Lato kisszem"

#define UNIT_CLASS_RABBIT_COMMAND "Nyul dzsip"
#define UNIT_CLASS_RABBIT_TANK "Nyul light tank"
#define UNIT_CLASS_RABBIT_HARDTANK "Nyul raketas pancelkocsi"
#define UNIT_CLASS_RABBIT_ARMORED "Nyul pancelauto"
#define UNIT_CLASS_RABBIT_ARTILLERY "Nyul loveg"
#define UNIT_CLASS_RABBIT_ROCKET "Nyul raketas"
#define UNIT_CLASS_RABBIT_MORTAR "Nyul mozsar"
#define UNIT_CLASS_RABBIT_MINE "Nyul aknarako"
#define UNIT_CLASS_RABBIT_TOW "Nyul vontato"
#define UNIT_CLASS_RABBIT_CHOPPER "Nyul helikopter"
#define UNIT_CLASS_RABBIT_BOMBER "Nyul bombazo"
#define UNIT_CLASS_RABBIT_MOVINGFORCE "Nyul movingforce"
#define UNIT_CLASS_RABBIT_BUNKER "Nyul bunker mozsar"
#define UNIT_CLASS_RABBIT_BUNKER_AIRDEFENSE "Nyul bunker airdefense"
#define UNIT_CLASS_RABBIT_BUNKER_ARTILLERY "Nyul bunker loveg"

#define SERVICE_CLASS_AMMO "Ammo"
#define SERVICE_CLASS_FUEL "Fuel"
#define SERVICE_CLASS_HEALTH "Service"

#define RABBIT_FLAG "Nyul zaszlo"
#define PIG_FLAG "Diszno zaszlo"
#define CTF_FLAG "CTF csapatzaszlo"
#define DOMINATION "Domination"

#define UPGRADE_FUEL "Upgrade fuel"
#define UPGRADE_AMMO "Upgrade ammo"
#define UPGRADE_SIGHT "Upgrade sight"
#define UPGRADE_MINESEEKER "Upgrade mine seeker"
#define UPGRADE_ARMOR "Upgrade armor"
#define UPGRADE_REPAIRKIT "Upgrade repair kit"
#define UPGRADE_TURBO "Upgrade turbo"
#define UPGRADE_BEER "Upgrade diszno sor"
#define UPGRADE_CARROT "Upgrade nyul repa"

#define UNIT_CLASS_HERO_KERO "Kero"
#define UNIT_CLASS_HERO_ZSK "Zsiros Korom"
#define UNIT_CLASS_HERO_NYSZ "Nyalas Szaj"
#define UNIT_CLASS_HERO_FW "Fogas Wili"
#define UNIT_CLASS_HERO_PR "Point Roger"
#define UNIT_CLASS_HERO_SPY "Spy"
#define UNIT_CLASS_HERO_LEGHAJO "Leghajo"

#define AMMO_TYPE_MINE "Akna"
#define AMMO_TYPE_CRIT_PIG "Makk"
#define AMMO_TYPE_CRIT_RABBIT "Repa"
#define AMMO_TYPE_INVISIBLE "invisible"
#define AMMO_TYPE_MORTAR "Mozsar lovedek"
#define AMMO_TYPE_MOVINGFORCE_PIG "Radioaktiv hordo diszno"
#define AMMO_TYPE_MOVINGFORCE_RABBIT "Radioaktiv hordo nyul"
#define AMMO_TYPE_BOMB "Bomba"
#define AMMO_TYPE_ROCKET "Raketa"
#define AMMO_TYPE_HOMEROCKET "int_Raketa"
#define AMMO_TYPE_ARTILLERY "Loveg lovedek"
#define AMMO_TYPE_SERVICE "Load Service"
#define AMMO_TYPE_FUEL "Load Fuel"
#define AMMO_TYPE_AMMO "Load Ammo"
#define AMMO_TYPE_NONE "Missing projectile name"

#define CHARACTER_PIG_COMMAND "P01-parancsnok"
#define CHARACTER_PIG_TANK "P07-normaltank"
#define CHARACTER_PIG_HARDTANK "P06-hardtank"
#define CHARACTER_PIG_ARMORED "P05-pancelkocsi"
#define CHARACTER_PIG_ARTILLERY "P04-loveges"
#define CHARACTER_PIG_ROCKET "P03-raketas"
#define CHARACTER_PIG_MORTAR "P08-Mozsar"
#define CHARACTER_PIG_MINE "P12-Aknarako"
#define CHARACTER_PIG_TOW "P02-Vontatos"
#define CHARACTER_PIG_CHOPPER "P10-Helikopter"
#define CHARACTER_PIG_BOMBER "P09-Pilota"
#define CHARACTER_PIG_MOVINGFORCE "P11-Movingforce"

#define CHARACTER_RABBIT_COMMAND "R01-Parancsnok"
#define CHARACTER_RABBIT_TANK "R07-Tank"
#define CHARACTER_RABBIT_HARDTANK "R06-Raketa"
#define CHARACTER_RABBIT_ARMORED "R05-pancel"
#define CHARACTER_RABBIT_ARTILLERY "R04-Loveges"
#define CHARACTER_RABBIT_ROCKET "R03-Raketas"
#define CHARACTER_RABBIT_MORTAR "R08-Mozsar"
#define CHARACTER_RABBIT_MINE "R12-Aknarako"
#define CHARACTER_RABBIT_TOW "R02-Vontatos"
#define CHARACTER_RABBIT_CHOPPER "R10-Helikopter"
#define CHARACTER_RABBIT_BOMBER "R09-Pilota"
#define CHARACTER_RABBIT_MOVINGFORCE "R11-Movingforce"

#define VOICE_PIG_COMMAND "P01-parancsnok"
#define VOICE_PIG_TANK "P04-normaltank"
#define VOICE_PIG_HARDTANK "P05-hardtank"
#define VOICE_PIG_ARMORED "P02-pancelkocsi"
#define VOICE_PIG_ARTILLERY "P03-loveges"
#define VOICE_PIG_ROCKET "P06-raketas"
#define VOICE_PIG_MORTAR "P09-Mozsar"
#define VOICE_PIG_MINE "P08-Aknarako"
#define VOICE_PIG_TOW "P07-Vontatos"
#define VOICE_PIG_CHOPPER "P11-Helikopter"
#define VOICE_PIG_BOMBER "P10-Bombazo"
#define VOICE_PIG_MOVINGFORCE "P12-Movingforce"

#define VOICE_RABBIT_COMMAND "R01-Parancsnok"
#define VOICE_RABBIT_TANK "R05-Tank"
#define VOICE_RABBIT_HARDTANK "R03-Tankkiller"
#define VOICE_RABBIT_ARMORED "R10-pancelkocsi"
#define VOICE_RABBIT_ARTILLERY "R04-Loveges"
#define VOICE_RABBIT_ROCKET "R06-Raketas"
#define VOICE_RABBIT_MORTAR "R07-Mozsar"
#define VOICE_RABBIT_MINE "R11-Aknarako"
#define VOICE_RABBIT_TOW "R02-Vontatos"
#define VOICE_RABBIT_CHOPPER "R08-Helikopter"
#define VOICE_RABBIT_BOMBER "R09-Bombazo"
#define VOICE_RABBIT_MOVINGFORCE "R12-Movingforce"

#define MAX_UNITS 400 //estimated
#define MAX_UNITS_MULTIPLAYER 325 //estimated

typedef class _SUnit {
public:
	char pad_0000[4]; //0x0000
	int ID; //0x0004
	char pad_0008[8]; //0x0008
	char* NAME; //0x0010
	char* TYPE; //0x0014
	char* CHARACTER; //0x0018
	char* VOICE; //0x001C
	char* MODEL; //0x0020
	char pad_0024[4]; //0x0024
	float MAXHP; //0x0028
	char pad_002C[12]; //0x002C
	float FRONTARMOR; //0x0038
	float BACKARMOR; //0x003C
	float TOPARMOR; //0x0040
	float VIEWRANGE; //0x0044
	float MINRANGE; //0x0048
	float MAXRANGE; //0x004C
	float ACTIONRANGE; //0x0050
	char pad_0054[4]; //0x0054
	bool UNTARGETABLE; //0x0058
	char pad_0059[7]; //0x0059
	int MOVETYPE; //0x0060
	char pad_0064[4]; //0x0064
	float SPEED; //0x0068
	float BODYROTATION; //0x006C
	char pad_0070[8]; //0x0070
	int MAXFUEL; //0x0078
	char pad_007C[4]; //0x007C
	int SHADOWCAST; //0x0080
	int SHADOWCAST2; //0x0084
	float TRAILPOS; //0x0088
	char pad_008C[4]; //0x008C
	float AIMSPEED; //0x0090
	int MAXAMMO; //0x0094
	int FIRERATE; //0x0098
	int SHOTTYPE; //0x009C
	float DAMAGE; //0x00A0
	char pad_00A4[16]; //0x00A4
	char* PROJECTILE; //0x00B4
	char* CRITICALPROJECTILE; //0x00B8
	char pad_00BC[8]; //0x00BC
	int AMMOTYPE; //0x00C4
	int SPECIALTYPE; //0x00C8
	char pad_00CC[392]; //0x00CC
	char* CLASSNAME; //0x0254
	int TEAMID; //0x0258
	int PLAYERID; //0x025C
	char pad_0260[4]; //0x0260
	float POSITIONX; //0x0264
	char pad_0268[4]; //0x0268
	float POSITIONY; //0x026C
	char pad_0270[4]; //0x0270
	float TURRETANGLE; //0x0274
	char pad_0278[16]; //0x0278
	float HEALTH; //0x0288
	float FUEL; //0x028C
	int AMMO; //0x0290
	int NUKECHARGE; //0x0294
	char pad_0298[16]; //0x0298
	int LEVEL; //0x02A8
	char pad_02AC[116]; //0x02AC
	int SELECTSTATUS; //0x0320
	char pad_0324[68]; //0x0324
	bool SPECIALTOGGLE; //0x0368
	char pad_0369[11]; //0x0369
} SUnit;

typedef struct _SUnitProp {
	bool SpinBot;
	bool GodMode;
	bool InfiniteResources;
	float flAngle;

	_SUnitProp()
	{
		this->ResetVariables();
	}

	void ResetVariables()
	{
		SpinBot = false;
		GodMode = false;
		InfiniteResources = false;
		flAngle = 0.0;
	}
} SUnitProp;

typedef struct _SUnitDescription {
	char* newclassname;
	int level;
	int* upgrades;
	float xp;
	bool isStarter;
	int kills;

	_SUnitDescription()
	{
		this->ResetVariables();
	}

	void ResetVariables()
	{
		newclassname = (char*)"None";
		level = 0;
		upgrades = nullptr;
		xp = 0.0;
		kills = 0;
		isStarter = false;
	}
} SUnitDescription;

/* Unused at all, haven't found any way to replace the models without restarting the match/game, also it is better to change the unit class rather than the model
#define MODEL_PIG_COMMAND "units\skinned\d_dzsip"
#define MODEL_PIG_TANK "units\skinned\d_normaltank"
#define MODEL_PIG_HARDTANK "units\skinned\d_hardtank"
#define MODEL_PIG_ARMORED "units\skinned\d_pancelkocsi"
#define MODEL_PIG_ARTILLERY "units\skinned\d_loveg"
#define MODEL_PIG_ROCKET "units\skinned\d_raketas"
#define MODEL_PIG_MORTAR "units\skinned\d_mozsar"
#define MODEL_PIG_MINE "units\skinned\d_aknarako"
#define MODEL_PIG_TOW "units\skinned\d_vontato_normal.4d"
#define MODEL_PIG_CHOPPER "units\skinned\d_helikopter"
#define MODEL_PIG_BOMBER "units\skinned\d_bombazo"
#define MODEL_PIG_MOVINGFORCE "units\skinned\d_movingforce"
#define MODEL_PIG_BUNKER "units\1text\d_bunker_mozsar.4d"
#define MODEL_PIG_BUNKER_AIRDEFENSE "units\1text\d_bunker_airdefense.4d"
#define MODEL_PIG_BUNKER_ARTILLERY "units\1text\d_bunker_loveg.4d"

#define MODEL_RABBIT_COMMAND "units\skinned\ny_dzsip"
#define MODEL_RABBIT_TANK "units\skinned\ny_lighttank"
#define MODEL_RABBIT_HARDTANK "units\skinned\ny_hardtank"
#define MODEL_RABBIT_ARMORED "units\skinned\ny_pancelkocsi"
#define MODEL_RABBIT_ARTILLERY "units\skinned\ny_loveg"
#define MODEL_RABBIT_ROCKET "units\skinned\ny_raketas"
#define MODEL_RABBIT_MORTAR "units\skinned\ny_mozsar"
#define MODEL_RABBIT_MINE "units\skinned\ny_aknarako"
#define MODEL_RABBIT_TOW "units\skinned\ny_vontato_normal.4d"
#define MODEL_RABBIT_CHOPPER "units\skinned\ny_helikopter"
#define MODEL_RABBIT_BOMBER "units\skinned\ny_bombazo"
#define MODEL_RABBIT_MOVINGFORCE "units\skinned\ny_movingforce"
#define MODEL_RABBIT_BUNKER "units\1text\ny_bunker_mozsar.4d"
#define MODEL_RABBIT_BUNKER_AIRDEFENSE "units\1text\ny_bunker_airdefense.4d"
#define MODEL_RABBIT_BUNKER_ARTILLERY "units\1text\ny_bunker_loveg.4d"*/