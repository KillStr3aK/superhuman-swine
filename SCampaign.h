#pragma once
#define IsMultiMode 0x998D0 //unused

typedef class _SCampaign
{
public:
    char pad_0000[8]; //0x0000
    int DIFFICULTY; //0x0008
    char pad_000C[24]; //0x000C
    int SP; //0x0024
    char pad_0028[12]; //0x0028
    char* MISSION; //0x0034
} SCampaign;