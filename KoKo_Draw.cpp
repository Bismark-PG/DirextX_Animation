#include "KoKo.h"

// Set Texture ID
int TexID_KoKo;

int AID_rw;
int AID_lw;
int AID_sm;
int AID_Box;
int AID_Block;
int AID_Ladder;
int AID_ap;

int PID_01;
int PID_02;
int PID_03;
int PID_04;
int PID_05;
int PID_06;
int PID_07;

void KoKo_Initialize()
{
	// Input Texture File
	// int name = Texture_Load(L"Texture address");
	TexID_KoKo = Texture_Load(L"Resource/Texture/kokosozai.png");

	// Make Texture Animation Pattern
	// (Pattern ID, Pattern Play Time, Pattern Size (X, Y), Start Position (W, H), Loop Animation (False = NO / True = YES)
	AID_rw = SpriteAni_Get_Pattern_Info(TexID_KoKo, 13, 16, 0.05, { 32, 32 }, { 32 * 0, 32 * 0 }, true);
	AID_lw = SpriteAni_Get_Pattern_Info(TexID_KoKo, 13, 16, 0.1, { 32, 32 }, { 32 * 0, 32 * 1 }, true);
	AID_sm = SpriteAni_Get_Pattern_Info(TexID_KoKo, 6, 16, 0.1, { 32, 32 }, { 32 * 0, 32 * 2 }, true);
	AID_Box = SpriteAni_Get_Pattern_Info(TexID_KoKo, 4, 16, 0.5, { 32, 32 }, { 32 * 2, 32 * 5 }, false);
	AID_Block = SpriteAni_Get_Pattern_Info(TexID_KoKo, 1, 16, 0.1, { 32, 32 }, { 32 * 0, 32 * 5 }, false);
	AID_Ladder = SpriteAni_Get_Pattern_Info(TexID_KoKo, 1, 16, 0.1, { 32, 32 }, { 32 * 1, 32 * 5 }, false);
	AID_ap = SpriteAni_Get_Pattern_Info(TexID_KoKo, 15, 16, 0.25, { 32, 32 }, { 32 * 0, 32 * 4 }, true);

	// Create Animation Player
	PID_01 = SpriteAni_CreatePlayer(AID_rw);
	PID_02 = SpriteAni_CreatePlayer(AID_lw);
	PID_03 = SpriteAni_CreatePlayer(AID_sm);
	PID_04 = SpriteAni_CreatePlayer(AID_ap);
	PID_05 = SpriteAni_CreatePlayer(AID_Box);
	PID_06 = SpriteAni_CreatePlayer(AID_Block);
	PID_07 = SpriteAni_CreatePlayer(AID_Ladder);
}

void KoKo_Draw()
{
	// Show Texture Animation (What, Where, Size)
	// Sample
	SpriteAni_Draw(PID_01, 128.f, 700.f, 128.f, 128.f);
	SpriteAni_Draw(PID_02, 128.f, 64.f, 128.f, 128.f);
	SpriteAni_Draw(PID_03, 256.f, 64.f, 128.f, 128.f);
	SpriteAni_Draw(PID_04, 384.f, 64.f, 128.f, 128.f);

	// Left
	SpriteAni_Draw(PID_06, 512.f, 560.f, 128.f, 128.f);
	SpriteAni_Draw(PID_06, 512.f, 444.f, 128.f, 128.f);
	SpriteAni_Draw(PID_06, 512.f, 316.f, 128.f, 128.f);

	// Ladder
	SpriteAni_Draw(PID_07, 640.f, 688.f, 128.f, 128.f);
	SpriteAni_Draw(PID_07, 640.f, 560.f, 128.f, 128.f);
	SpriteAni_Draw(PID_07, 640.f, 444.f, 128.f, 128.f);
	SpriteAni_Draw(PID_07, 640.f, 316.f, 128.f, 128.f);

	// Right
	SpriteAni_Draw(PID_06, 768.f, 560.f, 128.f, 128.f);
	SpriteAni_Draw(PID_06, 768.f, 444.f, 128.f, 128.f);
	SpriteAni_Draw(PID_06, 768.f, 316.f, 128.f, 128.f);

	// Up
	SpriteAni_Draw(PID_06, 896.f, 316.f, 128.f, 128.f);
	SpriteAni_Draw(PID_06, 1024.f, 316.f, 128.f, 128.f);
	SpriteAni_Draw(PID_06, 1152.f, 316.f, 128.f, 128.f);
	SpriteAni_Draw(PID_06, 1280.f, 316.f, 128.f, 128.f);
	SpriteAni_Draw(PID_06, 1408.f, 316.f, 128.f, 128.f);
	SpriteAni_Draw(PID_05, 1408.f, 188.f, 128.f, 128.f);
}