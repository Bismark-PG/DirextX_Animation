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
	float Angle;
}RMan1, RMan2, RMan3, RMan4;

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

	RMan1 = { Run_PID_01, ((float)SCREEN_WIDTH - 140.f) / 2, 625.f, 140.f, 200.f, 0.f };
	RMan2 = { Run_PID_02, ((float)SCREEN_WIDTH - 140.f) / 2, 625.f, 140.f, 200.f, 0.f };
	RMan3 = { Run_PID_03, ((float)SCREEN_WIDTH - 140.f) / 2, 730.f, 140.f, 200.f, 0.f };
	RMan4 = { Run_PID_04, 890.f, 650.f, 0.f, 0.f, 0.f };
}

float Move_X = (float)SCREEN_WIDTH;

int Run_To_Middle_Draw()
{
	if (Move_X > RMan1.X)
	{
		SpriteAni_Update(1.0 / 180.0);
		SpriteAni_Draw(RMan1.ID, Move_X, RMan1.Y, RMan1.Width, RMan1.Height, RMan1.Angle);
		Move_X -= 2.5f; // Move Left
		return 0;
		if (Move_X < RMan1.X) Move_X = RMan1.X; // Stop at Middle
	}
	else
	{
		SpriteAni_Update(1.0 / 90.0); // Update Animation Frame
		SpriteAni_Draw(RMan1.ID, RMan1.X, RMan1.Y, RMan1.Width, RMan1.Height, RMan1.Angle);
		return 1; // Return 1 to Indicate Drawing is Complete
	}
}
int Run_To_Left()
{
	SpriteAni_Draw(RMan1.ID, Move_X, RMan1.Y, RMan1.Width, RMan1.Height, RMan1.Angle);
	Move_X -= 5.f; // Move Left
	if (Move_X < -RMan1.Width)
		return 2;
}


int Run_To_Front()
{
	if (RMan4.Width < 50.f)
	{
		SpriteAni_Draw(RMan4.ID, RMan4.X, RMan4.Y, RMan4.Width, RMan4.Height, RMan4.Angle);
		RMan4.X -= 0.15625f;
		RMan4.Y -= 0.3125f;
		RMan4.Width += 0.3125f;
		RMan4.Height += 0.625f;
		return 0;
		if (RMan4.Width > 50.f)
		{
			RMan4.Width = 50.f;
			RMan4.Height = 100.f;
		}
	}
	else if (RMan4.Width < 100.f)
	{
		SpriteAni_Draw(RMan4.ID, RMan4.X, RMan4.Y, RMan4.Width, RMan4.Height, RMan4.Angle);
		RMan4.X -= 0.3125f;
		RMan4.Y -= 0.625f;
		RMan4.Width += 0.625f;
		RMan4.Height += 1.25f;
		return 0;
		if (RMan4.Width > 100.f)
		{
			RMan4.Width = 100.f;
			RMan4.Height = 200.f;
		}
	}
	else if (RMan4.Width < 200.f)
	{
		SpriteAni_Draw(RMan4.ID, RMan4.X, RMan4.Y, RMan4.Width, RMan4.Height, RMan4.Angle);
		RMan4.X -= 0.25f;
		RMan4.Y += 0.125f;
		RMan4.Width += 0.625f;
		RMan4.Height += 1.25f;
		return 0;
		if (RMan4.Width > 200.f)
		{
			RMan4.Width = 200.f;
			RMan4.Height = 400.f;
		}
	}
	else if (RMan4.Width < 300.f)
	{
		SpriteAni_Draw(RMan4.ID, RMan4.X, RMan4.Y, RMan4.Width, RMan4.Height, RMan4.Angle);
		RMan4.X -= 0.5f;
		RMan4.Y += 0.25f;
		RMan4.Width += 0.625f;
		RMan4.Height += 1.25f;
		return 0;
		if (RMan4.Width > 300.f)
		{
			RMan4.Width = 300.f;
			RMan4.Height = 600.f;
		}
	}
	else if (RMan4.Y < SCREEN_HEIGHT)
	{
		SpriteAni_Draw(RMan4.ID, RMan4.X, RMan4.Y, RMan4.Width, RMan4.Height, RMan4.Angle);
		RMan4.X -= 0.5f;
		RMan4.Y += 2.5f;
		return 0;
		if (RMan4.Y > SCREEN_HEIGHT)
		{
			RMan4.Y = SCREEN_HEIGHT;
		}
	}
	else
	{
		SpriteAni_Draw(RMan4.ID, RMan4.X, RMan4.Y, RMan4.Width, RMan4.Height, RMan4.Angle);
		return 1;
	}
}

float Move_PX = (float)SCREEN_WIDTH;

int Run_Poly()
{
	if (Move_PX > RMan3.X)
	{
		SpriteAni_Draw(RMan3.ID, Move_PX, RMan3.Y, RMan3.Width, RMan3.Height, RMan3.Angle);
		Move_PX -= 5.f; // Move Left
		if (Move_PX < -RMan3.Width)
			return 0;
	}
	else
	{
		SpriteAni_Draw(RMan3.ID, RMan3.X, RMan3.Y, RMan3.Width, RMan3.Height, RMan3.Angle);
		return 1;
	}
}

void Run_Poly_Middle()
{
	SpriteAni_Draw(RMan3.ID, RMan3.X, RMan3.Y, RMan3.Width, RMan3.Height, RMan3.Angle);
}

void Run_Middle()
{
	SpriteAni_Draw(RMan1.ID, RMan1.X, 730.f, RMan1.Width, RMan1.Height, RMan1.Angle);
}

void Run_Middle_Human()
{
	SpriteAni_Draw(RMan2.ID, RMan2.X, 730.f, RMan2.Width, RMan2.Height, RMan2.Angle);
}