#include "Background.h"

int TexID_White;
int TexID_PixelGround;
int TexID_GroundBlur;

void Ground_Initialize()
{
	TexID_White = Texture_Load(L"Resource/Texture/w.png");
	TexID_PixelGround = Texture_Load(L"Resource/Texture/pixel_ground.jpg");
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
		G_blur -= 0.01;
		if (G_blur < 0.0f) G_blur = 0.0f;
		return 0;
	}
	else
	{
		Sprite_Draw(TexID_PixelGround, 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, { 1.f, 1.f, 1.f, 0.f });
		return 1;
	}
}