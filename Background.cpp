#include "Background.h"

int TexID_White;
int TexID_PixelGround;
int TexID_GroundBlur;
int TexID_TopViewGround;
int TexID_PolygonGround;
int TexID_Cloud01;
int TexID_Cloud02;
int TexID_Grass;
int TexID_Mountain1;
int TexID_Mountain2;
int TexID_Ground;
int TexID_Black;

void Ground_Initialize()
{
	TexID_White = Texture_Load(L"Resource/Texture/w.png");
	TexID_PixelGround = Texture_Load(L"Resource/Texture/pixel_ground.jpg");
	TexID_TopViewGround = Texture_Load(L"Resource/Texture/Ground_Top.png");
	TexID_PolygonGround = Texture_Load(L"Resource/Texture/Polygon_ground.png");
	TexID_Cloud01 = Texture_Load(L"Resource/Texture/Polygon_ground_cloud_1.png");
	TexID_Cloud02 = Texture_Load(L"Resource/Texture/Polygon_ground_cloud_2.png");
	TexID_Grass = Texture_Load(L"Resource/Texture/Polygon_ground_grass.png");
	TexID_Mountain1 = Texture_Load(L"Resource/Texture/Polygon_ground_mountain_re_1.png");
	TexID_Mountain2 = Texture_Load(L"Resource/Texture/Polygon_ground_mountain_re_2.png");
	TexID_Ground = Texture_Load(L"Resource/Texture/Pixel_Ground.png");
	TexID_Black = Texture_Load(L"Resource/Texture/Black.png");
}

void White_Draw()
{
	Sprite_Draw(TexID_White, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, { 1.f, 1.f, 1.f, 1.f });
}

float x = -(float)SCREEN_WIDTH;
int Ground_Draw()
{
	if (x < 0)
	{
		Sprite_Draw(TexID_PixelGround, x, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
		x += 5.f; // Move Right
		return 0;
		if (x > 0) x = 0;
	}
	else
	{
		Sprite_Draw(TexID_PixelGround, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
		return 1;
	}
}

float G_blur = 1.0f;
int Ground_Blur()
{
	if (G_blur > 0.0f)
	{
		Sprite_Draw(TexID_PixelGround, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, { 1.f, 1.f, 1.f, G_blur });
		G_blur -= 0.01f;
		if (G_blur < 0.0f) G_blur = 0.0f;
		return 0;
	}
	else
	{
		Sprite_Draw(TexID_PixelGround, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, { 1.f, 1.f, 1.f, 0.f });
		return 2;
	}
}
float TG_blur = 0.0f;
int Top_View_Ground()
{

	if (TG_blur < 1.0f)
	{
		Sprite_Draw(TexID_TopViewGround, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, { 1.f, 1.f, 1.f, TG_blur });
		TG_blur += 0.01f;
		return 0; // Return 0 to Indicate Drawing is in Progress
		if (TG_blur > 1.0f) TG_blur = 1.0f;
	}
	else
	{
		Sprite_Draw(TexID_TopViewGround, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, { 1.f, 1.f, 1.f, 1.f });
		return 1; // Return 1 to Indicate Drawing is Complete
	}
}
float Fx = 0.f;
int FGround_Move()
{
	if (Fx <= 0)
	{
		Sprite_Draw(TexID_TopViewGround, Fx, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
		Fx -= 5.f;
		return 0;
		if (Fx < -(float)SCREEN_WIDTH) Fx = 0;
	}
	else
	{
		Sprite_Draw(TexID_TopViewGround, -(float)SCREEN_WIDTH, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
		return 1;
	}
}
float Px = (float)SCREEN_WIDTH;
int Polygon_Ground_Draw()
{
	if (Px > 0)
	{
		Sprite_Draw(TexID_PolygonGround, Px, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
		Px -= 5.f;
		return 0;
		if (Px < 0.f) Px = 0;
	}
	else
	{
		Sprite_Draw(TexID_PolygonGround, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
		return 1;
	}
}
void Polygon_Ground()
{
	Sprite_Draw(TexID_PolygonGround, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
}
float Gx = -(float)SCREEN_WIDTH;
int Grass_Draw()
{
	if (Gx < 0)
	{
		Sprite_Draw(TexID_Grass, Gx, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
		Gx += 5.f;
		return 0;
		if (Gx > 0) Gx = 0;
	}
	else
	{
		Sprite_Draw(TexID_Grass, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
		return 1;
	}
}
float Cx1 = -(float)SCREEN_WIDTH / 2;
int Cloud_Draw_1()
{
	if (Cx1 < 1000)
	{
		Sprite_Draw(TexID_Cloud01, Cx1, 0.f, 419.f, 186.f);
		Cx1 += 5.f;
		return 0;
		if (Cx1 > 1000) Cx1 = 1000;
	}
	else
	{
		Sprite_Draw(TexID_Cloud01, 1000, 0.f, 419.f, 186.f);
		return 1;
	}
}
float Cx2 = -328.f;
int Cloud_Draw_2()
{
	if (Cx2 < 450)
	{
		Sprite_Draw(TexID_Cloud02, Cx2, 0.f, 328.f, 141.f);
		Cx2 += 2.f;
		return 0;
		if (Cx2 > 450) Cx2 = 450;
	}
	else
	{
		Sprite_Draw(TexID_Cloud02, 450, 0.f, 328.f, 141.f);
		return 1;
	}
}
float Mx1 = -2024.f;
int Mountain_Draw_1()
{
	if (Mx1 < -100)
	{
		Sprite_Draw(TexID_Mountain1, Mx1, (float)SCREEN_HEIGHT - 470.f, 2024.f, 308.f);
		Mx1 += 5.f;
		return 0;
		if (Mx1 > -100) Mx1 = -100;
	}
	else
	{
		Sprite_Draw(TexID_Mountain1, -100, (float)SCREEN_HEIGHT - 470.f, 2024.f, 308.f);
		return 1;
	}
}
float Mx2 = -1822.f;
int Mountain_Draw_2()
{
	if (Mx2 < -50)
	{
		Sprite_Draw(TexID_Mountain2, Mx2, (float)SCREEN_HEIGHT - 485.f, 1822.f, 322.f);
		Mx2 += 7.f;
		return 0;
		if (Mx2 > -50) Mx2 = -50;
	}
	else
	{
		Sprite_Draw(TexID_Mountain2, -50, (float)SCREEN_HEIGHT - 485.f, 1822.f, 322.f);
		return 1;
	}
}


float PSx = 0.f;
int Polygon_Ground_Move()
{
	PSx += 2.f;
	if (PSx >= SCREEN_WIDTH)
		PSx = 0.f;

	Sprite_Draw(TexID_PolygonGround, PSx, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	Sprite_Draw(TexID_PolygonGround, PSx - SCREEN_WIDTH, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	if (PSx >= 1500.f)
		return 3;
	else if (PSx >= 1000.f)
		return 2;
	else if (PSx >= 500.f)
		return 1;
}

float GSx = 0.f;
void Polygon_Grass_Move()
{
	GSx += 3.f;
	if (GSx >= SCREEN_WIDTH)
		GSx = 0.f;

	Sprite_Draw(TexID_Grass, GSx, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	Sprite_Draw(TexID_Grass, GSx - SCREEN_WIDTH, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
}

float MSx1 = -100.f;
void Polygon_Mountain_Move1()
{
	MSx1+= 2.f;
	if (MSx1 >= SCREEN_WIDTH)
		MSx1 = -100.f;

	Sprite_Draw(TexID_Mountain1, MSx1, (float)SCREEN_HEIGHT - 470.f, 2024.f, 308.f);
	Sprite_Draw(TexID_Mountain1, MSx1 - 2024.f, (float)SCREEN_HEIGHT - 470.f, 2024.f, 308.f);
}

float MSx2 = -50.f;
void Polygon_Mountain_Move2()
{
	MSx2 += 1.f;
	if (MSx2 >= SCREEN_WIDTH)
		MSx2 = -50.f;

	Sprite_Draw(TexID_Mountain2, MSx2, (float)SCREEN_HEIGHT - 485.f, 1822.f, 322.f);
	Sprite_Draw(TexID_Mountain2, MSx2 - 1822.f, (float)SCREEN_HEIGHT - 485.f, 1822.f, 322.f);
}

float CSx1 = 1000.f;
void Polygon_Cloud_Move1()
{
	CSx1 += 2.f;
	if (CSx1 >= SCREEN_WIDTH)
		CSx1 = 0.f;

	Sprite_Draw(TexID_Cloud01, CSx1, 0.f, 419.f, 186.f);
	Sprite_Draw(TexID_Cloud01, CSx1 - SCREEN_WIDTH, 0.f, 419.f, 186.f);
}

float CSx2 = 450.f;
void Polygon_Cloud_Move2()
{
	CSx2 += 1.f;
	if (CSx2 >= SCREEN_WIDTH)
		CSx2 = 0.f;

	Sprite_Draw(TexID_Cloud02, CSx2, 0.f, 328.f, 141.f);
	Sprite_Draw(TexID_Cloud02, CSx2 - SCREEN_WIDTH, 0.f, 328.f, 141.f);
}

float PBlur = 0.0f;
int PGround_Blur()
{
	if (PBlur < 1.0f)
	{
		Sprite_Draw(TexID_Ground, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, { 1.f, 1.f, 1.f, PBlur });
		PBlur += 0.01f;
		return 0;
		if (PBlur > 1.0f) PBlur = 1.0f;
	}
	else
	{
		Sprite_Draw(TexID_Ground, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, { 1.f, 1.f, 1.f, 1.f });
		return 1;
	}
}

void PGround()
{
	Sprite_Draw(TexID_Ground, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, { 1.f, 1.f, 1.f, 1.f });
}

float BBlur = 0.0f;
void Black_Blur()
{
	if (BBlur < 1.0f)
	{
		Sprite_Draw(TexID_Black, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, { 1.f, 1.f, 1.f, BBlur });
		BBlur += 0.01f;
		if (BBlur > 1.0f) BBlur = 1.0f;
	}
	else
	{
		Sprite_Draw(TexID_Black, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, { 1.f, 1.f, 1.f, 1.f });
	}
}