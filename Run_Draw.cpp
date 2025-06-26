#include "Run.h"

int TexID_Run01, TexID_Run02, TexID_Run03, TexID_Run04;

int AID_Run01, AID_Run02, AID_Run03, AID_Run04;

int Run_PID_01, Run_PID_02, Run_PID_03, Run_PID_04;

const constexpr int SCREEN_WIDTH = 1920;
const constexpr int SCREEN_HEIGHT = 1080;

struct RunData
{
	int ID;
	float X, Y;
	float Width, Height;
};

void Run_Initialize()
{ 
	TexID_Run01 = Texture_Load(L"Resource/Texture/runningman001.png");
	TexID_Run02 = Texture_Load(L"Resource/Texture/runningman002.png");
	TexID_Run03 = Texture_Load(L"Resource/Texture/runningman003.png");
	TexID_Run04 = Texture_Load(L"Resource/Texture/runningman000.png");

	AID_Run01 = SpriteAni_Get_Pattern_Info(TexID_Run01, 10, 5, 0.2, { 140, 200 }, { 140 * 0, 200 * 0 }, true);
	AID_Run02 = SpriteAni_Get_Pattern_Info(TexID_Run02, 10, 5, 0.2, { 140, 200 }, { 140 * 0, 200 * 0 }, true);
	AID_Run03 = SpriteAni_Get_Pattern_Info(TexID_Run03, 10, 5, 0.2, { 140, 200 }, { 140 * 0, 200 * 0 }, true);
	AID_Run04 = SpriteAni_Get_Pattern_Info(TexID_Run04, 8, 8, 0.2, { 100, 200 }, { 100 * 0, 200 * 0 }, true);

	Run_PID_01 = SpriteAni_CreatePlayer(AID_Run01);
	Run_PID_02 = SpriteAni_CreatePlayer(AID_Run02);
	Run_PID_03 = SpriteAni_CreatePlayer(AID_Run03);
	Run_PID_04 = SpriteAni_CreatePlayer(AID_Run04);
}

RunData RMan1 = { Run_PID_01, ((float)SCREEN_WIDTH - 140.f) / 2, 625.f, 140.f, 200.f};
float Move_X = (float)SCREEN_WIDTH;

int Run_To_Middle_Draw()
{ 
	if (Move_X > RMan1.X)
	{
		SpriteAni_Update(1.0 / 180.0);
		SpriteAni_Draw(RMan1.ID, Move_X, RMan1.Y, RMan1.Width, RMan1.Height);
		Move_X -= 2.5f; // Move Left
		return 0;
		if (Move_X < RMan1.X) Move_X = RMan1.X; // Stop at Middle
	}
	else
	{
		SpriteAni_Update(1.0 / 90.0); // Update Animation Frame
		SpriteAni_Draw(RMan1.ID, RMan1.X, RMan1.Y, RMan1.Width, RMan1.Height);
		return 1; // Return 1 to Indicate Drawing is Complete
	}
}

int Run_To_Left()
{
	SpriteAni_Draw(RMan1.ID, Move_X, RMan1.Y, RMan1.Width, RMan1.Height);
	Move_X -= 5.f; // Move Left
	if (Move_X < -RMan1.Width)
		return 2;
}

