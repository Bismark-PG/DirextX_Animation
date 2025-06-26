#include "HAL.h"
#include "Run.h"

float SCREEN_WIDTH = 1920.f;
float SCREEN_HEIGHT = 1080.f;

int TexID_HAL;

struct HAL
{
	int ID;
	float x, y;
	float width, height;
	XMFLOAT4 color;
};

HAL HAL_ = { 0, (SCREEN_WIDTH - 1057.f) / 2, (SCREEN_HEIGHT - 260.f) / 2, 1057.f, 260.f, {1.f, 1.f, 1.f, 1.f} };

void HAL_Initialize()
{
	HAL_.ID = Texture_Load(L"Resource/Texture/HAL.jpg");
}

float blur = 0.0f;
float run_x = 0.0f;

int HAL_Blur()
{
	if (blur < 1.0f)
	{
		Sprite_Draw(HAL_.ID, HAL_.x, HAL_.y, HAL_.width, HAL_.height, { 1.f, 1.f, 1.f, blur });
		blur += 0.01f;
		return 0; // Return 0 to Indicate Drawing is in Progress
		if (blur > 1.0f) blur = 1.0f;
	}
	else
	{
		Sprite_Draw(HAL_.ID, HAL_.x, HAL_.y, HAL_.width, HAL_.height, { 1.f, 1.f, 1.f, 1.f });
		return 1; // Return 1 to Indicate Drawing is Complete
	}
}

void HAL_Move()
{
	Sprite_Draw(HAL_.ID, HAL_.x, HAL_.y, HAL_.width, HAL_.height, HAL_.color);
	HAL_.x += 5.f; // Move Right
}
